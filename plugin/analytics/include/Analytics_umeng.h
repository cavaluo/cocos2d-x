#ifndef __CCX_ANALYTICS_UMENG_H__
#define __CCX_ANALYTICS_UMENG_H__

#include "Analytics.h"

namespace cocos2d { namespace plugin {

class AnalyticsUmeng : public AnalyticsProtocol
{
public:
	enum ReportPolicy
	{
		REALTIME = 0,
		BATCH_AT_LAUNCH = 1,
		DAILY = 4,
		WIFIONLY = 5
	};

	void updateOnlineConfig();
	const char* getConfigParams(const char* key);
	void setDefaultReportPolicy(ReportPolicy ePolicy);

	void logEventWithLabel(const char* eventId, const char* label);
	void logEventWithDuration(const char* eventId, long duration, const char* label);
	void logEventWithDuration(const char* eventId, long duration, const LogEventParamMap* pParamMap = NULL);

	void logTimedEventWithLabelBegin(const char* eventId, const char* label);
	void logTimedEventWithLabelEnd(const char* eventId, const char* label);

	void logTimedKVEventBegin(const char* eventId, const char* label, const LogEventParamMap* pParamMap);
	void logTimedKVEventEnd(const char* eventId, const char* label);
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_ANALYTICS_UMENG_H__ */
