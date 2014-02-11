/*
 * StatsLayer.cpp
 *
 *  Created on: 2013-12-9
 *      Author: zp
 */

#include "StatsLayer.h"
#include "../Scenes/MainMenuScene.h"
#include "../World/Settings.h"

StatsLayer::~StatsLayer() {
	CC_SAFE_RELEASE(_bestTimeLabels);
	CC_SAFE_RELEASE(_bestRunLabels);
	CC_SAFE_RELEASE(_finishedLabels);
}

bool StatsLayer::init() {
	if(!CCLayer::init()) {
		return false;
	}

	_back = CCSprite::create("back.png");
	_back->setPosition(ccp(24 + 40, 800 - 56.5 + 15));
	this->addChild(_back);

	CCSprite * statsLogo = CCSprite::create("stats_logo.png");
	statsLogo->setPosition(ccp(177 + 64, 800 - 105 - 18.5));
	this->addChild(statsLogo);

	CCSpriteBatchNode * bestTimeBatch = CCSpriteBatchNode::create("s_besttime.png");
	CCSpriteBatchNode * bestRunBatch = CCSpriteBatchNode::create("s_bestrun.png");
	CCSpriteBatchNode * finishedBatch = CCSpriteBatchNode::create("s_finished.png");
	CCSpriteBatchNode * dotLineBatch = CCSpriteBatchNode::create("dotted_line.png");

	int LineY[3] = {288, 419, 558};
	for(int i = 0; i < 3; i++) {
		CCSprite * line = CCSprite::createWithTexture(dotLineBatch->getTexture());
		line->setPosition(ccp(33 + line->boundingBox().size.width / 2,
				800 - LineY[i] - line->boundingBox().size.height / 2));
		this->addChild(line);
	}

	_bestTimeLabels = CCArray::createWithCapacity(4);
	_bestTimeLabels->retain();
	_bestRunLabels = CCArray::createWithCapacity(4);
	_bestRunLabels->retain();
	_finishedLabels = CCArray::createWithCapacity(4);
	_finishedLabels->retain();

	CCArray * labels[3] = {_bestTimeLabels, _bestRunLabels, _finishedLabels};
	char levels[4][20] = {"level/s_easy.png", "level/s_normal.png",
			"level/s_hard.png", "level/s_expert.png"};
	CCSpriteBatchNode * batches[3] = {bestTimeBatch, bestRunBatch, finishedBatch};
	int LevelY[4] = {216, 343, 477, 615};
	int StatsY[4] = {184, 314, 446, 586};
	for(int i = 0; i < 4; i++) {
		CCSprite * level = CCSprite::create(levels[i]);
		level->setPosition(ccp(43 + level->boundingBox().size.width / 2,
				800 - LevelY[i] - level->boundingBox().size.height / 2));
		this->addChild(level);

		for(int j = 0; j < 3; j++) {
			CCSprite * sprite = CCSprite::createWithTexture(batches[j]->getTexture());
			sprite->setPosition(ccp(239 + sprite->boundingBox().size.width / 2,
					800 - StatsY[i] - j * 33.5 - sprite->boundingBox().size.height / 2));
			this->addChild(sprite);

			CCLabelTTF * label = CCLabelTTF::create("0", "Verdana-Bold", 24);
			label->setPosition(ccp(440, 800 - StatsY[i] - j * 33.5 - sprite->boundingBox().size.height / 2));
			this->addChild(label);
			label->setColor(ccc3(0, 0, 0));
			labels[j]->addObject(label);
		}
	}
	this->schedule(schedule_selector(StatsLayer::update));

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	return true;
}

void StatsLayer::update (float dt) {
	char buffer[20];
	for(int level = 0; level < 4; level ++) {
		if(Stats::bestTime[level] == 0) {
			sprintf(buffer, "--:--");
		} else {
			int sec = Stats::bestTime[level];
			int min = sec / 60;
			int hour = min / 60;
			sec = sec % 60;
			min = min % 60;
			if(hour > 0)
				sprintf(buffer, "%d:%02d:%02d", hour, min, sec);
			else
				sprintf(buffer, "%02d:%02d", min, sec);
		}
		CCLabelTTF * timeLabel = (CCLabelTTF *) _bestTimeLabels->objectAtIndex(level);
		timeLabel->setString(buffer);
		timeLabel->setPositionX(440 - timeLabel->boundingBox().size.width / 2);

		if(Stats::bestRun[level])
			sprintf(buffer, "%d", Stats::bestRun[level]);
		else
			sprintf(buffer, "-");
		CCLabelTTF * runLabel = (CCLabelTTF *) _bestRunLabels->objectAtIndex(level);
		runLabel->setString(buffer);
		runLabel->setPositionX(440 - runLabel->boundingBox().size.width / 2);

		if(Stats::finished[level])
			sprintf(buffer, "%d", Stats::finished[level]);
		else
			sprintf(buffer, "-");
		CCLabelTTF * finishedLabel = (CCLabelTTF *) _finishedLabels->objectAtIndex(level);
		finishedLabel->setString(buffer);
		finishedLabel->setPositionX(440 - finishedLabel->boundingBox().size.width / 2);
	}


}

void StatsLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
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
		}
	}
}

void StatsLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event) {
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
		}
	}
}

void StatsLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
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
		}
	}
}

void StatsLayer::keyBackClicked() {
	back();
}

void StatsLayer::back() {
	CCScene * newScene = MainMenu::scene();

	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene * transition = CCTransitionPageTurn::create(0.8, newScene, true);
	CCDirector::sharedDirector()->replaceScene(transition);
}
