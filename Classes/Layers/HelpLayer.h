/*
 * HelpLayer.h
 *
 *  Created on: 2013-12-12
 *      Author: zp
 */

#ifndef HELPLAYER_H_
#define HELPLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class HelpLayer : public CCLayer, public CCScrollViewDelegate {
private:
	CCScrollView* scrollView;
	float _lastOffset;

	void back();

public:
	virtual bool init();

	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);

	virtual void keyBackClicked();

	CREATE_FUNC(HelpLayer);

	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);
};

#endif /* HELPLAYER_H_ */
