/*
 * StatsScene.cpp
 *
 *  Created on: 2013-12-9
 *      Author: zp
 */

#include "StatsScene.h"
#include "../Layers/BackgroundLayer.h"
#include "../Layers/PatternLayer.h"
#include "../Layers/StatsLayer.h"

CCScene * StatsScene::scene() {
	CCScene * scene = CCScene::create();

	CCLayer * background = BackgroundLayer::create();
	scene->addChild(background);

	CCLayer * pattern = PatternLayer::create();
	scene->addChild(pattern);

	CCLayer * stats = StatsLayer::create();
	scene->addChild(stats);

	return scene;
}


