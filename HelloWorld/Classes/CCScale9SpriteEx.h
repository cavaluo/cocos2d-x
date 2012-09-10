#ifndef CCSCALE9SPRITE_EX_H__
#define CCSCALE9SPRITE_EX_H__

#include "base_nodes/CCNode.h"
#include "CCProtocols.h"
namespace cocos2d { class CCSprite; }
namespace cocos2d { class CCNode; }

typedef enum {
	kCentre = 0,
	kTop,
	kLeft,
	kRight,
	kBottom,
	kTopRight,
	kTopLeft,
	kBottomRight,
	kBottomLeft
} ccScale9Position;

typedef enum 
{
	eScale9Strach = 0,
	eScale9Tile
} ccScale9Mode;

USING_NS_CC;

class CCScale9SpriteEx:public CCNode,public CCRGBAProtocol
{
private:
	ccScale9Mode scaleMode_;
	bool bIsOpacityModifyRGB_;
	CCNode* groupNode_;
	// 九宫格精灵
	CCSprite* spriteTopLeft_;
	CCSprite* spriteTop_;
	CCSprite* spriteTopRight_;
	CCSprite* spriteLeft_;
	CCSprite* spriteCentre_;
	CCSprite* spriteRight_;
	CCSprite* spriteBottomLeft_;
	CCSprite* spriteBottom_;
	CCSprite* spriteBottomRight_;

	CCRect spriteRect_;

	// 上下左右中心位置的纹理矩形区域
	CCRect textureRectCenter_;
	CCRect textureRectLeft_;
	CCRect textureRectRight_;
	CCRect textureRectTop_;
	CCRect textureRectBottom_;
	//根据给定的中心点size产生并校验九宫格上下左右中心部分的纹理宽度
	void generateTextureRect(const CCRect& texture_rect,const CCRect& center_rect);

public:
	CCScale9SpriteEx();
	~CCScale9SpriteEx();
	virtual void removeAllChildrenWithCleanup(bool doCleanup);

	// 初始化方法
	virtual bool initWithFile(const char* file,ccScale9Mode mode=eScale9Strach, const CCRect* rect= NULL, const CCRect* capInsets = NULL);
	static CCScale9SpriteEx* create(const char* file,ccScale9Mode mode=eScale9Strach, const CCRect* rect=NULL, const CCRect* capInsets = NULL);
	void setContentSize(const CCSize &size);
	virtual void setOpacityModifyRGB(bool bValue);
	virtual bool isOpacityModifyRGB(){return bIsOpacityModifyRGB_;}

	CC_SYNTHESIZE(CCSize, originalSize_, OriginalSize);;
	CC_SYNTHESIZE(CCSize, preferredSize_, PreferredSize);
	// Opacity: conforms to CCRGBAProtocol protocol
	CC_PROPERTY(GLubyte, cOpacity_, Opacity);
	// Color: conforms to CCRGBAProtocol protocol
	CC_PROPERTY_PASS_BY_REF(ccColor3B, tColor_, Color);
	CC_PROPERTY(CCRect, capInsets_, CapInsets);
};

#endif
