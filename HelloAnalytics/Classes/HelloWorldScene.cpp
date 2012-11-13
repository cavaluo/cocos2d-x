#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameAnalytics.h"

using namespace cocos2d;
using namespace CocosDenshion;

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

    return true;
}

void HelloWorld::eventMenuCallback(CCObject* pSender)
{
    CCMenuItemLabel* pMenuItem = (CCMenuItemLabel*)pSender;
    switch (pMenuItem->getTag())
    {
    case TAG_LOG_EVENT_ID:
        {
            GameAnalytics::getAnalytics()->logEvent("click");
            GameAnalytics::getAnalytics()->logEvent("music");
        }
        break;
    case TAG_LOG_EVENT_ID_KV:
        {
            LogEventParamMap paramMap;
            paramMap.insert(LogEventParamPair("type", "popular"));
            paramMap.insert(LogEventParamPair("artist", "JJLin"));
            GameAnalytics::getAnalytics()->logEvent("music", &paramMap);
        }
        break;
    case TAG_LOG_ONLINE_CONFIG:
        {
#if (TARGET_ANALYTICS == ANALYTICS_UMENG)
            CCLog("Online config = %s", GameAnalytics::getAnalytics()->getConfigParams("abc"));
#endif            
        }
        break;
    case TAG_LOG_EVENT_ID_DURATION:
        {
#if (TARGET_ANALYTICS == ANALYTICS_UMENG)
            GameAnalytics::getAnalytics()->logEventWithDuration("book", 12000);
            GameAnalytics::getAnalytics()->logEventWithDuration("book", 23000, "chapter1");
            LogEventParamMap paramMap;
            paramMap.insert(LogEventParamPair("type", "popular"));
            paramMap.insert(LogEventParamPair("artist", "JJLin"));
            GameAnalytics::getAnalytics()->logEventWithDuration("music", 2330000, &paramMap);
#endif            
        }
        break;
    case TAG_LOG_EVENT_BEGIN:
        {
            GameAnalytics::getAnalytics()->logTimedEventBegin("music");

            LogEventParamMap paramMap;
            paramMap.insert(LogEventParamPair("type", "popular"));
            paramMap.insert(LogEventParamPair("artist", "JJLin"));
#if (TARGET_ANALYTICS == ANALYTICS_UMENG)
            GameAnalytics::getAnalytics()->logTimedEventWithLabelBegin("music", "one");
            GameAnalytics::getAnalytics()->logTimedKVEventBegin("music", "flag0", &paramMap);
#elif (TARGET_ANALYTICS == ANALYTICS_FLURRY)
            GameAnalytics::getAnalytics()->logTimedEventBegin("music-kv", &paramMap);
#endif
        }
        break;
    case TAG_LOG_EVENT_END:
        {
            GameAnalytics::getAnalytics()->logTimedEventEnd("music");
#if (TARGET_ANALYTICS == ANALYTICS_UMENG)            
            GameAnalytics::getAnalytics()->logTimedEventWithLabelEnd("music", "one");
            GameAnalytics::getAnalytics()->logTimedKVEventEnd("music", "flag0");
#elif (TARGET_ANALYTICS == ANALYTICS_FLURRY)
            GameAnalytics::getAnalytics()->logTimedEventEnd("music-kv");
#endif
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
