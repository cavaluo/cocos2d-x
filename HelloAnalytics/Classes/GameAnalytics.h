#ifndef __GAMEANALYTICS_H__
#define __GAMEANALYTICS_H__

#include "GameDefine.h"

class GameAnalytics
{
public:
#if (TARGET_ANALYTICS == ANALYTICS_UMENG)
	static AnalyticsUmeng* getAnalytics();
#elif (TARGET_ANALYTICS == ANALYTICS_FLURRY)
	static AnalyticsFlurry* getAnalytics();
#endif
	static void destory();
};

#endif /* __GAMEANALYTICS_H__ */
