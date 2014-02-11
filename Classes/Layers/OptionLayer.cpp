/*
 * OptionLayer.cpp
 *
 *  Created on: 2013-11-25
 *      Author: zp
 */

#include "OptionLayer.h"
#include "../Scenes/MainMenuScene.h"
#include "../World/Settings.h"

OptionLayer::~OptionLayer(){
	CC_SAFE_RELEASE(_switchButtons);
}

bool OptionLayer::init() {
	if (!CCLayer::init()) {
		return false;
	}

	_back = CCSprite::create("back.png");
	_back->setPosition(ccp(24 + 40, 800 - 56.5 + 15));
	this->addChild(_back);

	CCSprite * mode = CCSprite::create("mode.png");
	mode->setPosition(ccp(132 + 111, 800 - 103 - 19.5));
	this->addChild(mode);

	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("dotted_line.png");
	int dottedLineY[3] = {313, 420, 539};
	for (int i = 0; i < 3; i++) {
		CCSprite * dotLine = CCSprite::createWithTexture(batchNode->getTexture());
		dotLine->setPosition(ccp(27 + 210.5, 800 - dottedLineY[i] - 1.5));
		this->addChild(dotLine);
	}

	_switchIndex = -1;
	_switches[0] = &Settings::showConflictedDigit;
	_switches[1] = &Settings::musicEnabled;
	_switches[2] = &Settings::soundEnabled;
	_switches[3] = &Settings::preventSleeping;
	_switches[4] = &Settings::showTimer;
	_switches[5] = &Settings::autoHighLight;
	_switches[6] = &Settings::autoRemoveNotes;
	_switches[7] = &Settings::removeCompleteDigits;

	CCSpriteBatchNode* maskBatchNode = CCSpriteBatchNode::create("mask.png");
	CCSpriteBatchNode* switchBatch = CCSpriteBatchNode::create("switch.png");
	_switchButtons = CCArray::createWithCapacity(7);
	_switchButtons->retain();
	char opLabel[10];
	int opLabelY[8] = {271, 332, 379, 445, 492, 566, 612, 657};
	for(int i = 0; i < 8; i++) {
		sprintf(opLabel, "op%d.png", i);
		CCSprite * label = CCSprite::create(opLabel);
		label->setPosition(ccp(25 + label->boundingBox().size.width / 2,
				800 - opLabelY[i] - label->boundingBox().size.height / 2));
		this->addChild(label);

		CCSprite * stencil = CCSprite::createWithTexture(maskBatchNode->getTexture());
		stencil->setPosition(ccp(380 + 39, 800 - opLabelY[i] - label->boundingBox().size.height / 2));
		CCClippingNode * cliper = CCClippingNode::create(stencil);
		cliper->setAlphaThreshold(0);
		CCSprite * switchButton = CCSprite::createWithTexture(switchBatch->getTexture());
		switchButton->setPosition(ccp(*(_switches[i]) ? 394 + 49 : 394, 800 - opLabelY[i] - label->boundingBox().size.height / 2));
		_switchButtons->addObject(switchButton);
		cliper->addChild(switchButton);
		this->addChild(cliper);
	}

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	return true;
}

void OptionLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
	CCSetIterator i;
	CCTouch * touch;
	CCPoint tap;

	for (i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch *) (*i);

		if (touch) {
			tap = touch->getLocation();

			if (_back->boundingBox().containsPoint(tap)) {
				_back->setPositionY(800 - 56.5);
			} else {
				for(int i = 0; i < 7; i++) {
					CCSprite * button = (CCSprite *)_switchButtons->objectAtIndex(i);
					if(button->boundingBox().containsPoint(tap)) {
						_switchIndex = i;
						_tapX = tap.x;
						break;
					}
				}
			}
		}
	}
}

void OptionLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event) {
	CCSetIterator i;
	CCTouch * touch;
	CCPoint tap;

	for (i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch *) (*i);

		if (touch) {
			tap = touch->getLocation();
			if(_switchIndex >= 0) {
				CCSprite * button = (CCSprite *)_switchButtons->objectAtIndex(_switchIndex);
				float displacement = tap.x - _tapX;
				_tapX = tap.x;
				float x = button->getPositionX() + displacement;
				if(x > 394 + 49) {
					x = _tapX = 394 + 49;
				} else if(x < 393) {
					x = _tapX = 394;
				}
				button->setPositionX(x);
			} else {
				if (_back->boundingBox().containsPoint(tap)) {
					_back->setPositionY(800 - 56.5);
				} else {
					_back->setPositionY(800 - 56.5 + 15);
				}
			}
		}
	}
}

void OptionLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
	CCSetIterator i;
	CCTouch * touch;
	CCPoint tap;

	for (i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch *) (*i);

		if (touch) {
			tap = touch->getLocation();
			if(_switchIndex >= 0) {
				CCSprite * button = (CCSprite *)_switchButtons->objectAtIndex(_switchIndex);
				float x = button->getPositionX();
				if(x > 393 + 24) {
					x = _tapX = 394 + 49;
					*(_switches[_switchIndex]) = true;
				} else {
					x = _tapX = 394;
					*(_switches[_switchIndex]) = false;
				}
				button->setPositionX(x);
				_switchIndex = -1;
			} else {
				if (_back->boundingBox().containsPoint(tap)) {
					back();
				}
				_back->setPositionY(800 - 56.5 + 15);
			}
		}
	}
}

void OptionLayer::keyBackClicked() {
	back();
}

void OptionLayer::back() {
	CCScene * newScene = MainMenu::scene();

	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene * transition = CCTransitionPageTurn::create(0.8, newScene, true);
	CCDirector::sharedDirector()->replaceScene(transition);
}
