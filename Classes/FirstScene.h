#pragma once
#include "cocos2d.h"
using namespace std;
class FirstScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};

