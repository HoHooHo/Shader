#pragma once

#include "cocos2d.h"
USING_NS_CC;

struct Vertex3D
{
	float position[3];
	float color[4];
};

class L4_Cube : public cocos2d::Layer
{
private:
	uint32_t _vao;
	uint32_t _vbo;

public:
	virtual bool init();

	virtual void visit(Renderer* render, const Mat4& parentTransform, uint32_t parentFlags) override;

	void onDraw();

	CREATE_FUNC(L4_Cube);

private:
	CustomCommand _command;
};
