/*
 * MainAnimationLayer.cpp
 *
 *  Created on: 2013-11-21
 *      Author: zp
 */

#include "MainAnimationLayer.h"

static int ROTATE[6] = { -15, 0, 15, 15, 0, 15 };
static int LX[6] = { 106, 164, 220, 276, 330, 387 };
static int ORDER[6] = { 1, 3, 5, 0, 2, 4 };

static float INTERVAL = 0.19f;
static float ROTATE_DURATION = 0.72f;
static float TOTAL;

static float HALF_LOGO_DURATION = 0.3f;
static float MAX_SCALE = 1.04f;
static float MAX_MOVEUP = 1.82f;
static float LOGO_ANIMATION_FORE_TIME;

MainAnimation::~MainAnimation() {
	CC_SAFE_RELEASE(_letters);

	CC_SAFE_RELEASE(_sudokuAction);
	CC_SAFE_RELEASE(_rotateActions);
}

bool MainAnimation::init() {
	if (!CCLayer::init()) {
		return false;
	}

	_sudoku = CCSprite::create("logo.png");
	_sudoku->setPosition(ccp(241, 643));
	this->addChild(_sudoku);

	CCSprite * m = CCSprite::create("lm.png");
	CCSprite * a = CCSprite::create("la.png");
	CCSprite * s = CCSprite::create("ls.png");
	CCSprite * t = CCSprite::create("lt.png");
	CCSprite * e = CCSprite::create("le.png");
	CCSprite * r = CCSprite::create("lr.png");

	_letters = CCArray::create(m, a, s, t, e, r, NULL);
	_letters->retain();

	createAction();

	CCSprite * letter;
	CCAction * animation;
	int k;
	for (int i = 0; i < 6; i++) {
		k = ORDER[i];
		animation = (CCAction*) _rotateActions->objectAtIndex(k);
		letter = (CCSprite *) _letters->objectAtIndex(k);
		letter->setPosition(ccp(LX[k], 800 - 250));
		letter->setRotation(ROTATE[k]);
		letter->runAction(animation);
		this->addChild(letter);
	}
	_sudoku->runAction(_sudokuAction);

	return true;
}

void MainAnimation::createAction() {
	LOGO_ANIMATION_FORE_TIME = ROTATE_DURATION + 5 * INTERVAL + 0.15f;
	TOTAL = LOGO_ANIMATION_FORE_TIME + HALF_LOGO_DURATION * 2 + 2;

	CCRotateBy* rotate0 = CCRotateBy::create(ROTATE_DURATION, 360);
	CCSequence * mSequence = CCSequence::create(rotate0,
			CCDelayTime::create(TOTAL - ROTATE_DURATION), NULL);
	CCAction * mAnimation = CCRepeatForever::create(
			(CCActionInterval*) mSequence);

	CCRotateBy* rotate1 = CCRotateBy::create(ROTATE_DURATION, 360);
	CCSequence * aSequence = CCSequence::create(CCDelayTime::create(INTERVAL),
			rotate1, CCDelayTime::create(TOTAL - ROTATE_DURATION - INTERVAL), NULL);
	CCAction * aAnimation = CCRepeatForever::create(
			(CCActionInterval*) aSequence);

	CCRotateBy* rotate2 = CCRotateBy::create(ROTATE_DURATION, 360);
	CCSequence * sSequence = CCSequence::create(
			CCDelayTime::create(INTERVAL * 2), rotate2,
			CCDelayTime::create(TOTAL - ROTATE_DURATION - INTERVAL * 2), NULL);
	CCAction * sAnimation = CCRepeatForever::create(
			(CCActionInterval*) sSequence);

	CCRotateBy* rotate3 = CCRotateBy::create(ROTATE_DURATION, 360);
	CCSequence * tSequence = CCSequence::create(
			CCDelayTime::create(INTERVAL * 3), rotate3,
			CCDelayTime::create(TOTAL - ROTATE_DURATION - INTERVAL * 3), NULL);
	CCAction * tAnimation = CCRepeatForever::create(
			(CCActionInterval*) tSequence);

	CCRotateBy* rotate4 = CCRotateBy::create(ROTATE_DURATION, 360);
	CCSequence * eSequence = CCSequence::create(
			CCDelayTime::create(INTERVAL * 4), rotate4,
			CCDelayTime::create(TOTAL - ROTATE_DURATION - INTERVAL * 4), NULL);
	CCAction * eAnimation = CCRepeatForever::create(
			(CCActionInterval*) eSequence);

	CCRotateBy* rotate5 = CCRotateBy::create(ROTATE_DURATION, 360);
	CCSequence * rSequence = CCSequence::create(
			CCDelayTime::create(INTERVAL * 5), rotate5,
			CCDelayTime::create(TOTAL - ROTATE_DURATION - INTERVAL * 5), NULL);
	CCAction * rAnimation = CCRepeatForever::create(
			(CCActionInterval*) rSequence);

	_rotateActions = CCArray::create(mAnimation, aAnimation, sAnimation, tAnimation, eAnimation, rAnimation, NULL);
	_rotateActions->retain();

	CCScaleTo * zoomIn = CCScaleTo::create(HALF_LOGO_DURATION, MAX_SCALE);
	CCScaleTo * zoomOut = CCScaleTo::create(HALF_LOGO_DURATION, 1);
	CCSequence * zoom = CCSequence::create(zoomIn, zoomOut, NULL);
	CCMoveBy * moveUp = CCMoveBy::create(HALF_LOGO_DURATION, ccp(0, MAX_MOVEUP));
	CCMoveBy * moveDown = CCMoveBy::create(HALF_LOGO_DURATION, ccp(0, -MAX_MOVEUP));
	CCSequence * move = CCSequence::create(moveUp, moveDown, NULL);
	CCAction * logoAction = CCSpawn::create(zoom, move, NULL);
	_sudokuAction = CCRepeatForever::create(CCSequence::create(
			CCDelayTime::create(LOGO_ANIMATION_FORE_TIME),
			logoAction,
			CCDelayTime::create(2),
			NULL));
	_sudokuAction->retain();
}
