/*
 * GameLayer.cpp
 *
 *  Created on: 2013-11-23
 *      Author: zp
 */

#include "GameLayer.h"
#include "../Scenes/ChooseScene.h"
#include "../World/Sudoku.h"
#include "../World/Settings.h"

int BX_START = 34.5;
int BX_STEP = 51.5;
int BY[2] = { 169, 144 };

GameLayer::~GameLayer() {
	CC_SAFE_RELEASE(_numBoardBatch);
	CC_SAFE_RELEASE(_numButtons);
}

bool GameLayer::init() {
	if (!CCLayer::init()) {
		return false;
	}

	char buffer[30];

	_numBoardBatch = CCArray::createWithCapacity(9);
	_numBoardBatch->retain();
	for(int i = 1; i <= 9; i++) {
		sprintf(buffer, "tileStyle/pn/%d.png", i);
		CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create(buffer);
		_numBoardBatch->addObject(batchNode);
	}

	CCSprite * background = CCSprite::create("tileStyle/background.jpg");
	background->setPosition(ccp(240, 400));
	this->addChild(background);

	_back = CCSprite::create("back.png");
	_back->setPosition(ccp(24 + 40, 800 - 56.5 + 15));
	this->addChild(_back);
	_restart = CCSprite::create("tileStyle/restart.png");
	_restart->setPosition(ccp(375 + 40, 800 - 56.5 + 15));
	this->addChild(_restart);

	_timer = CCLabelTTF::create("0", "Verdana-Bold", 30);
	_timer->setPosition(ccp(240, 800 - 13 - 20));
	_timer->setVisible(Settings::showTimer);
	this->addChild(_timer);

	_numButtons = CCArray::createWithCapacity(9);
	_numButtons->retain();
	_numNote = CCArray::createWithCapacity(9);
	_numNote->retain();
	_numNoteBatch = CCArray::createWithCapacity(9);
	_numNoteBatch->retain();
	_backPlanes = CCArray::createWithCapacity(9);
	_backPlanes->retain();
	CCSpriteBatchNode* backPlaneBatch = CCSpriteBatchNode::create("tileStyle/backplane.png");
	for(int i = 1; i <= 9; i++) {
		sprintf(buffer, "tileStyle/numb/%d.png", i);
		CCSprite * num = CCSprite::create(buffer);
		num->setZOrder(4);
		_numButtons->addObject(num);

		sprintf(buffer, "tileStyle/noteb/%d.png", i);
		CCSpriteBatchNode* noteBatch = CCSpriteBatchNode::create(buffer);
		_numNoteBatch->addObject(noteBatch);

		CCSprite * note = CCSprite::createWithTexture(noteBatch->getTexture());
		_numNote->addObject(note);

		CCSprite * backPlane = CCSprite::createWithTexture(backPlaneBatch->getTexture());
		_backPlanes->addObject(backPlane);
	}
	int k;
	for (int order = 0; order < 2; order++) {
		for (int i = 0; i < 5 - order; i++) {
			k = 2 * i + order;
			CCSprite * num = (CCSprite*)_numButtons->objectAtIndex(k);
			num->setPosition(ccp(BX_START + k * BX_STEP, BY[order]));
			num->setVisible(Sudoku::state == Running);
			this->addChild(num);

			CCSprite * note = (CCSprite *)_numNote->objectAtIndex(k);
			note->setPosition(ccp(BX_START + k * BX_STEP, BY[order]));
			note->setVisible(Sudoku::state == Note);
			this->addChild(note);

			CCSprite * backPlane = (CCSprite *)_backPlanes->objectAtIndex(k);
			backPlane->setPosition(ccp(BX_START + k * BX_STEP, BY[order]));
			this->addChild(backPlane);
		}
	}
	updateBackplane();

	_hint = CCLabelTTF::create("5", "Verdana-Bold", 32);
	_hint->setPosition(ccp(12 + 33 - 2, 800 - 704 - 33 + 2));
	_hint->setColor(ccc3(0, 0, 0));
	updateHint();
	this->addChild(_hint);
	CCSprite * magnifierGlass = CCSprite::create("tileStyle/hint.png");
	magnifierGlass->setPosition(ccp(12 + 33, 800 - 704 - 33));
	this->addChild(magnifierGlass);
	_pencilToNote = CCSprite::create("tileStyle/pencil.png");
	_pencilToNote->setPosition(ccp(401 + 33, 800 - 704 - 33));
	_pencilToNote->setVisible(Sudoku::state == Running);
	this->addChild(_pencilToNote);
	_penToRun = CCSprite::create("tileStyle/pen.png");
	_penToRun->setPosition(ccp(401 + 33, 800 - 704 - 33));
	_penToRun->setVisible(Sudoku::state == Note);
	this->addChild(_penToRun);

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	this->schedule(schedule_selector(GameLayer::update));

	return true;
}

void GameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
	CCSetIterator i;
	CCTouch * touch;
	CCPoint tap;

	for (i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch *) (*i);

		if (touch) {
			// begin to handle a touch event
			tap = touch->getLocation();

			if (_back->boundingBox().containsPoint(tap)) {
				_back->setPositionY(800 - 56.5);
			}
			if (_restart->boundingBox().containsPoint(tap)) {
				_restart->setPositionY(800 - 56.5);
			}

			for (unsigned b = 0; b < _numButtons->count(); b++) {
				CCSprite* button = (CCSprite*) _numButtons->objectAtIndex(b);
				if (button->boundingBox().containsPoint(tap)) {
					onButtonClicked(button, b);
				}
			}

			if(_hint->boundingBox().containsPoint(tap)) {
				if(Sudoku::state == Running && !Sudoku::isCurPosFilled() && Stats::hintNum > 0) {
					CCSprite* button = (CCSprite*)_numButtons->objectAtIndex(Sudoku::getResult() - 1);
					int actionNum = getActionManager()->numberOfRunningActionsInTarget(button);
					if(!actionNum) {
						consumeHint();
						button->runAction(
								CCSequence::create(
										CCRotateBy::create(1, 360),
										CCDelayTime::create(0.3),
										CCRotateBy::create(1, 360),
										NULL
								)
						);
					}
				}
			}

			if(_penToRun->boundingBox().containsPoint(tap)) {
				Sudoku::state = (Sudoku::state == Running) ? Note : Running;
				_pencilToNote->setVisible(Sudoku::state == Running);
				_penToRun->setVisible(Sudoku::state == Note);
				if(Sudoku::state == Note) updateBackplane();
				for(int i = 0; i < 9; i++) {
					CCSprite * rb = (CCSprite *) _numButtons->objectAtIndex(i);
					rb->setVisible(Sudoku::state == Running);

					CCSprite * nb = (CCSprite *) _numNote->objectAtIndex(i);
					nb->setVisible(Sudoku::state == Note);
				}
			}
			// end handling
		}
	}
}

void GameLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event) {
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
			if (_restart->boundingBox().containsPoint(tap)) {
				_restart->setPositionY(800 - 56.5);
			} else {
				_restart->setPositionY(800 - 56.5 + 15);
			}
		}
	}
}

void GameLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
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
			if (_restart->boundingBox().containsPoint(tap)) {

			}
			_restart->setPositionY(800 - 56.5 + 15);
		}
	}
}

bool GameLayer::onButtonClicked(CCSprite* button, int index) {
	if(Sudoku::state == Note && !Sudoku::isCurPosFilled()) {
		Sudoku::notes[Sudoku::position.x][Sudoku::position.y].toggle(index + 1);
		updateNote(Sudoku::position.x, Sudoku::position.y);
		updateBackplane();
		return true;
	}
	return false;
}

static const int NOTE_NUM_RX[] = {
		15,
		8, 24,
		15, 8, 24,
		8, 24, 8, 24,
		8, 24, 2, 16, 30,
		2, 16, 30, 2, 16, 30,
		2, 16, 30, 15, 2, 16, 30,
		2, 16, 30, 8, 24, 2, 16, 30,
		2, 16, 30, 2, 16, 30, 2, 16, 30
};
static const int NOTE_NUM_RY[] = {
		16,
		16, 16,
		5, 26, 26,
		5, 5, 26, 26,
		5, 5, 26, 26, 26,
		5, 5, 5, 26, 26, 26,
		1, 1, 1, 15, 29, 29, 29,
		1, 1, 1, 15, 15, 29, 29, 29,
		1, 1, 1, 15, 15, 15, 29, 29, 29
};
static const float SCALE[] = {0.5, 0.5, 0.5, 0.5, 0.4, 0.4, 0.3, 0.3, 0.3};

void GameLayer::updateNote(int x, int y) {
	int totalNote = Sudoku::notes[x][y].total();
	int k = 0, offset = totalNote * (totalNote - 1) / 2;
	for(int i = 0; i < 9; i++) {
		if(Sudoku::notes[x][y].has(i+1)) {
			if(!_notes[x][y][i]) {
				CCSpriteBatchNode * batch = (CCSpriteBatchNode*)_numNoteBatch->objectAtIndex(i);
				CCSprite * littleNote = CCSprite::createWithTexture(batch->getTexture());
				littleNote->setZOrder(2);
				_notes[x][y][i] = littleNote;
				this->addChild(littleNote);
			}
			// position it
			_notes[x][y][i]->setPosition(ccp(
					NOTE_NUM_RX[offset + k] + 26 + x * 49 + x / 3 * 3,
					-NOTE_NUM_RY[offset + k] + 800 - 141 - y * 49 - y / 3 * 3));
			CCLog("total note: %d", totalNote);
			_notes[x][y][i]->setScale(SCALE[totalNote - 1]);
			CCLog("here");
			k++;
		} else {
			if(_notes[x][y][i]) {
				this->removeChild(_notes[x][y][i]);
				_notes[x][y][i] = NULL;
			}
		}
	}
}

void GameLayer::updateBackplane() {
	if(Sudoku::state == Note) {
		int x = Sudoku::position.x;
		int y = Sudoku::position.y;
		for(int i = 0; i < 9; i++) {
			CCSprite * backplane = (CCSprite *)_backPlanes->objectAtIndex(i);
			backplane->setVisible(Sudoku::notes[x][y].has(i + 1));
		}
	}
}

void GameLayer::update (float dt) {
	Sudoku::usedTimeSec += dt;
	int sec = (int) Sudoku::usedTimeSec;
	int min = sec / 60;
	int hour = min / 60;
	sec = sec % 60;
	min = min % 60;
	char buffer[10];
	if(hour > 0)
		sprintf(buffer, "%d:%02d:%02d", hour, min, sec);
	else
		sprintf(buffer, "%02d:%02d", min, sec);
	_timer->setString(buffer);
}

void GameLayer::consumeHint(){
	Stats::hintNum --;
	updateHint();
}

void GameLayer::updateHint(){
	char buf[4];
	if(Stats::hintNum > 999) {
		sprintf(buf, "%03d", Stats::hintNum % 1000);
	} else if(Stats::hintNum){
		sprintf(buf, "%d", Stats::hintNum);
	} else {
		sprintf(buf, "+");
	}
	_hint->setString(buf);

	if(Stats::hintNum > 99) {
		_hint->setFontSize(18);
	} else if(Stats::hintNum > 9) {
		_hint->setFontSize(25);
	} else {
		_hint->setFontSize(32);
	}
}

void GameLayer::keyBackClicked() {
	back();
}

void GameLayer::back() {
	CCScene * newScene = ChooseScene::scene();

	CCDirector::sharedDirector()->setDepthTest(true);
	CCTransitionScene * transition = CCTransitionPageTurn::create(0.8, newScene,
			true);
	CCDirector::sharedDirector()->replaceScene(transition);
}

