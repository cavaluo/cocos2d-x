#include "CCScale9SpriteEx.h"
#include "platform/CCImage.h"
#include "sprite_nodes/CCSprite.h"
#include "sprite_nodes/CCSpriteBatchNode.h"
#include "support/CCPointExtension.h"
#include "textures/CCTextureCache.h"
#include "platform/CCFileUtils.h"
#include "textures/CCTexture2D.h"
#include "CCDirector.h"


bool CCScale9SpriteEx::initWithFile( const char* file,ccScale9Mode mode/*=eScale9Strach*/,const CCRect* rect, const CCRect* capInsets)
{
	CCAssert(file != NULL, "Invalid file for sprite");

	scaleMode_ = mode;
	if(scaleMode_==eScale9Strach)
		groupNode_ = CCSpriteBatchNode::create(file, 9);
	else
		groupNode_ = CCNode::create();

	CCTexture2D* texture = NULL;
	
	if(scaleMode_==eScale9Strach)
		texture = ((CCSpriteBatchNode*)groupNode_)->getTexture();
	else
		texture = CCTextureCache::sharedTextureCache()->addImage(file);

	if (!rect || rect->equals(CCRectZero)){
		CCSize textureSize = texture->getContentSize();
		spriteRect_ = CCRectMake(0, 0, textureSize.width, textureSize.height);
	} else {
		spriteRect_ = *rect;
	}

	originalSize_ = spriteRect_.size; 
	preferredSize_= originalSize_; 

	// 锚点设置为中心
	setAnchorPoint(ccp(0.5f, 0.5f));

	if (!capInsets || capInsets->equals(CCRectZero)) {
		capInsets_ = CCRectMake(
			spriteRect_.origin.x+originalSize_.width/3, 
			spriteRect_.origin.y+originalSize_.height/3, 
			originalSize_.width/3,
			originalSize_.height/3);
	} else {
		capInsets_ = *capInsets;
	}

	// 获取纹理边界
	float l = spriteRect_.origin.x;
	float t = spriteRect_.origin.y;
	float h = spriteRect_.size.height;
	float w = spriteRect_.size.width;

	// center
	if(scaleMode_==eScale9Strach){
		spriteCentre_ = CCSprite::createWithTexture(texture, capInsets_);
		spriteTop_    = CCSprite::createWithTexture(texture, CCRectMake(capInsets_.origin.x, t, capInsets_.size.width, capInsets_.origin.y-t));
		spriteBottom_ = CCSprite::createWithTexture(texture, CCRectMake(capInsets_.origin.x, capInsets_.origin.y+capInsets_.size.height, capInsets_.size.width, h-(capInsets_.origin.y-t+capInsets_.size.height)));
		spriteLeft_   = CCSprite::createWithTexture(texture, CCRectMake(l, capInsets_.origin.y, capInsets_.origin.x-l, capInsets_.size.height));
		spriteRight_  = CCSprite::createWithTexture(texture, CCRectMake(capInsets_.origin.x + capInsets_.size.width,capInsets_.origin.y,w-(capInsets_.origin.x-l+capInsets_.size.width),capInsets_.size.height));
	} else if(scaleMode_ ==eScale9Tile){
		CCImage image;
		image.initWithImageFile(file);
		spriteCentre_ = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addTextureBlock(&image,capInsets_.origin, capInsets_.size,file,Texture2DBlock_Center));
		spriteTop_    = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addTextureBlock(&image,CCPointMake(capInsets_.origin.x,t),CCSizeMake(capInsets_.size.width,capInsets_.origin.y - t),file,Texture2DBlock_Top));
		spriteBottom_ = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addTextureBlock(&image,CCPointMake(capInsets_.origin.x,capInsets_.origin.y + capInsets_.size.height),CCSizeMake(capInsets_.size.width,h-(capInsets_.origin.y-t+capInsets_.size.height)),file,Texture2DBlock_Bottom));
		spriteLeft_   = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addTextureBlock(&image,CCPointMake(l,capInsets_.origin.y),CCSizeMake(capInsets_.origin.x-l,capInsets_.size.height),file,Texture2DBlock_Left));
		spriteRight_  = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addTextureBlock(&image,CCPointMake(capInsets_.origin.x+capInsets_.size.width,capInsets_.origin.y),CCSizeMake(w-(capInsets_.origin.x - l + capInsets_.size.width),capInsets_.size.height),file,Texture2DBlock_Right));
	} else{
		CCAssert(false,"Invalid Mode.");
		return false;
	}

	spriteTopLeft_     = CCSprite::createWithTexture(texture, CCRectMake(l,t,capInsets_.origin.x-l,capInsets_.origin.y-t));
	spriteTopRight_    = CCSprite::createWithTexture(texture, CCRectMake(capInsets_.origin.x+capInsets_.size.width,t,w-(capInsets_.origin.x-l+capInsets_.size.width), capInsets_.origin.y-t));
	spriteBottomLeft_  = CCSprite::createWithTexture(texture, CCRectMake(l,capInsets_.origin.y+capInsets_.size.height, capInsets_.origin.x-l, h-(capInsets_.origin.y-t+capInsets_.size.height)) );
	spriteBottomRight_ = CCSprite::createWithTexture(texture, CCRectMake(capInsets_.origin.x+capInsets_.size.width, capInsets_.origin.y + capInsets_.size.height, w-(capInsets_.origin.x-l+capInsets_.size.width),h-(capInsets_.origin.y-t+capInsets_.size.height)));

	if(scaleMode_ ==eScale9Tile){
		static ccTexParams params_center = {GL_LINEAR,GL_LINEAR,GL_REPEAT ,GL_REPEAT};
		static ccTexParams params_h = {GL_LINEAR,GL_LINEAR,GL_REPEAT ,GL_LINEAR_MIPMAP_NEAREST};
		static ccTexParams params_v = {GL_LINEAR,GL_LINEAR,GL_LINEAR_MIPMAP_NEAREST,GL_REPEAT };

		static_cast<CCTexture2DBlock*>(spriteCentre_->getTexture())->setTexParameters(&params_center);
		static_cast<CCTexture2DBlock*>(spriteTop_->getTexture())->setTexParameters(&params_h);
		static_cast<CCTexture2DBlock*>(spriteBottom_->getTexture())->setTexParameters(&params_h);
		static_cast<CCTexture2DBlock*>(spriteLeft_->getTexture())->setTexParameters(&params_v);
		static_cast<CCTexture2DBlock*>(spriteRight_->getTexture())->setTexParameters(&params_v);
	}

	groupNode_->addChild(spriteCentre_ ,0 ,kCentre);
	groupNode_->addChild(spriteTop_, 1, kTop);
	groupNode_->addChild(spriteBottom_, 1, kBottom);
	groupNode_->addChild(spriteLeft_, 1, kLeft);
	groupNode_->addChild(spriteRight_, 1, kRight);

	groupNode_->addChild(spriteTopLeft_, 2, kTopLeft);
	groupNode_->addChild(spriteTopRight_, 2, kTopRight);
	groupNode_->addChild(spriteBottomLeft_, 2, kBottomLeft);
	groupNode_->addChild(spriteBottomRight_, 2, kBottomRight);

	setContentSize(spriteRect_.size);
	addChild(groupNode_);
	return true;
}

CCScale9SpriteEx* CCScale9SpriteEx::create( const char* file,ccScale9Mode mode/*=eScale9Strach*/, const CCRect* rect, const CCRect* capInsets )
{
	CCScale9SpriteEx* pReturn = new CCScale9SpriteEx();
	if ( pReturn && pReturn->initWithFile(file,mode, rect, capInsets) )
	{
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return NULL;
}

void CCScale9SpriteEx::setContentSize(const CCSize &size)
{
	CCNode::setContentSize(size);
	setAnchorPoint(ccp(0.5f,0.5f));

	float sizableWidth = size.width - spriteTopLeft_->getContentSize().width - spriteRight_->getContentSize().width;
	float sizableHeight = size.height - spriteTopLeft_->getContentSize().height - spriteBottomRight_->getContentSize().height;
	
	float horizontalScale = sizableWidth/spriteCentre_->getContentSize().width;
	float verticalScale = sizableHeight/spriteCentre_->getContentSize().height;
	float rescaledWidth = spriteCentre_->getContentSize().width * horizontalScale;
	float rescaledHeight = spriteCentre_->getContentSize().height * verticalScale;

	float despx = size.width*0.5f;
	float despy = size.height*0.5f;

	//Position corners
	spriteTopLeft_->setPosition(ccp(-rescaledWidth/2 - spriteTopLeft_->getContentSize().width/2 +despx, rescaledHeight/2 + spriteTopLeft_->getContentSize().height*0.5f +despy) );
	spriteTopRight_->setPosition(ccp(rescaledWidth/2 + spriteRight_->getContentSize().width/2 +despx, rescaledHeight/2 + spriteRight_->getContentSize().height*0.5f +despy));
	spriteBottomLeft_->setPosition(ccp(-rescaledWidth/2 - spriteBottomLeft_->getContentSize().width/2 +despx, -rescaledHeight/2 - spriteBottomLeft_->getContentSize().height*0.5f +despy));
	spriteBottomRight_->setPosition(ccp(rescaledWidth/2 + spriteBottomRight_->getContentSize().width/2 +despx, -rescaledHeight/2 + -spriteBottomRight_->getContentSize().height*0.5f +despy));

	if(scaleMode_==eScale9Strach){
		spriteCentre_->setScaleX(horizontalScale);
		spriteCentre_->setScaleY(verticalScale);
		spriteTop_->setScaleX(horizontalScale);
		spriteBottom_->setScaleX (horizontalScale);
		spriteLeft_->setScaleY (verticalScale);
		spriteRight_->setScaleY (verticalScale);
	} else if(scaleMode_==eScale9Tile){
		spriteTop_->setTextureRect(CCRectMake(0,0,rescaledWidth,spriteTopLeft_->getContentSize().height));
		spriteBottom_->setTextureRect(CCRectMake(0,0,rescaledWidth,spriteBottomLeft_->getContentSize().height));
		spriteLeft_->setTextureRect(CCRectMake(0,0,spriteTopLeft_->getContentSize().width,rescaledHeight));
		spriteRight_->setTextureRect(CCRectMake(0,0,spriteRight_->getContentSize().width,rescaledHeight));
		spriteCentre_->setTextureRect(CCRectMake(0,0,rescaledWidth,rescaledHeight));
	}

	spriteTop_->setPosition(ccp(0+despx,rescaledHeight/2 + spriteTopLeft_->getContentSize().height*0.5f +despy));	
	spriteBottom_->setPosition(ccp(0+despx,-rescaledHeight/2 - spriteBottomLeft_->getContentSize().height*0.5f +despy));	
	spriteLeft_->setPosition(ccp(-rescaledWidth/2 - spriteLeft_->getContentSize().width/2 +despx, 0+despy));
	spriteRight_->setPosition(ccp(rescaledWidth/2 + spriteRight_->getContentSize().width/2 +despx, 0+despy));
	spriteCentre_->setPosition(ccp(despx, despy));
}

void CCScale9SpriteEx::setOpacityModifyRGB( bool bValue )
{
	bIsOpacityModifyRGB_ = bValue;
	CCArray* children = groupNode_->getChildren();
	if (groupNode_ && children && children->count()) {
		CCObject* child;
		CCARRAY_FOREACH(children, child){
			CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);
			if (pNode){
				pNode->setOpacityModifyRGB(bIsOpacityModifyRGB_);
			}
		}
	}
}

//LabelBMFont - CCRGBAProtocol protocol
void CCScale9SpriteEx::setColor(const ccColor3B& color3)
{
    tColor_ = color3;
	CCArray* children = groupNode_->getChildren();
    if (children && children->count()) {
        CCObject* child;
        CCARRAY_FOREACH(children, child) {
            CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);        
            if (pNode){
                pNode->setColor(tColor_);
            }
        }
    }
}
const ccColor3B& CCScale9SpriteEx::getColor(void)
{
    return tColor_;
}

void CCScale9SpriteEx::setOpacity(GLubyte var)
{
    cOpacity_ = var;
    CCArray* children = groupNode_->getChildren();
    if (children && children->count()) {
        CCObject* child;
        CCARRAY_FOREACH(children, child) {
            CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);
            if (pNode){
                pNode->setOpacity(cOpacity_);
            }
        }
    }
}

/** sets the opacity.
 @warning If the the texture has premultiplied alpha then, the R, G and B channels will be modifed.
 Values goes from 0 to 255, where 255 means fully opaque.
 */
GLubyte CCScale9SpriteEx::getOpacity()
{
    return cOpacity_;
}


void CCScale9SpriteEx::setCapInsets(CCRect capInsets)
{
    capInsets_ = capInsets;
}

CCRect CCScale9SpriteEx::getCapInsets()
{
    return capInsets_;
}

CCScale9SpriteEx::CCScale9SpriteEx()
: scaleMode_(eScale9Strach)
, bIsOpacityModifyRGB_(false)
, groupNode_(NULL)
, spriteTopLeft_(NULL)
, spriteTop_(NULL)
, spriteTopRight_(NULL)
, spriteLeft_(NULL)
, spriteCentre_(NULL)
, spriteRight_(NULL)
, spriteBottomLeft_(NULL)
, spriteBottom_(NULL)
, spriteBottomRight_(NULL)
{
}

CCScale9SpriteEx::~CCScale9SpriteEx()
{
	if(groupNode_) {
		groupNode_->removeAllChildrenWithCleanup(true);
	}
}

void CCScale9SpriteEx::removeAllChildrenWithCleanup( bool doCleanup )
{
	CCNode::removeAllChildrenWithCleanup(doCleanup);
	groupNode_->removeAllChildrenWithCleanup(doCleanup);
}
