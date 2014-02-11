/*
 * MainMenuScene.cpp
 *
 *  Created on: 2013-11-22
 *      Author: zp
 */

#include "MainMenuScene.h"
#include "../Layers/BackgroundLayer.h"
#include "../Layers/MainAnimationLayer.h"
#include "../Layers/BoardLayer.h"
#include "../Layers/MainMenuLayer.h"

CCScene* MainMenu::scene() {
	CCScene * scene = CCScene::create();

	BackgroundLayer* backgroundLayer = BackgroundLayer::create();
	scene->addChild(backgroundLayer);

	BoardLayer* boardLayer = BoardLayer::create();
	scene->addChild(boardLayer);

	MainAnimation * mainAnimation = MainAnimation::create();
	scene->addChild(mainAnimation);

	MainMenuLayer * mainMenuLayer = MainMenuLayer::create();
	scene->addChild(mainMenuLayer);

	return scene;
}

