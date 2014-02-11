/*
 * MainMenuLayer.cpp
 *
 *  Created on: 2013-11-22
 *      Author: zp
 */

#include "MainMenuLayer.h"
#include "../Scenes/ChooseScene.h"
#include "../Scenes/OptionScene.h"
#include "../Scenes/StatsScene.h"
#include "../Scenes/HelpScene.h"

MainMenuLayer::~MainMenuLayer() {
	CC_SAFE_RELEASE(_slideButtons);
	CC_SAFE_RELEASE(_zoomButtons);
}

bool MainMenuLayer::init() {
	if (!CCLayer::init())
		return false;

	_help = CCSprite::create("op_help.png");
	_help->setPosition(ccp(372 + 40, 800 - 56.5 + 15));
	this->addChild(_help);
	_rate = CCSprite::create("rate.png");
	_rate->setPosition(ccp(287 + 40, 800 - 56.5 + 15));
	this->addChild(_rate);

	CCSprite * triRope = CCSprite::create("triRope.png");
	triRope->setPosition(ccp(139 + 103, 800 - 297 - 28));
	this->addChild(triRope);

	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create(
			"straightRope.png");
	int SRX[2] = { 137, 328 };
	int SRY[3] = { 385, 475, 565 };
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 3; y++) {
			CCSprite * rope = CCSprite::createWithTexture(
					batchNode->getTexture());
			rope->setPosition(ccp(SRX[x] + 7, 800 - 35 - SRY[y]));
			this->addChild(rope);
		}
	}

	int BY[4] = { 333, 426, 519, 612 };
	const char * buttonFilenames[4] = { "play.png", "options.png", "stats.png",
			"more_game.png" };
	_zoomButtons = CCArray::createWithCapacity(4);
	_zoomButtons->retain();
	for (int i = 0; i < 4; i++) {
		CCSprite * button = CCSprite::create(buttonFilenames[i]);
		button->setPosition(ccp(104 + 143, 800 - BY[i] - 43));
		button->setScale(0.95f);
		this->addChild(button);
		_zoomButtons->addObject(button);
	}

	_slideButtons = CCArray::create(_help, _rate, NULL);
	_slideButtons->retain();

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	_gotoActionOfSlideButtons[0] = gotoHelpScene;
	_gotoActionOfSlideButtons[1] = gotoRate;

	_gotoActionOfZoomButtons[0] = gotoChooseScene;
	_gotoActionOfZoomButtons[1] = gotoOptionsScene;
	_gotoActionOfZoomButtons[2] = gotoStatsScene;
	_gotoActionOfZoomButtons[3] = gotoMoreGames;

	return true;
}

void MainMenuLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
	CCSetIterator i;
	CCTouch * touch;
	CCPoint tap;

	for (i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch *) (*i);

		if (touch) {
			tap = touch->getLocation();

			for (unsigned b = 0; b < _slideButtons->count(); b++) {
				CCSprite* button = (CCSprite*) _slideButtons->objectAtIndex(b);
				if (button->boundingBox().containsPoint(tap)) {
					button->setPositionY(800 - 56.5);
				}
			}

			for (unsigned b = 0; b < _zoomButtons->count(); b++) {
				CCSprite* button = (CCSprite*) _zoomButtons->objectAtIndex(b);
				if (button->boundingBox().containsPoint(tap)) {
					button->setScale(1.05f);
				}
			}
		}
	}
}

void MainMenuLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event) {
	CCSetIterator i;
	CCTouch * touch;
	CCPoint tap;

	for (i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch *) (*i);

		if (touch) {
			tap = touch->getLocation();

			for (unsigned b = 0; b < _slideButtons->count(); b++) {
				CCSprite* button = (CCSprite*) _slideButtons->objectAtIndex(b);
				if (button->boundingBox().containsPoint(tap)) {
					button->setPositionY(800 - 56.5);
				} else {
					button->setPositionY(800 - 56.5 + 15);
				}
			}

			for (unsigned b = 0; b < _zoomButtons->count(); b++) {
				CCSprite* button = (CCSprite*) _zoomButtons->objectAtIndex(b);
				if (button->boundingBox().containsPoint(tap)) {
					button->setScale(1.05f);
				} else {
					button->setScale(0.95f);
				}
			}
		}
	}
}

void MainMenuLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
	CCSetIterator i;
	CCTouch * touch;
	CCPoint tap;

	for (i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch *) (*i);

		if (touch) {
			tap = touch->getLocation();

			for (unsigned b = 0; b < _slideButtons->count(); b++) {
				CCSprite* button = (CCSprite*) _slideButtons->objectAtIndex(b);
				if (button->boundingBox().containsPoint(tap)) {
					(*_gotoActionOfSlideButtons[b])();
				}
				button->setPositionY(800 - 56.5 + 15);
			}

			for (unsigned b = 0; b < _zoomButtons->count(); b++) {
				CCSprite* button = (CCSprite*) _zoomButtons->objectAtIndex(b);
				if (button->boundingBox().containsPoint(tap)) {
					(*_gotoActionOfZoomButtons[b])();
				}
				button->setScale(0.95f);
			}
		}
	}
}

void MainMenuLayer::gotoHelpScene() {
	CCScene * newScene = HelpScene::scene();

	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene * transition = CCTransitionPageTurn::create(0.8, newScene, false);
	CCDirector::sharedDirector()->replaceScene(transition);
}

void MainMenuLayer::gotoRate() {

}

void MainMenuLayer::gotoChooseScene() {
	CCScene * newScene = ChooseScene::scene();

	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene * transition = CCTransitionPageTurn::create(0.8, newScene, false);
	CCDirector::sharedDirector()->replaceScene(transition);
}

void MainMenuLayer::gotoOptionsScene() {
	CCScene * newScene = OptionScene::scene();

	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene * transition = CCTransitionPageTurn::create(0.8, newScene, false);
	CCDirector::sharedDirector()->replaceScene(transition);
}

void MainMenuLayer::gotoStatsScene() {
	CCScene * newScene = StatsScene::scene();

	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene * transition = CCTransitionPageTurn::create(0.8, newScene, false);
	CCDirector::sharedDirector()->replaceScene(transition);
}

void MainMenuLayer::gotoMoreGames() {

}

void MainMenuLayer::keyBackClicked() {
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
