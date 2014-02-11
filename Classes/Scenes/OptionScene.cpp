/*
 * OptionScene.cpp
 *
 *  Created on: 2013-11-26
 *      Author: zp
 */

#include "OptionScene.h"
#include "../Layers/BackgroundLayer.h"
#include "../Layers/PatternLayer.h"
#include "../Layers/OptionLayer.h"

CCScene* OptionScene::scene() {
	CCScene * scene = CCScene::create();

	BackgroundLayer * bgLayer = BackgroundLayer::create();
	scene->addChild(bgLayer);

	PatternLayer * patternLayer = PatternLayer::create();
	scene->addChild(patternLayer);

	OptionLayer * optionLayer = OptionLayer::create();
	scene->addChild(optionLayer);

	return scene;
}


