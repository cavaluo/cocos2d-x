#include "AppDelegate.h"

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Analytics_umeng.h"

USING_NS_CC;
using namespace cocos2d::plugin;

AnalyticsUmeng* g_pAnalytics = NULL;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
    CC_SAFE_DELETE(g_pAnalytics);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    g_pAnalytics = new AnalyticsUmeng();
    g_pAnalytics->setDebugMode(true);
    g_pAnalytics->updateOnlineConfig();
    g_pAnalytics->setCaptureUncaughtException(true);
    g_pAnalytics->setDefaultReportPolicy(AnalyticsUmeng::REALTIME);
    g_pAnalytics->beginSession("509b76db5270150885000013");
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
    g_pAnalytics->endSession();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    CCLog("AppDelegate::applicationWillEnterForeground");
    g_pAnalytics->beginSession("509b76db5270150885000013");
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
