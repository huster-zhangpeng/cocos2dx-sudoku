/*
 * BackgroundLayer.cpp
 *
 *  Created on: 2013-11-20
 *      Author: zp
 */

#include "BackgroundLayer.h"

bool BackgroundLayer::init() {
	if (!CCLayer::init()) {
		return false;
	}

	CCLog("create background");
	_background = CCSprite::create("background.jpg");
	_background->setPosition(ccp(240, 400));
	this->addChild(_background);

	return true;
}

