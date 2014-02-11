/*
 * ChooseScene.cpp
 *
 *  Created on: 2013-11-23
 *      Author: zp
 */

#include "ChooseScene.h"
#include "MainMenuScene.h"
#include "../Layers/BackgroundLayer.h"
#include "../Layers/MainAnimationLayer.h"
#include "../Layers/BoardLayer.h"
#include "../Layers/ChooseLayer.h"

CCScene* ChooseScene::scene() {
	CCScene * scene = CCScene::create();

	BackgroundLayer* backgroundLayer = BackgroundLayer::create();
	scene->addChild(backgroundLayer);

	BoardLayer* boardLayer = BoardLayer::create();
	scene->addChild(boardLayer);

	ChooseLayer* chooseLayer = ChooseLayer::create();
	scene->addChild(chooseLayer);

	return scene;
}

