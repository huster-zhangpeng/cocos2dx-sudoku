/*
 * BoardLayer.cpp
 *
 *  Created on: 2013-11-22
 *      Author: zp
 */

#include "BoardLayer.h"

bool BoardLayer::init(){
	if(! CCLayer::init()){
		return false;
	}

	_board = CCSprite::create("bg.png");
	_board->setPosition(ccp(28 + 212, 800 - 292 - 210));
	this->addChild(_board);

	return true;
}


