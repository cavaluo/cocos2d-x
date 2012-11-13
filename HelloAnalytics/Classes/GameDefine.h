#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__


#define ANALYTICS_UMENG   0
#define ANALYTICS_FLURRY  1

#define TARGET_ANALYTICS  ANALYTICS_FLURRY

#if (TARGET_ANALYTICS == ANALYTICS_UMENG)
#include "Analytics_umeng.h"
#elif (TARGET_ANALYTICS == ANALYTICS_FLURRY)
#include "Analytics_flurry.h"
#endif

using namespace cocos2d::plugin;

#endif /* __GAME_DEFINE_H__ */
