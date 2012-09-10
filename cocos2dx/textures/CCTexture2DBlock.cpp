#include "CCTexture2DBlock.h"
#include "platform/CCFileUtils.h"
#include "platform/CCImage.h"
#include "platform/CCCommon.h"
#include <math.h>
#include "ccMacros.h"
#include "CCDirector.h"
#include "CCTextureCache.h"
#include "support/ccUtils.h"

NS_CC_BEGIN

enum 
{
    kDataBufferFormat32 = 0,
    kDataBufferFormat24
};

class DataBuffer
{
public:
    DataBuffer()
        : pData(NULL)
        , nWidth(0)
        , nHeight(0)
        , nFormat(kDataBufferFormat32)
    {}

    unsigned char* pData;
    unsigned int   nWidth;
    unsigned int   nHeight;
    unsigned int   nPOTWidth;
    unsigned int   nPOTHeight;
    unsigned int   nFormat;
};

static bool getSubDataBuffer(const DataBuffer* pOriginBuffer, const CCRect& offsetRect, bool needNextPOT, DataBuffer* pOutBuffer)
{
    CCRect originRect = CCRectMake(0, 0, pOriginBuffer->nWidth, pOriginBuffer->nHeight);
    if (!originRect.intersectsRect(offsetRect))
    {
        return false;
    }

    unsigned int nBytePerPixel = 4;
    if (pOriginBuffer->nFormat == kDataBufferFormat24)
    {
        nBytePerPixel = 3;
    }

    CCRect interSectRect = originRect.getIntersectRect(offsetRect);
    CCLOG("x = %f, y = %f, width = %f, height = %f", interSectRect.origin.x, interSectRect.origin.y, interSectRect.size.width, interSectRect.size.height);
    pOutBuffer->nFormat = pOriginBuffer->nFormat;

    pOutBuffer->nWidth = interSectRect.size.width;
    pOutBuffer->nHeight = interSectRect.size.height;
    unsigned int nPOTWidth = pOutBuffer->nWidth;
    unsigned int nPOTHeight = pOutBuffer->nHeight;

    if (needNextPOT)
    {
        nPOTWidth = ccNextPOT(nPOTWidth);
        nPOTHeight = ccNextPOT(nPOTHeight);
    }

    pOutBuffer->nPOTWidth = nPOTWidth;
    pOutBuffer->nPOTHeight = nPOTHeight;

    pOutBuffer->pData = new unsigned char[nPOTWidth * nPOTHeight * nBytePerPixel];
    memset(pOutBuffer->pData, 0, nPOTWidth * nPOTHeight * nBytePerPixel);

    unsigned char* src = pOriginBuffer->pData + ((int)interSectRect.origin.x + (int)interSectRect.origin.y * pOriginBuffer->nWidth)*nBytePerPixel;
    unsigned char* dst = pOutBuffer->pData;
    unsigned char* dstSaved = dst;
    unsigned int originPitch = pOriginBuffer->nWidth * nBytePerPixel;
    unsigned int outPitch = pOutBuffer->nWidth * nBytePerPixel;
    unsigned int outPOTPitch = nPOTWidth * nBytePerPixel;

    for (unsigned int i = 0; i < pOutBuffer->nPOTHeight; i++)
    {
        if (i < pOutBuffer->nHeight)
        {
            memcpy(dst, src, outPitch);
            memcpy(dst+outPitch, dst, outPOTPitch-outPitch);
            src += originPitch;
            dst += outPOTPitch;
        }
        else
        {
            memcpy(dst, dstSaved, outPOTPitch);
            dstSaved += outPOTPitch;
            dst += outPOTPitch;
        }
    }

    return true;
}

bool CCTexture2DBlock::initWithImage( CCImage * uiImage, CCPoint origin,CCSize textSize)
{
	if (uiImage == NULL) {
		CCLOG("cocos2d: CCTexture2D. Can't create Texture. UIImage is nil");
		this->release();
		return false;
	}
	unsigned int imageWidth = uiImage->getWidth();
	unsigned int imageHeight = uiImage->getHeight();
	//m_eResolutionType = resolution;
	return initPremultipliedATextureWithImage(uiImage, imageWidth, imageHeight,origin,textSize);
}

bool CCTexture2DBlock::initPremultipliedATextureWithImage(CCImage *image, unsigned int width, unsigned int height,CCPoint origin,CCSize textSize )
{
	unsigned char*            tempData = NULL;
	unsigned int*             inPixel32 = NULL;
	unsigned char*            inPixel8 = NULL;
	unsigned short*           outPixel16 = NULL;
	bool                      hasAlpha = image->hasAlpha();
	CCSize                    imageSize = CCSizeMake((float)(image->getWidth()), (float)(image->getHeight()));
	CCSize                    requireSize = CCSizeMake((float)(textSize.width), (float)(textSize.height));
	CCTexture2DPixelFormat    pixelFormat;
	size_t                    bpp = image->getBitsPerComponent();
    DataBuffer originBuf;
   
	// compute pixel format
	if(hasAlpha) {
		pixelFormat = kCCTexture2DPixelFormat_Default;
	} else {
		if (bpp >= 8) {
			pixelFormat = kCCTexture2DPixelFormat_RGB888;
		} else  {
			pixelFormat = kCCTexture2DPixelFormat_RGB565;
		}
	}

	// Repack the pixel data into the right format
	int start_x = floor(origin.x*CC_CONTENT_SCALE_FACTOR());
	int start_y = floor(origin.y*CC_CONTENT_SCALE_FACTOR());
	int end_x  = start_x + floor(textSize.width*CC_CONTENT_SCALE_FACTOR())-1;
	int end_y   = start_y + floor(textSize.height*CC_CONTENT_SCALE_FACTOR())-1;
	
    unsigned int POTWide = ccNextPOT(end_x-start_x+1);
    unsigned int POTHigh = ccNextPOT(end_y-start_y+1);
    unsigned int length = POTWide * POTHigh;

	if (pixelFormat == kCCTexture2DPixelFormat_RGB565) {
		if (hasAlpha) {
			// Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"
			tempData = new unsigned char[length* 2];
			outPixel16 = (unsigned short*)tempData;
			inPixel32 = (unsigned int*)image->getData();

			for(unsigned short i=0; i<height; ++i) {
				inPixel32 = (unsigned int*)image->getData() + i*width;
				if(i<start_y) continue;
				if(i>end_y)  break;
				for(int j=0; j<(int)width; ++j) {
					++inPixel32;
					if(j<start_x) continue;
					if(j>end_x)   break;
					*outPixel16++ = 
						((((*inPixel32 >>  0) & 0xFF) >> 3) << 11) |  // R
						((((*inPixel32 >>  8) & 0xFF) >> 2) << 5)  |  // G
						((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);    // B
				}
			}
		} else  {
			// Convert "RRRRRRRRRGGGGGGGGBBBBBBBB" to "RRRRRGGGGGGBBBBB"
			tempData = new unsigned char[length * 2];
			outPixel16 = (unsigned short*)tempData;
			inPixel8 = (unsigned char*)image->getData();

			for(unsigned short i = 0; i < height; ++i) {
				inPixel8 = image->getData() + i*width;
				if(i<start_y) continue;
				if(i>end_y)  break;
				for(int j = 0; j < (int)width; ++j) {
					++inPixel8;
					if(j<start_x) continue;
					if(j>end_x)   break;
					*outPixel16++ = 
						(((*inPixel8++ & 0xFF) >> 3) << 11) |  // R
						(((*inPixel8++ & 0xFF) >> 2) << 5)  |  // G
						(((*inPixel8++ & 0xFF) >> 3) << 0);    // B
				}
			}
		}    
	} else if (pixelFormat == kCCTexture2DPixelFormat_RGBA4444) {
		// Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRGGGGBBBBAAAA"
		inPixel32 = (unsigned int*)image->getData();  
		tempData = new unsigned char[length * 2];
		outPixel16 = (unsigned short*)tempData;

		for(unsigned short i = 0; i < height; ++i) {
			inPixel32 = (unsigned int*)image->getData() + i*width;
			if(i<start_y) continue;
			if(i>end_y)  break;
			for(int j = 0; j < (int)width; ++j) {
				++inPixel32;
				if(j<start_x) continue;
				if(j>end_x)   break;
				*outPixel16++ = 
					((((*inPixel32 >> 0) & 0xFF) >> 4) << 12) | // R
					((((*inPixel32 >> 8) & 0xFF) >> 4) <<  8) | // G
					((((*inPixel32 >> 16) & 0xFF) >> 4) << 4) | // B
					((((*inPixel32 >> 24) & 0xFF) >> 4) << 0);  // A
			}
		}
	} else if (pixelFormat == kCCTexture2DPixelFormat_RGB5A1) {
		// Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGBBBBBA"
		inPixel32 = (unsigned int*)image->getData();   
		tempData = new unsigned char[length * 2];
		outPixel16 = (unsigned short*)tempData;

		for(unsigned short i = 0; i < height; ++i) {
			inPixel32 = (unsigned int*)image->getData() + i*width;
			if(i<start_y) continue;
			if(i>end_y)  break;
			for(int j = 0; j < (int)width; ++j) {
				++inPixel32;
				if(j<start_x) continue;
				if(j>end_x)   break;
				*outPixel16++ = 
					((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | // R
					((((*inPixel32 >> 8) & 0xFF) >> 3) <<  6) | // G
					((((*inPixel32 >> 16) & 0xFF) >> 3) << 1) | // B
					((((*inPixel32 >> 24) & 0xFF) >> 7) << 0);  // A
			}
		}
	} else if (pixelFormat == kCCTexture2DPixelFormat_A8) {
		// Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "AAAAAAAA"
		inPixel32 = (unsigned int*)image->getData();
		tempData = new unsigned char[length];
		unsigned char *outPixel8 = tempData;

		for(unsigned short i = 0; i < height; ++i) {
			inPixel32 = (unsigned int*)image->getData() + i*width;
			if(i<start_y) continue;
			if(i>end_y)  break;
			for(int j = 0; j < (int)width; ++j) {
				++inPixel32;
				if(j<start_x) continue;
				if(j>end_x)   break;
				*outPixel8++ = (*inPixel32 >> 24) & 0xFF;  // A
			}
		}
	}
	if (hasAlpha && pixelFormat == kCCTexture2DPixelFormat_RGB888) {
		// Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRRRRGGGGGGGGBBBBBBBB"
		inPixel32 = (unsigned int*)image->getData();
		tempData = new unsigned char[length * 3];
		unsigned char *outPixel8 = tempData;

		for(unsigned short i = 0; i < height; ++i) {
			inPixel32 = (unsigned int*)image->getData() + i*width;
			if(i<start_y) continue;
			if(i>end_y)  break;
			for(int j = 0; j < (int)width; ++j) {
				++inPixel32;
				if(j<start_x) continue;
				if(j>end_x)   break;
				*outPixel8++ = (*inPixel32 >> 0) & 0xFF; // R
				*outPixel8++ = (*inPixel32 >> 8) & 0xFF; // G
				*outPixel8++ = (*inPixel32 >> 16) & 0xFF; // B
			}
		}
	}

	if(pixelFormat == kCCTexture2DPixelFormat_Default) {
        originBuf.pData = image->getData();
        originBuf.nWidth = width;
        originBuf.nHeight = height;
        originBuf.nFormat = kDataBufferFormat32;
        DataBuffer out;
        getSubDataBuffer(&originBuf, CCRectMake(start_x, start_y, end_x - start_x +1, end_y - start_y+1), true, &out);
        tempData = out.pData;
        POTWide = out.nPOTWidth;
        POTHigh = out.nPOTHeight;
        /////////////////////////
// 		inPixel32 = (unsigned int*)image->getData();
// 		tempData = new unsigned char[length * 4];
//         memset(tempData, 0, length * 4);
// 		unsigned char *outPixel32 = tempData;
//         unsigned int nRowNum = 0;
//         CCLOG("POTWidth = %d, POTHeight = %d", POTWide, POTHigh);
// 		for(unsigned short i = 0; i < height; ++i) {
// 			inPixel32 = (unsigned int*)image->getData() + i*width;
// 			if(i<start_y) continue;
// 			if(i>end_y){break;}
// 			for(int j = 0; j < (int)width; ++j) {
// 				if(j<start_x) {++inPixel32;continue;}
//                 if(j>end_x){break;}
// 				*outPixel32++ = (*inPixel32 >> 0);
// 				*outPixel32++ = (*inPixel32 >> 8);
// 				*outPixel32++ = (*inPixel32 >> 16);
// 				*outPixel32++ = (*inPixel32 >> 24);
// 				++inPixel32;
// 			}
// 		}
        /////////////////////////////////////////
	}
	initWithData(tempData, pixelFormat, POTWide , POTHigh, CCSizeMake(end_x-start_x+1,end_y-start_y+1));
    //initWithData(tempData, pixelFormat, end_x-start_x+1 , end_y-start_y+1, CCSizeMake(end_x-start_x+1,end_y-start_y+1));

	if (tempData != image->getData()) {
		delete [] tempData;
	}

	m_bHasPremultipliedAlpha = image->isPremultipliedAlpha();
	return true;
}

CCTexture2DBlock* CCTexture2DBlock::textureFromFile( const char* file,CCPoint origin,CCSize textSize)
{
	CCImage image;
	image.initWithImageFile(file);

	CCTexture2DBlock * texture = NULL;
	texture = new CCTexture2DBlock();
	texture->initWithImage(&image, origin,textSize);
	if(texture)
		texture->autorelease();
	return texture;
}

CCTexture2DBlock* CCTexture2DBlock::textureFromImage(CCImage * uiImage,CCPoint origin,CCSize textSize)
{
	CCTexture2DBlock * texture = NULL;
	texture = new CCTexture2DBlock();
	texture->initWithImage(uiImage, origin,textSize);
	if(texture)
		texture->autorelease();
	return texture;
}

void CCTexture2DBlock::setTexParameters( ccTexParams* texParams )
{
	// The .png image MUST be power of 2 in order to create a continue effect.
	// eg: 32x64, 512x128, 256x1024, 64x64, etc..
	// 暂时不做检验
	//CCAssert( (m_uPixelsWide == ccNextPOT(m_uPixelsWide) && m_uPixelsHigh == ccNextPOT(m_uPixelsHigh)) ||
	//    (texParams->wrapS == GL_CLAMP_TO_EDGE && texParams->wrapT == GL_CLAMP_TO_EDGE),
	//    "GL_CLAMP_TO_EDGE should be used in NPOT textures");
	ccGLBindTexture2D( m_uName );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParams->minFilter );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParams->magFilter );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texParams->wrapS );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texParams->wrapT );
}

cocos2d::CCTexture2DBlock* CCTextureCache::addTextureBlock( const char* file,CCPoint origin,CCSize textSize,const char* name )
{
	cocos2d::CCTexture2DBlock * texture = NULL;
	std::string forKey;
	if(file) {
		forKey = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(file);
	} else{
		return NULL;
	}

	forKey += name;
	do 
	{
		// If key is nil, then create a new texture each time
		if(file && (texture = (cocos2d::CCTexture2DBlock *)m_pTextures->objectForKey(forKey.c_str())))
			break;

		CCImage image;
		unsigned char *pBuffer;
		unsigned long nSize;
		pBuffer = CCFileUtils::sharedFileUtils()->getFileData(file, "rb", &nSize);
		if(pBuffer) {
			std::string lowerCase(file);
			for (unsigned int i = 0; i < lowerCase.length(); ++i){
				lowerCase[i] = tolower(lowerCase[i]);
			}
			CCImage::EImageFormat eImageFormat = CCImage::kFmtUnKnown;
			if (std::string::npos != lowerCase.find(".png")){
				eImageFormat = CCImage::kFmtPng;
			} else if (std::string::npos != lowerCase.find(".jpg") || std::string::npos != lowerCase.find(".jpeg")){
				eImageFormat = CCImage::kFmtJpg;
			} else if (std::string::npos != lowerCase.find(".tif") || std::string::npos != lowerCase.find(".tiff")) {
				eImageFormat = CCImage::kFmtTiff;
			}
			image.initWithImageData((void*)pBuffer, nSize, eImageFormat);
			delete [] pBuffer;
		}

		// prevents overloading the autorelease pool
		texture = new cocos2d::CCTexture2DBlock();
		texture->initWithImage(&image, origin,textSize);

		if(texture) {
			m_pTextures->setObject(texture, forKey.c_str());
			texture->autorelease();
		} else {
			CCLOG("cocos2d: Couldn't add UIImage in CCTextureCache");
		}
	} while (0);
	return texture;
}

cocos2d::CCTexture2DBlock* CCTextureCache::addTextureBlock( CCImage* image,CCPoint origin,CCSize textSize,const char* file,const char* name )
{
	cocos2d::CCTexture2DBlock * texture = NULL;
	std::string forKey;
	if(file) {
		forKey = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(file);
	} else{
		return NULL;
	}

	forKey += name;
	do 
	{
		// If key is nil, then create a new texture each time
		if(file && (texture = (cocos2d::CCTexture2DBlock *)m_pTextures->objectForKey(forKey.c_str())))
			break;
		texture = new cocos2d::CCTexture2DBlock();
		texture->initWithImage(image, origin,textSize);

		if(texture) {
			m_pTextures->setObject(texture, forKey.c_str());
			texture->autorelease();
		} else {
			CCLOG("cocos2d: Couldn't add UIImage in CCTextureCache");
		}
	}while (0);

	return texture;
}

NS_CC_END
