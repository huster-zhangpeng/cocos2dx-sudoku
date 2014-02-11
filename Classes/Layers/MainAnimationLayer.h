/*
 * MainAnimationLayer.h
 *
 *  Created on: 2013-11-21
 *      Author: zp
 */

#ifndef MAINANIMATIONLAYER_H_
#define MAINANIMATIONLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class MainAnimation : public CCLayer {
private:

 	CCSprite * _sudoku;

	CCArray * _letters;
	CCAction * _sudokuAction;
	CCArray * _rotateActions;

	void createAction();

public:

	~MainAnimation();

	virtual bool init();

	CREATE_FUNC(MainAnimation);
};


#endif /* MAINANIMATIONLAYER_H_ */
