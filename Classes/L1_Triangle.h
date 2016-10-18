#pragma once

#include "cocos2d.h"
USING_NS_CC;

class L1_Triangle : public cocos2d::Layer
{
public:
    virtual bool init();

	virtual void visit(Renderer* render, const Mat4& parentTransform, uint32_t parentFlags) override;

	void onDraw();

	void update(float delta);

    CREATE_FUNC(L1_Triangle);

private:
	CustomCommand _command;
};
