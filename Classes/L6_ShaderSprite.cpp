#include "L6_ShaderSprite.h"


L6_ShaderSprite* L6_ShaderSprite::create(const char *pszFileName) {
	auto pRet = new (std::nothrow) L6_ShaderSprite();
	if (pRet && pRet->initWithFile(pszFileName)) {
		pRet->autorelease();
	}
	else {
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

bool L6_ShaderSprite::initWithTexture(Texture2D* texture, const Rect& rect) {
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

void L6_ShaderSprite::initGLProgram()
{
	auto program = new GLProgram();
	program->initWithFilenames("L6_Water/vertex.shader", "L6_Water/fragment.shader");
	program->link();
	program->updateUniforms();
	program->autorelease();

	this->setGLProgram(program);


	auto normalMapTextrue = TextureCache::getInstance()->addImage("L6_Water/water_normal.png");
	Texture2D::TexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	normalMapTextrue->setTexParameters(texParams);
	getGLProgramState()->setUniformTexture("u_normalMap", normalMapTextrue);


	auto waveTextrue = TextureCache::getInstance()->addImage("L6_Water/hailang_ceshi01.jpg");
	waveTextrue->setTexParameters(texParams);
	getGLProgramState()->setUniformTexture("u_WaveFlowerMask1", waveTextrue);

	auto waveTextrue1 = TextureCache::getInstance()->addImage("L6_Water/hailang_ceshi02.jpg");
	waveTextrue1->setTexParameters(texParams);
	getGLProgramState()->setUniformTexture("u_WaveFlowerMask2", waveTextrue1);

	getGLProgramState()->setUniformInt("u_pause", 0);

}