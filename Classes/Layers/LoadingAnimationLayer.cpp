/*
 * LoadingAnimationLayer.cpp
 *
 *  Created on: 2013-11-22
 *      Author: zp
 */

#include "LoadingAnimationLayer.h"
#include "../Scenes/MainMenuScene.h"

LoadingAnimation::~LoadingAnimation(){
	CC_SAFE_RELEASE(_dots);
}

bool LoadingAnimation::init() {
	if(!CCLayer::init()) {
		return false;
	}

	_loading = CCSprite::create("loading.png");
	_loading->setPosition(ccp(160 + 80, 800 - 482 - 19));
	this->addChild(_loading);

	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("dot.png");
	_dots = CCArray::createWithCapacity(3);
	_dots->retain();

	for(int i = 0; i < 3; i++) {
		CCSprite * dot = CCSprite::createWithTexture(batchNode->getTexture());
		dot->setPosition(ccp(308 + 10 + i * 10, 800 - 499 - 10));
		this->addChild(dot);
		_dots->addObject(dot);
	}

	_counter = 0;
	this->schedule(schedule_selector(LoadingAnimation::update));
	this->schedule(schedule_selector(LoadingAnimation::changeToMainMenuScene), 0, 0, 5);

	return true;
}

void LoadingAnimation::update(float dt) {
	_time += dt;
	if(_time > 0.5) {
		_time = 0;
		_counter = (_counter + 1 ) % 4;
	}

	CCSprite * dot;
	for(int i = 0; i < 3; i++) {
		dot = (CCSprite *) _dots->objectAtIndex(i);
		if(i < _counter) {
			dot->setVisible(true);
		} else {
			dot->setVisible(false);
		}
	}
}

void LoadingAnimation::changeToMainMenuScene(float dt) {
	CCScene * newScene = MainMenu::scene();

	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene * transition = CCTransitionPageTurn::create(0.8, newScene, false);
	CCDirector::sharedDirector()->replaceScene(transition);
}


