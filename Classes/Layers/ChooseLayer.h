/*
 * ChooseLayer.h
 *
 *  Created on: 2013-11-22
 *      Author: zp
 */

#ifndef CHOOSELAYER_H_
#define CHOOSELAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class ChooseLayer: public CCLayer {
private:
	CCSprite * _back;
	CCSprite * _resume;

	CCArray * _levelButtons;

	static void back();
	static void gotoGame();

public:

	~ChooseLayer();

	virtual bool init();

	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);

	virtual void keyBackClicked();

	CREATE_FUNC(ChooseLayer);
};

#endif /* CHOOSELAYER_H_ */
