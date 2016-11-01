#include "L8_ShaderSprite.h"


L8_ShaderSprite* L8_ShaderSprite::create(const char *pszFileName) {
	auto pRet = new (std::nothrow) L8_ShaderSprite();
	if (pRet && pRet->initWithFile(pszFileName)) {
		pRet->autorelease();
	}
	else {
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

bool L8_ShaderSprite::initWithTexture(Texture2D* texture, const Rect& rect) {
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

void L8_ShaderSprite::initGLProgram()
{
	auto program = new GLProgram();
	//program->initWithFilenames("L8_Water/vertex.shader", "L8_Water/wave1.fsh");
	//program->initWithFilenames("L8_Water/vertex.shader", "L8_Water/wave2.fsh");
	program->initWithFilenames("L8_Water/vertex.shader", "L8_Water/fragment.shader");
	program->link();
	program->updateUniforms();
	program->autorelease();

	this->setGLProgram(program);


	auto normalMapTextrue = TextureCache::getInstance()->addImage("L8_Water/water_normal.png");
	Texture2D::TexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	normalMapTextrue->setTexParameters(texParams);

	getGLProgramState()->setUniformTexture("u_normalMap", normalMapTextrue);
}