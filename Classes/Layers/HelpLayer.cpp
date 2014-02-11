/*
 * HelpLayer.cpp
 *
 *  Created on: 2013-12-12
 *      Author: zp
 */

#include "HelpLayer.h"
#include "../Scenes/MainMenuScene.h"

bool HelpLayer::init() {
	if(!CCLayer::init()) {
		return false;
	}

	CCLayer * containerlayer = CCLayer::create();

	char buffer[20];
	for(int i = 0; i < 2; i++) {
		sprintf(buffer, "help/%d.jpg", i);
		CCSprite * sprite = CCSprite::create(buffer);
		sprite->setPosition(ccp(240 + i * 480, 400));
		containerlayer->addChild(sprite);
	}

	containerlayer->setContentSize(CCSizeMake(960, 800));
	scrollView = CCScrollView::create();
	scrollView->setContainer(containerlayer);
	scrollView->setPosition(CCPointZero);
	scrollView->setViewSize(CCSizeMake(480, 800));
	scrollView->setContentSize(CCSizeMake(960, 800));
	scrollView->setTouchEnabled(true);
	scrollView->setTouchPriority(1);
	scrollView->setDelegate(this);
	scrollView->setDirection(kCCScrollViewDirectionHorizontal);

	_lastOffset = scrollView->getContentOffset().x;
	CCLog("offset %f", _lastOffset);

	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);
	this->addChild(scrollView);

	return true;
}

void HelpLayer::scrollViewDidScroll(CCScrollView* view){
}

void HelpLayer::scrollViewDidZoom(CCScrollView* view){
}

#define ADJUST_ANIM_VELOCITY 200.0

void HelpLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
	this->unscheduleAllSelectors();

	float x = scrollView->getContentOffset().x;
	CCLog("offset: %f", x);
	if(x < _lastOffset) {
		if(_lastOffset == -1440) {
			back();
			return;
		}
		_lastOffset = _lastOffset - 480.0;
	} else {
		if(_lastOffset != 0) {
			_lastOffset = _lastOffset + 480.0;
		}
	}

	scrollView->setContentOffset(ccp(x - _lastOffset, 0), false);
//	scrollView->setContentOffsetInDuration(ccp(x, 0), 0.3);
	CCLog("x = %f, last offset = %f, cur = %f", x,  _lastOffset, scrollView->getContentOffset().x);
}

void HelpLayer::keyBackClicked() {
	back();
}

void HelpLayer::back() {
	CCScene * newScene = MainMenu::scene();

	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene * transition = CCTransitionPageTurn::create(0.8, newScene,
			true);
	CCDirector::sharedDirector()->replaceScene(transition);
}

