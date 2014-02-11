/*
 * BoardLayer.h
 *
 *  Created on: 2013-11-22
 *      Author: zp
 */

#ifndef BOARDLAYER_H_
#define BOARDLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class BoardLayer : public CCLayer {
private:

	CCSprite * _board;

public:

	virtual bool init();

	CREATE_FUNC(BoardLayer);
};


#endif /* BOARDLAYER_H_ */
