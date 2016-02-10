#include "HelloWorldScene.h"
#include "MenuScene.h"
#include "stdlib.h"
USING_NS_CC;
using namespace std;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Set an image to a texture, set the param "repeat"
	Texture2D *bgTexture = Director::getInstance()->getTextureCache()->addImage("tile2.png");
	const Texture2D::TexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };

	// use the texture as Sprite
	Sprite *background = Sprite::createWithTexture(bgTexture, Rect(0, 0, visibleSize.width, visibleSize.height));
	background->getTexture()->setTexParameters(&tp);
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background, 1);

	//Create wall texture
	Texture2D *wallTexture = Director::getInstance()->getTextureCache()->addImage("tile3.png");
	// use the texture as Sprite
	wall = Sprite::createWithTexture(wallTexture, Rect(0, 0, 32, visibleSize.height));
	wall2 = Sprite::createWithTexture(wallTexture, Rect(0, 0, 32, visibleSize.height));
	wall3 = Sprite::createWithTexture(wallTexture, Rect(0, 0, visibleSize.width, 32));
	wall4 = Sprite::createWithTexture(wallTexture, Rect(0, 0, visibleSize.width, 32));
	wall->getTexture()->setTexParameters(&tp);

	wall->setPosition(Vec2(visibleSize.width - 16, visibleSize.height / 2));
	this->addChild(wall, 300);
	wall2->setPosition(Vec2(16, visibleSize.height / 2));
	this->addChild(wall2, 300);

	wall3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 16));
	this->addChild(wall3, 300);
	wall4->setPosition(Vec2(visibleSize.width / 2, 16));
	this->addChild(wall4, 300);

	snake = new Snake(this);
	food = new Food();
	food->SpawnFood(this, snake);
	snekduler = schedule_selector(HelloWorld::move);
	restarting = schedule_selector(HelloWorld::restart);
	gamespeed = .15;
	this->schedule(snekduler, gamespeed);
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if (snake->chkReady() == true) { snake->changeDir(keyCode); snake->ready(false); }
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	return true;
}

void HelloWorld::restart(float delta) {
	auto newScene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.5, newScene, Color3B(255, 255, 255)));
}

void HelloWorld::move(float delta) {
	snake->ready(false);
	snake->move();
	if (snake->checkHit(snake->getHead()) || snake->checkHeadHit(wall)
		|| snake->checkHeadHit(wall2) || snake->checkHeadHit(wall3)
		|| snake->checkHeadHit(wall4)) {
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->playEffect("dead2.wav", false, 1.0f, 1.0f, 0.005f);
		if (isScheduled(snekduler)) {
			unschedule(snekduler);
			this->schedule(restarting, 2.0f);

		};
	}
	if (snake->checkHeadSame(food->getSprite())) {
		if (isScheduled(snekduler)) {
			unschedule(snekduler);
			auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
			audio->playEffect("pickup2.wav", false, 1.0f, 1.0f, 0.005f);
			delete food;
			food = new Food();
			food->SpawnFood(this, snake);
			snake->grow(this);
			gamespeed -= 0.005;
			if (gamespeed <= 0.05) gamespeed = 0.05;
			this->schedule(snekduler, gamespeed);
		};
	}

	snake->ready(true);
}