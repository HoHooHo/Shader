#pragma once

#include "cocos2d.h"
USING_NS_CC;

class L7_ShaderSprite : public cocos2d::Sprite
{
public:
	bool initWithTexture(Texture2D* texture, const Rect&  rect);
	void initGLProgram();

	static L7_ShaderSprite* create(const char* pszFileName);

};
