/*
 * OptionLayer.h
 *
 *  Created on: 2013-11-25
 *      Author: zp
 */

#ifndef OPTIONLAYER_H_
#define OPTIONLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class OptionLayer: public CCLayer {
private:

	CCSprite * _back;

	CCArray * _switchButtons;
	int _switchIndex;
	float _tapX;
	bool * _switches[8];

	static void back();

public:

	~OptionLayer();
	virtual bool init();

	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);

	virtual void keyBackClicked();

	CREATE_FUNC(OptionLayer);
};

#endif /* OPTIONLAYER_H_ */
