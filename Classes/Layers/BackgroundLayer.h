/*
 * BackgroundLayer.h
 *
 *  Created on: 2013-11-20
 *      Author: zp
 */

#ifndef BACKGROUNDLAYER_H_
#define BACKGROUNDLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public cocos2d::CCLayer {
private:
	CCSprite * _background;

public:

	virtual bool init();

	CREATE_FUNC(BackgroundLayer);
};


#endif /* BACKGROUNDLAYER_H_ */
