#ifndef __CCX_ANALYTICS_UMENG_H__
#define __CCX_ANALYTICS_UMENG_H__

#include "Analytics.h"

namespace cocos2d { namespace plugin {

class AnalyticsUmeng : public Analytics
{
public:
	enum ReportPolicy
	{
		BATCH_AT_LAUNCH = 0,
		REALTIME,
		DAILY,
		WIFIONLY
	}
	const char* getConfigParams(const char* key);
	void setDefaultReportPolicy(ReportPolicy ePolicy);

	void logEventWithLabel(const char* eventId, const char* label);
	void logEventWithDuration(const char* eventId, long duration);
	void logEventWithDuration(const char* eventId, long duration, const char* label);
	void logEventWithDuration(const char* eventId, long duration, const EventParamsMap* pParams);
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_ANALYTICS_UMENG_H__ */
