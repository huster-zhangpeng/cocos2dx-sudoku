/*
 * CasualGameLayer.cpp
 *
 *  Created on: 2013-12-2
 *      Author: zp
 */

#include "GameLayer.h"
#include "../World/Sudoku.h"
#include "../World/Settings.h"

#define SPEED_FACTOR 0.00105f

bool CasualGameLayer::init() {
	if (!GameLayer::init()) {
		return false;
	}

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++) {
			if(Sudoku::puzzel[i][j] != '.'){
				CCSpriteBatchNode* batchNode = (CCSpriteBatchNode*)_numBoardBatch->objectAtIndex(Sudoku::puzzel[i][j] - '1');
				CCSprite * cell = CCSprite::createWithTexture(batchNode->getTexture());
				cell->setPosition(ccp(18 + i * 49 + i / 3 * 3 + 25, 800 - 132 - j * 49 - j / 3 * 3 - 25));
				cell->setScale(0.854);
				cell->setZOrder(2);
				this->addChild(cell);
				_cells[i][j] = cell;
			} else {
				_cells[i][j] = NULL;
			}
		}
	}

	_redMask = CCSprite::create("tileStyle/unfilledFrame.png");
	_redMask->setVisible(false);
	_redMask->setZOrder(3);
	this->addChild(_redMask);

	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create(
			"tileStyle/filledFrame.png");
	for (int i = 0; i < 9; i++) {
		CCSprite * greenMask = CCSprite::createWithTexture(
				batchNode->getTexture());
		greenMask->setVisible(false);
		greenMask->setZOrder(3);
		this->addChild(greenMask);
		_greenMasks[i] = greenMask;
	}
	_greenMaskNum = 0;

	updateCurPos(4, 4);

	return true;
}

void CasualGameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
	GameLayer::ccTouchesBegan(pTouches, event);

	CCSetIterator i;
	CCTouch * touch;
	CCPoint tap;

	for (i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch *) (*i);

		if (touch) {
			tap = touch->getLocation();

			if (tap.y < 680 && tap.y > 210) {
				int x, y;
				for (x = 1; x < 9; x++) {
					if (tap.x < 18 + x * 49 + x / 3 * 3) {
						break;
					}
				}
				for (y = 1; y < 9; y++) {
					if (tap.y > 800 - 132 - y * 49 - y / 3 * 3) {
						break;
					}
				}
				updateCurPos(x - 1, y - 1);
				updateBackplane();
			}
		}
	}
}

void CasualGameLayer::updateCurPos(int x, int y) {
	Sudoku::setCurrentPos(x, y);
	if (Sudoku::puzzel[x][y] == '.') {
		_redMask->setPosition(
				ccp(18 + x * 49 + x / 3 * 3 + 23, 800 - 132 - y * 49 - y / 3 * 3 - 23));
		_redMask->setVisible(true);
		for (int i = 0; i < _greenMaskNum; i++) {
			_greenMasks[i]->setVisible(false);
		}
		_greenMaskNum = 0;
	} else {
		if(Settings::autoHighLight) {
			_greenMaskNum = 0;
			char ch = Sudoku::puzzel[x][y];
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (Sudoku::puzzel[i][j] == ch) {
						_greenMasks[_greenMaskNum]->setPosition(ccp(
								18 + i * 49 + i / 3 * 3 + 23,
								800 - 132 - j * 49 - j / 3 * 3 - 23
						));
						_greenMasks[_greenMaskNum++]->setVisible(true);
					}
				}
			}
			for (int i = _greenMaskNum; i < 9; i++) {
				_greenMasks[i]->setVisible(false);
			}
		} else {
			_greenMaskNum = 1;
			_greenMasks[0]->setPosition(
					ccp(18 + x * 49 + x / 3 * 3 + 23, 800 - 132 - y * 49 - y / 3 * 3 - 23));
			_greenMasks[0]->setVisible(true);
		}
		_redMask->setVisible(false);
	}
}

bool CasualGameLayer::onButtonClicked(CCSprite* button, int index) {
	if(GameLayer::onButtonClicked(button, index)) {
		return true;
	}
	if (Sudoku::state == Running) {
		if (!Sudoku::isCurPosFilled()) {
			button->stopAllActions();
			button->setRotation(0);
			CCPoint end =
					ccp(
							18 + Sudoku::position.x * 49 + Sudoku::position.x / 3 * 3 + 25,
							800 - 132 - Sudoku::position.y * 49 - Sudoku::position.y / 3 * 3 - 25
					);
			float duration = ccpDistance(button->getPosition(),
					end) * SPEED_FACTOR;
			if (Sudoku::isRight('1' + index)) {
				int * params = new int[3];
				params[0] = Sudoku::position.x;
				params[1] = Sudoku::position.y;
				params[2] = index;
				CCSequence * sequence = CCSequence::create(CCMoveTo::create(duration, end),
						CCEaseOut::create(
								CCSequence::create(
										CCRotateBy::create(0.22, -120),
										CCRotateBy::create(0.22, 120),
										NULL), 2),
						CCMoveTo::create(0, button->getPosition()),
						CCCallFuncND::create(this,
								callfuncND_selector(CasualGameLayer::callBack),
								(void*) params), NULL);
				sequence->setTag(TAG_ACTION_FILL);
				button->runAction(sequence);
			} else {
				CCSequence * sequence = CCSequence::create(CCMoveTo::create(duration, end),
						CCRotateBy::create(0.075, -120),
						CCRotateBy::create(0.15, 240),
						CCRotateBy::create(0.075, -120),
						CCMoveTo::create(duration,
								button->getPosition()), NULL);
				sequence->setTag(TAG_ACTION_FILL);
				button->runAction(sequence);
			}
		}
	}
	return true;
}

void CasualGameLayer::callBack(CCNode* sender, void* data) {
	int * params = (int*) data;
	int x, y, res;
	x = params[0];
	y = params[1];
	res = params[2];
	Sudoku::setResult(x, y, res);

	CCSpriteBatchNode* batchNode =
			(CCSpriteBatchNode*) _numBoardBatch->objectAtIndex(res);
	CCSprite * cell = CCSprite::createWithTexture(batchNode->getTexture());
	cell->setPosition(
			ccp(18 + x * 49 + x / 3 * 3 + 25, 800 - 132 - y * 49 - y / 3 * 3 - 25));
	cell->setScale(0.854);
	cell->setZOrder(2);
	this->addChild(cell);
	_cells[x][y] = cell;

	if(Sudoku::position.x == x && Sudoku::position.y == y)
		updateCurPos(x, y);
	if (Settings::removeCompleteDigits && !Sudoku::remain[res]) {
		CCSprite * button = (CCSprite*) _numButtons->objectAtIndex(res);
		button->setVisible(false);
	}
	checkFinished(x, y);
	delete params;
}

void CasualGameLayer::checkFinished(int x, int y){
	bool needCircle[9][9];
	memset(needCircle, false, sizeof(needCircle));
	if(Sudoku::isRowFinished(x)){
		for(int i = 0; i < 9; i++)
			needCircle[x][i] = true;
	}
	if(Sudoku::isColumnFinished(y)){
		for(int i = 0; i < 9; i++)
			needCircle[i][y] = true;
	}
	if(Sudoku::isSquareFinished(x, y)) {
		int sx = x / 3 * 3;
		int sy = y / 3 * 3;
		for(int i = sx; i < sx + 3; i++)
			for(int j = sy; j < sy + 3; j++)
				needCircle[i][j] = true;
	}
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++) if(needCircle[i][j])
			_cells[i][j]->runAction(CCRotateBy::create(0.7, 360));
	}
}
