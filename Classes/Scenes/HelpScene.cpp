/*
 * HelpScene.cpp
 *
 *  Created on: 2013-12-12
 *      Author: zp
 */

#include "HelpScene.h"
#include "../Layers/HelpLayer.h"

CCScene* HelpScene::scene() {

	CCScene * scene = CCScene::create();

	CCLayer * helpLayer = HelpLayer::create();
	scene->addChild(helpLayer);

	return scene;
}


