#ifndef __CCX_ANALYTICS_UMENG_H__
#define __CCX_ANALYTICS_UMENG_H__

#include "AnalyticsProtocol.h"

namespace cocos2d { namespace plugin {

class AnalyticsUmeng : public AnalyticsProtocol
{
	PLUGIN_REGISTER_DECL()
public:
	enum ReportPolicy
	{
		REALTIME = 0,
		BATCH_AT_LAUNCH = 1,
		DAILY = 4,
		WIFIONLY = 5
	};
	AnalyticsUmeng();
	~AnalyticsUmeng();

	void updateOnlineConfig();
	const char* getConfigParams(const char* key);
	void setDefaultReportPolicy(ReportPolicy policy);

	void logEventWithLabel(const char* eventId, const char* label);
	void logEventWithDuration(const char* eventId, long duration, const char* label);
	void logEventWithDuration(const char* eventId, long duration, const LogEventParamMap* paramMap = NULL);

	void logTimedEventWithLabelBegin(const char* eventId, const char* label);
	void logTimedEventWithLabelEnd(const char* eventId, const char* label);

	void logTimedKVEventBegin(const char* eventId, const char* label, const LogEventParamMap* paramMap);
	void logTimedKVEventEnd(const char* eventId, const char* label);
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_ANALYTICS_UMENG_H__ */
