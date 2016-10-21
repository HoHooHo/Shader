#pragma once

#include "cocos2d.h"
USING_NS_CC;

struct Vertex3D_Tex
{
	float position[3];
	float color[4];
	float texCoord[2];
};

class L5_Cube_Textrue : public cocos2d::Layer
{
private:
	uint32_t _vao;
	uint32_t _vbo;

	GLuint _textureId;
public:
	virtual bool init();

	virtual void visit(Renderer* render, const Mat4& parentTransform, uint32_t parentFlags) override;

	void onDraw();

	CREATE_FUNC(L5_Cube_Textrue);

private:
	CustomCommand _command;
};
