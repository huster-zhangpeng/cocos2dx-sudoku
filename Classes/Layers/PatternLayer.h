/*
 * Pattern.h
 *
 *  Created on: 2013-11-25
 *      Author: zp
 */

#ifndef PATTERN_H_
#define PATTERN_H_

#include "cocos2d.h"

USING_NS_CC;

class PatternLayer : public CCLayer {
private:

	CCSprite * _pattern;

public:

	virtual bool init();

	CREATE_FUNC(PatternLayer);
};


#endif /* PATTERN_H_ */
