/*
 * ChooseLayer.cpp
 *
 *  Created on: 2013-11-23
 *      Author: zp
 */

#include "ChooseLayer.h"
#include "../Scenes/MainMenuScene.h"
#include "../Scenes/GameScene.h"

ChooseLayer::~ChooseLayer() {
	CC_SAFE_RELEASE(_levelButtons);
}

bool ChooseLayer::init() {
	if (!CCLayer::init()) {
		return false;
	}

	CCSprite * label = CCSprite::create("casual_mode.png");
	label->setPosition(ccp(158 + 82.5, 800 - 133 - 19));
	this->addChild(label);

	CCSprite * triRope = CCSprite::create("triRope.png");
	triRope->setPosition(ccp(139 + 103, 800 - 186 - 28));
	this->addChild(triRope);

	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create(
			"straightRope.png");
	int SRX[2] = { 137, 328 };
	int SRY[3] = { 276, 384, 492 };
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 3; y++) {
			CCSprite * rope = CCSprite::createWithTexture(
					batchNode->getTexture());
			rope->setPosition(ccp(SRX[x] + 7, 800 - 35 - SRY[y]));
			this->addChild(rope);
		}
	}

	_back = CCSprite::create("back.png");
	_back->setPosition(ccp(24 + 40, 800 - 56.5 + 15));
	this->addChild(_back);
	_resume = CCSprite::create("c_resume.png");
	_resume->setPosition(ccp(310 + 103 - 17.5, 800 - 48 - 41));
	this->addChild(_resume);

	_levelButtons = CCArray::createWithCapacity(4);
	_levelButtons->retain();
	const char * levelFileName[] = { "level/c_easy.png", "level/c_normal.png",
			"level/c_hard.png", "level/c_expert.png" };
	for (int i = 0; i < 4; i++) {
		CCSprite * button = CCSprite::create(levelFileName[i]);
		button->setPosition(ccp(97 + 143.5, 800 - 226 - i * 108 - 43.5));
		this->addChild(button);
		_levelButtons->addObject(button);
	}

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	return true;
}

void ChooseLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
	CCSetIterator i;
	CCTouch * touch;
	CCPoint tap;

	for (i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch *) (*i);

		if (touch) {
			tap = touch->getLocation();

			if (_back->boundingBox().containsPoint(tap)) {
				_back->setPositionY(800 - 56.5);
			}
			if (_resume->boundingBox().containsPoint(tap)) {
				_resume->setPositionX(276 + 103);
			}

			for (unsigned b = 0; b < _levelButtons->count(); b++) {
				CCSprite* button = (CCSprite*) _levelButtons->objectAtIndex(b);
				if (button->boundingBox().containsPoint(tap)) {
					button->setScale(1.1f);
				}
			}
		}
	}
}

void ChooseLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event) {
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
				_back->setPositionY(800 - 56.5 + 15);
			}
			if (_resume->boundingBox().containsPoint(tap)) {
				_resume->setPositionX(276 + 103);
			} else {
				_resume->setPositionX(310 + 103 - 17.5);
			}

			for (unsigned b = 0; b < _levelButtons->count(); b++) {
				CCSprite* button = (CCSprite*) _levelButtons->objectAtIndex(b);
				if (button->boundingBox().containsPoint(tap)) {
					button->setScale(1.1f);
				} else {
					button->setScale(1.0f);
				}
			}
		}
	}
}

void ChooseLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
	CCSetIterator i;
	CCTouch * touch;
	CCPoint tap;

	for (i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch *) (*i);

		if (touch) {
			tap = touch->getLocation();

			if (_back->boundingBox().containsPoint(tap)) {
				back();
			}
			_back->setPositionY(800 - 56.5 + 15);
			if (_resume->boundingBox().containsPoint(tap)) {
				gotoGame();
			}
			_resume->setPositionX(310 + 103 - 17.5);

			for (unsigned b = 0; b < _levelButtons->count(); b++) {
				CCSprite* button = (CCSprite*) _levelButtons->objectAtIndex(b);
				if (button->boundingBox().containsPoint(tap)) {
					gotoGame();
				}
				button->setScale(1.0f);
			}
		}
	}
}

void ChooseLayer::keyBackClicked() {
	back();
}

void ChooseLayer::back() {
	CCScene * newScene = MainMenu::scene();

	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene * transition = CCTransitionPageTurn::create(0.8, newScene, true);
	CCDirector::sharedDirector()->replaceScene(transition);
}

void ChooseLayer::gotoGame() {
	CCScene * newScene = GameScene::scene();

	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene * transition = CCTransitionPageTurn::create(0.8, newScene, false);
	CCDirector::sharedDirector()->replaceScene(transition);
}
