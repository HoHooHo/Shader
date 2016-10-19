#pragma once

#include "cocos2d.h"
USING_NS_CC;

class L2_Triangle : public cocos2d::Layer
{
private:
	float _vertercies[6];
	float _color[12];

	uint32_t _vao;
	uint32_t _vbo;
public:
    virtual bool init();

	virtual void visit(Renderer* render, const Mat4& parentTransform, uint32_t parentFlags) override;

	void onDraw();

	void update(float delta);

    CREATE_FUNC(L2_Triangle);

private:
	CustomCommand _command;
};
