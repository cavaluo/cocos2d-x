#include "AppDelegate.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "AnalyticsManager.h"

using namespace cocos2d::plugin;
USING_NS_CC;

// The app key of flurry
#define FLURRY_KEY "W8N2JXRQGTGVSG2T3PC8"
// The app key of umeng must be set in AndroidManifest.xml

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
    AnalyticsManager::destory();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // Please change the type of analytics here.
    AnalyticsManager::setAnalyticsType(kAnalyticsType_Umeng);
    //AnalyticsManager::setAnalyticsType(kAnalyticsType_Flurry);

    AnalyticsProtocol* pAnalyticsInstance = AnalyticsManager::getAnalytics();
    AnalyticsUmeng* pUmeng = dynamic_cast<AnalyticsUmeng*>(pAnalyticsInstance);
    AnalyticsFlurry* pFlurry = dynamic_cast<AnalyticsFlurry*>(pAnalyticsInstance);

    pAnalyticsInstance->setDebugMode(true);
    pAnalyticsInstance->setCaptureUncaughtException(true);

    if (pUmeng != NULL)
    {
        pUmeng->updateOnlineConfig();
        pUmeng->setDefaultReportPolicy(AnalyticsUmeng::REALTIME);
        // The app key of umeng must be set in AndroidManifest.xml, so you don't need to set it here.
        pUmeng->startSession("");
    }

    if (pFlurry != NULL)
    {
        pFlurry->setReportLocation(true);
        pFlurry->logPageView();
        int sdkVersion = pFlurry->getAgentVersion();
        CCLog("Flurry sdk version = %d", sdkVersion);
        pFlurry->setVersionName("1.1");
        pFlurry->setAge(20);
        pFlurry->setGender(AnalyticsFlurry::MALE);
        pFlurry->setUserId("123456");
        pFlurry->setUseHttps(false);
        pFlurry->startSession(FLURRY_KEY);
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
    AnalyticsManager::getAnalytics()->stopSession();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();

    AnalyticsType type = AnalyticsManager::getAnalyticsType();
    if (type == kAnalyticsType_Umeng)
    {
        AnalyticsManager::getAnalytics()->startSession("");
    }
    else if (type == kAnalyticsType_Flurry)
    {
        AnalyticsManager::getAnalytics()->startSession(FLURRY_KEY);
    }

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
