/*
 * PatternLayer.cpp
 *
 *  Created on: 2013-11-25
 *      Author: zp
 */

#include "PatternLayer.h"

bool PatternLayer::init() {
	if(!CCLayer::init()) {
		return false;
	}

	_pattern = CCSprite::create("pattern.png");
	_pattern->setPosition(ccp(51 + 188, 800 - 212 - 193.5));
	_pattern->setScale(0.8f);
	_pattern->setOpacity(0x4E);
	this->addChild(_pattern);

	return true;
}


