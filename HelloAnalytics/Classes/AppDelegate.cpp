#include "AppDelegate.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "PluginManager.h"
#include "AnalyticsFlurry.h"
#include "AnalyticsUmeng.h"

using namespace cocos2d::plugin;
USING_NS_CC;

// The app key of flurry
#define FLURRY_KEY "W8N2JXRQGTGVSG2T3PC8"
// The app key of umeng must be set in AndroidManifest.xml

AnalyticsUmeng* g_pUmeng = NULL;
AnalyticsFlurry* g_pFlurry = NULL;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{

}

bool AppDelegate::applicationDidFinishLaunching()
{
    PluginProtocol* pPlugin = NULL;
    pPlugin = PluginManager::getInstance()->loadPlugin("AnalyticsFlurry");
    g_pFlurry = dynamic_cast<AnalyticsFlurry*>(pPlugin);
    pPlugin = PluginManager::getInstance()->loadPlugin("AnalyticsUmeng");
    g_pUmeng = dynamic_cast<AnalyticsUmeng*>(pPlugin);
    
    g_pFlurry->setDebugMode(true);
    g_pUmeng->setDebugMode(true);

    g_pFlurry->setCaptureUncaughtException(true);
    g_pUmeng->setCaptureUncaughtException(true);

    if (g_pUmeng != NULL)
    {
        g_pUmeng->updateOnlineConfig();
        g_pUmeng->setDefaultReportPolicy(AnalyticsUmeng::REALTIME);
        // The app key of umeng must be set in AndroidManifest.xml, so you don't need to set it here.
        g_pUmeng->startSession("");
    }

    if (g_pFlurry != NULL)
    {
        g_pFlurry->setReportLocation(true);
        g_pFlurry->logPageView();
        int sdkVersion = g_pFlurry->getAgentVersion();
        CCLog("Flurry sdk version = %d", sdkVersion);
        g_pFlurry->setVersionName("1.1");
        g_pFlurry->setAge(20);
        g_pFlurry->setGender(AnalyticsFlurry::MALE);
        g_pFlurry->setUserId("123456");
        g_pFlurry->setUseHttps(false);
        g_pFlurry->startSession(FLURRY_KEY);
    }
    
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
    g_pFlurry->stopSession();
    g_pUmeng->stopSession();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();

    g_pUmeng->startSession("");
    g_pFlurry->startSession(FLURRY_KEY);

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
