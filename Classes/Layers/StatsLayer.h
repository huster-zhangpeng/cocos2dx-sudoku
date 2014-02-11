/*
 * StatsLayer.h
 *
 *  Created on: 2013-12-9
 *      Author: zp
 */

#ifndef STATSLAYER_H_
#define STATSLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class StatsLayer : public CCLayer {
private:

	CCSprite * _back;

	CCArray * _bestTimeLabels;
	CCArray * _bestRunLabels;
	CCArray * _finishedLabels;

	void back();
	void update (float dt);

public:

	~StatsLayer();

	virtual bool init();

	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
	virtual void keyBackClicked();

	CREATE_FUNC(StatsLayer);
};


#endif /* STATSLAYER_H_ */
