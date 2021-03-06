#include "Controler.h"
#include "ui/CocosGUI.h"

#include "HelloWorldScene.h"
#include "L1_Triangle.h"
#include "L2_Triangle.h"
#include "L3_Rectangle.h"
#include "L4_Cube.h"
#include "L5_Cube_Textrue.h"
#include "L6_ShaderSprite.h"
#include "L7_ShaderSprite.h"
#include "L8_ShaderSprite.h"

USING_NS_CC;


typedef struct _Controller{
	const char *test_name;
	std::function<Node*()> callback;
} controler;
controler g_aTestNames[] = {
	{"HelloWorld", [](){auto layer = HelloWorld::create(); layer->retain(); return layer;}},
	{"L1_Triangle", [](){auto layer = L1_Triangle::create(); layer->retain(); return layer;}},
	{"L2_Triangle", [](){auto layer = L2_Triangle::create(); layer->retain(); return layer;}},
	{"L3_Rectangle", [](){auto layer = L3_Rectangle::create(); layer->retain(); return layer;}},
	{"L4_Cube", [](){auto layer = L4_Cube::create(); layer->retain(); return layer;}},
	{"L5_Cube_Textrue", [](){auto layer = L5_Cube_Textrue::create(); layer->retain(); return layer;}},
	{"L6_ShaderSprite", [](){auto layer = L6_ShaderSprite::create("L6_Water/fight_sea.jpg"); layer->setPosition(480, 320); layer->retain(); return layer;}},
	{"L7_ShaderSprite", [](){auto layer = L7_ShaderSprite::create("HelloWorld.png"); layer->setPosition(480, 320); layer->retain(); return layer;}},
	{"L8_ShaderSprite", [](){auto layer = L8_ShaderSprite::create("HelloWorld.png"); layer->setPosition(480, 320); layer->retain(); return layer;}},
};

static int g_testCount = sizeof(g_aTestNames) / sizeof(g_aTestNames[0]);

Scene* Controler::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = Controler::create();

    //// add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Controler::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	initControler();
    
    return true;
}

void Controler::initControler(){
	Size visibleSize = Director::getInstance()->getVisibleSize();

	ui::ListView* listView = ui::ListView::create();
	listView->setDirection(ui::ScrollView::Direction::VERTICAL);
	listView->setBounceEnabled(true);
	listView->setBackGroundImage("green_edit.png");
	listView->setBackGroundImageScale9Enabled(true);
	listView->setContentSize(visibleSize);
	listView->setPosition(Vec2(0, 0));

	this->addChild(listView);

	for (int i = 0; i < g_testCount; i++)
	{
		ui::Layout *custom_item = ui::Layout::create();
		custom_item->setContentSize(Size(visibleSize.width, 50));

		auto menuItem = MenuItemFont::create(g_aTestNames[i].test_name, [&](void* sender){
			auto item = static_cast<MenuItem *>(sender);

			this->removeAllChildren();
			auto layer = g_aTestNames[item->getTag() - 1000].callback();

			this->addChild(layer);
			layer->release();
			this->addChild(this->initMenuItem());
		});

		menuItem->setTag(1000 + i);

		auto menu = Menu::create(menuItem, NULL);
		menu->setPosition(visibleSize.width/2, 25);
		custom_item->addChild(menu);


		listView->addChild(custom_item);

	}
}


Menu* Controler::initMenuItem(){
	auto menuItem = MenuItemFont::create("MainMenu", CC_CALLBACK_1(Controler::onCallback, this));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	menuItem->setPosition(Vec2(origin.x + visibleSize.width - menuItem->getContentSize().width/2, menuItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(Vec2::ZERO);

	return menu;
}

void Controler::onCallback(Ref* pSender){
	this->removeAllChildren();
	initControler();
}
