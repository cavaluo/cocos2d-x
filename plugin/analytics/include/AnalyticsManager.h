#ifndef __ANALYTICSMANAGER_H__
#define __ANALYTICSMANAGER_H__

#include "Analytics_umeng.h"
#include "Analytics_flurry.h"

namespace cocos2d { namespace plugin {

enum AnalyticsType
{
	kAnalyticsType_Umeng = 0,
	kAnalyticsType_Flurry
};

class AnalyticsManager
{
public:
	static void setAnalyticsType(AnalyticsType type);
	static AnalyticsType getAnalyticsType();
	static AnalyticsProtocol* getAnalytics();
	static void destory();
};

}} //namespace cocos2d { namespace plugin {

#endif /* __ANALYTICSMANAGER_H__ */
