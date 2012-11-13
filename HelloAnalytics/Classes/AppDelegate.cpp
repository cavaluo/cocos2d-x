#include "AppDelegate.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "GameAnalytics.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
    GameAnalytics::destory();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    GameAnalytics::getAnalytics()->setDebugMode(true);
    GameAnalytics::getAnalytics()->setCaptureUncaughtException(true);
#if (TARGET_ANALYTICS == ANALYTICS_UMENG)
    GameAnalytics::getAnalytics()->updateOnlineConfig();
    GameAnalytics::getAnalytics()->setDefaultReportPolicy(AnalyticsUmeng::REALTIME);
    GameAnalytics::getAnalytics()->startSession("509b76db5270150885000013");
#elif (TARGET_ANALYTICS == ANALYTICS_FLURRY)
    GameAnalytics::getAnalytics()->setReportLocation(true);
    GameAnalytics::getAnalytics()->logPageView();
    int sdkVersion = GameAnalytics::getAnalytics()->getAgentVersion();
    CCLog("Flurry sdk version = %d", sdkVersion);
    GameAnalytics::getAnalytics()->setVersionName("1.1");
    GameAnalytics::getAnalytics()->setAge(20);
    GameAnalytics::getAnalytics()->setGender(AnalyticsFlurry::MALE);
    GameAnalytics::getAnalytics()->setUserId("123456");
    GameAnalytics::getAnalytics()->setUseHttps(false);
    GameAnalytics::getAnalytics()->startSession("W8N2JXRQGTGVSG2T3PC8");
#endif
    
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    GameAnalytics::getAnalytics()->stopSession();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();

#if (TARGET_ANALYTICS == ANALYTICS_UMENG)
    GameAnalytics::getAnalytics()->startSession("509b76db5270150885000013");
#elif (TARGET_ANALYTICS == ANALYTICS_FLURRY)
    GameAnalytics::getAnalytics()->startSession("W8N2JXRQGTGVSG2T3PC8");
#endif
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
