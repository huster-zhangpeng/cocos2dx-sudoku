/*
 * LoadingAnimationLayer.h
 *
 *  Created on: 2013-11-22
 *      Author: zp
 */

#ifndef LOADINGANIMATIONLAYER_H_
#define LOADINGANIMATIONLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class LoadingAnimation : public CCLayer {
private:

	CCSprite * _loading;
	CCArray * _dots;

	int _counter;
	float _time;

	void changeToMainMenuScene(float dt);

public:

	~LoadingAnimation();

	virtual bool init();

	void update(float dt);

	CREATE_FUNC(LoadingAnimation);
};


#endif /* LOADINGANIMATIONLAYER_H_ */
