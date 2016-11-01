#include "L7_ShaderSprite.h"


L7_ShaderSprite* L7_ShaderSprite::create(const char *pszFileName) {
	auto pRet = new (std::nothrow) L7_ShaderSprite();
	if (pRet && pRet->initWithFile(pszFileName)) {
		pRet->autorelease();
	}
	else {
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

bool L7_ShaderSprite::initWithTexture(Texture2D* texture, const Rect& rect) {
	if (Sprite::initWithTexture(texture, rect)) {
#if CC_ENABLE_CACHE_TEXTURE_DATA
		auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event) {
			setGLProgram(nullptr);
			initGLProgram();
		});

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
		initGLProgram();
		return true;
	}

	return false;
}

void L7_ShaderSprite::initGLProgram()
{
	auto program = new GLProgram();
	program->initWithFilenames("L7_Water/vertex.shader", "L7_Water/fragment.shader");
	program->link();
	program->updateUniforms();
	program->autorelease();

	this->setGLProgram(program);
}