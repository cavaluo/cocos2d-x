#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "PluginManager.h"
#include "AnalyticsFlurry.h"
#include "AnalyticsUmeng.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::plugin;

extern AnalyticsUmeng* g_pUmeng;
extern AnalyticsFlurry* g_pFlurry;

enum {
    TAG_LOG_EVENT_ID = 0,
    TAG_LOG_EVENT_ID_KV,
    TAG_LOG_ONLINE_CONFIG,
    TAG_LOG_EVENT_ID_DURATION,
    TAG_LOG_EVENT_BEGIN,
    TAG_LOG_EVENT_END,
    TAG_MAKE_ME_CRASH
};

typedef struct tagEventMenuItem {
    std::string id;
    int tag;
}EventMenuItem;

static EventMenuItem s_EventMenuItem[] = {
    {"OnlineConfig",        TAG_LOG_ONLINE_CONFIG},
    {"LogEvent-eventId"   , TAG_LOG_EVENT_ID},
    {"LogEvent-eventId-kv", TAG_LOG_EVENT_ID_KV},
    {"LogEvent-eventId-Duration", TAG_LOG_EVENT_ID_DURATION},
    {"LogEvent-Begin", TAG_LOG_EVENT_BEGIN},
    {"LogEvent-End", TAG_LOG_EVENT_END},
    {"MakeMeCrash", TAG_MAKE_ME_CRASH}
};

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(size.width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    for (int i = 0; i < sizeof(s_EventMenuItem)/sizeof(s_EventMenuItem[0]); i++) {
        CCLabelTTF* label = CCLabelTTF::create(s_EventMenuItem[i].id.c_str(), "Arial", 24);
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(HelloWorld::eventMenuCallback));
        pMenu->addChild(pMenuItem, 0, s_EventMenuItem[i].tag);
        pMenuItem->setPosition( ccp(size.width / 2, size.height - 50*i - 100));
    }

    CCLabelTTF* label = CCLabelTTF::create("reload all plugins", "Arial", 24);
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(HelloWorld::reloadPluginMenuCallback));
    pMenuItem->setAnchorPoint(ccp(0.5f, 0));
    pMenu->addChild(pMenuItem, 0);
    pMenuItem->setPosition( ccp(size.width / 2, 0));

    return true;
}

void HelloWorld::reloadPluginMenuCallback(CCObject* pSender)
{
    PluginManager::getInstance()->unloadPlugin("AnalyticsFlurry");
    PluginManager::getInstance()->unloadPlugin("AnalyticsUmeng");

    PluginProtocol* pPlugin = NULL;
    pPlugin = PluginManager::getInstance()->loadPlugin("AnalyticsFlurry");
    g_pFlurry = dynamic_cast<AnalyticsFlurry*>(pPlugin);
    pPlugin = PluginManager::getInstance()->loadPlugin("AnalyticsUmeng");
    g_pUmeng = dynamic_cast<AnalyticsUmeng*>(pPlugin);
}

void HelloWorld::eventMenuCallback(CCObject* pSender)
{
    CCMenuItemLabel* pMenuItem = (CCMenuItemLabel*)pSender;
    switch (pMenuItem->getTag())
    {
    case TAG_LOG_EVENT_ID:
        {
            g_pUmeng->logEvent("click");
            g_pUmeng->logEvent("music");
            g_pFlurry->logEvent("click");
            g_pFlurry->logEvent("music");
        }
        break;
    case TAG_LOG_EVENT_ID_KV:
        {
            LogEventParamMap paramMap;
            paramMap.insert(LogEventParamPair("type", "popular"));
            paramMap.insert(LogEventParamPair("artist", "JJLin"));
            g_pUmeng->logEvent("music", &paramMap);
            g_pFlurry->logEvent("music", &paramMap);
        }
        break;
    case TAG_LOG_ONLINE_CONFIG:
        {
            if (g_pUmeng != NULL)
            {
                CCLog("Online config = %s", g_pUmeng->getConfigParams("abc"));           
            }
        }
        break;
    case TAG_LOG_EVENT_ID_DURATION:
        {
            if (g_pUmeng != NULL)
            {
                g_pUmeng->logEventWithDuration("book", 12000);
                g_pUmeng->logEventWithDuration("book", 23000, "chapter1");
                LogEventParamMap paramMap;
                paramMap.insert(LogEventParamPair("type", "popular"));
                paramMap.insert(LogEventParamPair("artist", "JJLin"));
                g_pUmeng->logEventWithDuration("music", 2330000, &paramMap);
            }            
        }
        break;
    case TAG_LOG_EVENT_BEGIN:
        {
            g_pUmeng->logTimedEventBegin("music");
            g_pFlurry->logTimedEventBegin("music");

            LogEventParamMap paramMap;
            paramMap.insert(LogEventParamPair("type", "popular"));
            paramMap.insert(LogEventParamPair("artist", "JJLin"));
            if (g_pUmeng != NULL)
            {
                g_pUmeng->logTimedEventWithLabelBegin("music", "one");
                g_pUmeng->logTimedKVEventBegin("music", "flag0", &paramMap);
            }
            else if (g_pFlurry != NULL)
            {
                g_pFlurry->logTimedEventBegin("music-kv", &paramMap);
            }
        }
        break;
    case TAG_LOG_EVENT_END:
        {
            g_pUmeng->logTimedEventEnd("music");
            g_pFlurry->logTimedEventEnd("music");
            if (g_pUmeng != NULL)
            {          
                g_pUmeng->logTimedEventWithLabelEnd("music", "one");
                g_pUmeng->logTimedKVEventEnd("music", "flag0");
            }
            else if (g_pFlurry != NULL)
            {
                g_pFlurry->logTimedEventEnd("music-kv");
            }
        }
        break;
    case TAG_MAKE_ME_CRASH:
        {
            char* pNull = NULL;
            *pNull = 0;
        }
        break;
    default:
        break;
    }
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
