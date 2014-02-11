/*
 * LoadingScreen.cpp
 *
 *  Created on: 2013-11-20
 *      Author: zp
 */

#include "LoadingScene.h"
#include "MainMenuScene.h"
#include "../Layers/BackgroundLayer.h"
#include "../Layers/MainAnimationLayer.h"
#include "../Layers/LoadingAnimationLayer.h"
#include "../Layers/BoardLayer.h"

CCScene* LoadingScene::scene(){
	CCScene* scene = CCScene::create();

	BackgroundLayer* backgroundLayer = BackgroundLayer::create();
	scene->addChild(backgroundLayer);

	BoardLayer* boardLayer = BoardLayer::create();
	scene->addChild(boardLayer);

	MainAnimation * mainAnimation = MainAnimation::create();
	scene->addChild(mainAnimation);

	LoadingAnimation * loadingAnimation = LoadingAnimation::create();
	scene->addChild(loadingAnimation);

	return scene;
}


