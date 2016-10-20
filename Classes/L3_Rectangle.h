#pragma once

#include "cocos2d.h"
USING_NS_CC;

struct Vertex
{
	float position[2];
	float color[4];
};

class L3_Rectangle : public cocos2d::Layer
{
private:
	//float _vertercies[8];
	//float _color[16];
	Vertex _data[4];

	uint32_t _vao;
	uint32_t _vbo;

	bool _scale;
public:
	virtual bool init();

	virtual void visit(Renderer* render, const Mat4& parentTransform, uint32_t parentFlags) override;

	void onDraw();

	void update(float delta);

	CREATE_FUNC(L3_Rectangle);

private:
	CustomCommand _command;
};
