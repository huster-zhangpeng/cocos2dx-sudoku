/*
 * GameLayer.h
 *
 *  Created on: 2013-11-23
 *      Author: zp
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include "cocos2d.h"

USING_NS_CC;

#define TAG_ACTION_FILL 101

class GameLayer: public CCLayer {
private:

	CCSprite * _back;
	CCSprite * _restart;

	CCLabelTTF * _timer;

	CCLabelTTF * _hint;
	CCSprite * _pencilToNote;
	CCSprite * _penToRun;

	static void back();
	void update (float dt);
	void updateHint();
	void consumeHint();

protected:

	CCArray * _numButtons;
	CCArray * _numNote;
	CCArray * _numNoteBatch;
	CCArray * _numBoardBatch;
	CCArray * _numBoardOrinalBatch;
	CCArray * _backPlanes;
	CCSprite * _cells[9][9];
	CCSprite * _notes[9][9][9];

	virtual bool onButtonClicked(CCSprite* button, int index);
	void updateNote(int x, int y);
	void updateBackplane();

public:

	~GameLayer();

	virtual bool init();


	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);

	virtual void keyBackClicked();
};

class CasualGameLayer : public GameLayer {
private:

	CCSprite * _redMask;
	CCSprite * _greenMasks[9];
	int _greenMaskNum;

	void updateCurPos(int x, int y);
	void checkFinished(int x, int y);
	void callBack(CCNode* sender, void* data);

protected:

	virtual bool onButtonClicked(CCSprite* button, int index);

public:

	virtual bool init();

	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);

	CREATE_FUNC(CasualGameLayer);
};

#endif /* GAMELAYER_H_ */
