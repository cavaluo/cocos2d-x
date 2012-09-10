#ifndef __CCTEXTURE2DBLOCK_H__
#define __CCTEXTURE2DBLOCK_H__

#include "CCTexture2D.h"

NS_CC_BEGIN

#define Texture2DBlock_TopLelt       "_top_left"
#define Texture2DBlock_Top           "_top"
#define Texture2DBlock_TopRight      "_top_right"
#define Texture2DBlock_Left          "_left"
#define Texture2DBlock_Center        "_center"
#define Texture2DBlock_Right         "_right"
#define Texture2DBlock_BottomLeft    "_bottom_left"
#define Texture2DBlock_Bottom        "_bottom"
#define Texture2DBlock_BottomRight   "_bottom_Right"

class CC_DLL CCTexture2DBlock: public CCTexture2D
{
public:
	static CCTexture2DBlock* textureFromFile(const char* file,CCPoint origin,CCSize textSize);
	static CCTexture2DBlock* textureFromImage(CCImage * uiImage,CCPoint origin,CCSize textSize);
	bool initWithImage(CCImage * uiImage, CCPoint origin,CCSize textSize);
	bool initPremultipliedATextureWithImage(CCImage * image, unsigned int pixelsWide, unsigned int pixelsHigh,CCPoint origin,CCSize textSize);
	void setTexParameters(ccTexParams* texParams);
};

NS_CC_END

#endif /* __CCTEXTURE2DBLOCK_H__ */
