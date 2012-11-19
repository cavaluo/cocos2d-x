#ifndef __CCX_ANALYTICS_UMENG_H__
#define __CCX_ANALYTICS_UMENG_H__

#include "AnalyticsProtocol.h"

namespace cocos2d { namespace plugin {

// Please refer to http://dev.umeng.com/doc/document_ana_android.html for the detail informations about
// how to use the interfaces of Umeng.

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
	virtual bool init();
	/** Update the online configuration */
	void updateOnlineConfig();
	/** Get the online configuration parameters */
	const char* getConfigParams(const char* key);
	/** Set the default policy */
	void setDefaultReportPolicy(ReportPolicy policy);

	/** Log event with a label.
	 * @note The label param is for distinguish event that with the same id. It will not be kept in the server.
	 */
	void logEventWithLabel(const char* eventId, const char* label);
	/** Log event with duration and a label 
	 * @note The label param is for distinguish event that with the same id. It will not be kept in the server.
     */
	void logEventWithDuration(const char* eventId, long duration, const char* label);
	/** Log event with duration and a map which contains event parameters. 
	 * @note The label param is for distinguish event that with the same id. It will not be kept in the server.
     */
	void logEventWithDuration(const char* eventId, long duration, const LogEventParamMap* paramMap = NULL);
	/** Start log a timed event with a label. */
	void logTimedEventWithLabelBegin(const char* eventId, const char* label);
	/** Finish log a timed event with a label */
	void logTimedEventWithLabelEnd(const char* eventId, const char* label);
	/** Start log a timed event with a label and a map which contains event parameters. */
	void logTimedKVEventBegin(const char* eventId, const char* label, const LogEventParamMap* paramMap);
	/** Finish log a timed event with a label. */ 
	void logTimedKVEventEnd(const char* eventId, const char* label);
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_ANALYTICS_UMENG_H__ */
