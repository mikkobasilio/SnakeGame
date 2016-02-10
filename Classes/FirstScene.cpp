#include "pch.h"
#include "FirstScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;
using namespace std;
int w, h, j, k;
Scene* FirstScene::createScene() 
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool FirstScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	w = visibleSize.width;
	h = visibleSize.height;
	j = w / 2 + origin.x;
	k = h / 2 + origin.y;
	Label* start = Label::createWithSystemFont("The Human Centipede", "Arial", 36);
	start->setPosition(j, 2);
	Label* label = Label::createWithSystemFont("Press ANY KEY to Start", "Arial", 24);
	label->setPosition(j, k);
	this->addChild(label);
	this->addChild(start);

	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
		auto director = Director::getInstance();
		auto scene = HelloWorld::createScene();
		director->replaceScene(scene);
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, label);

}