#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "Scenes/LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "Scenes/GameScene.h"
#include "World/Sudoku.h"
#include "World/Puzzels.h"

USING_NS_CC;

using namespace std;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    CCSize screenSize = pEGLView->getFrameSize();
    CCLog("%.2f and %.2f is FrameSize", screenSize.width, screenSize.height);
    CCSize designSize = CCSize(480, 800);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionUnKnown);
    if(screenSize.width > 768) {
    	vector<string> searchPaths;
    	searchPaths.push_back("hd");
    	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    } else {
    	vector<string> searchPaths;
    	searchPaths.push_back("sd");
    	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    }

    Sudoku::load(0, puzzels[0][0], puzzels[0][0]);
	
//    SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("hit.wav").c_str());
//    SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("score.hit").c_str());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
//    CCScene *pScene = HelloWorld::scene();
    CCScene *pScene = LoadingScene::scene();
//    CCScene *pScene = GameScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
