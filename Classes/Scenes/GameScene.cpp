/*
 * GameScene.cpp
 *
 *  Created on: 2013-11-23
 *      Author: zp
 */

#include "GameScene.h"
#include "../Layers/GameLayer.h"

CCScene* GameScene::scene() {
	CCScene * scene = CCScene::create();

	GameLayer * gameLayer = CasualGameLayer::create();
	scene->addChild(gameLayer);

	return scene;
}


