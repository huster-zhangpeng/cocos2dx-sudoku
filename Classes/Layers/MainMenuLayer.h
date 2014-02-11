/*
 * MainMenuLayer.h
 *
 *  Created on: 2013-11-22
 *      Author: zp
 */

#ifndef MAINMENULAYER_H_
#define MAINMENULAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class MainMenuLayer: public CCLayer {
private:

	CCSprite * _help;
	CCSprite * _rate;

	CCArray * _slideButtons;
	CCArray * _zoomButtons;

	static void gotoHelpScene();
	static void gotoRate();

	static void gotoChooseScene();
	static void gotoOptionsScene();
	static void gotoStatsScene();
	static void gotoMoreGames();

	void (*_gotoActionOfZoomButtons[4])();
	void (*_gotoActionOfSlideButtons[2])();

public:

	~MainMenuLayer();

	virtual bool init();

	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);

	virtual void keyBackClicked();

	CREATE_FUNC(MainMenuLayer);
};

#endif /* MAINMENULAYER_H_ */
