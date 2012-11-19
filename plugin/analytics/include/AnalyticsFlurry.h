#ifndef __CCX_ANALYTICS_FLURRY_H__
#define __CCX_ANALYTICS_FLURRY_H__

#include "AnalyticsProtocol.h"

namespace cocos2d { namespace plugin {

class AnalyticsFlurry : public AnalyticsProtocol
{
	PLUGIN_REGISTER_DECL()
public:
	enum Gender{
	    FEMALE = 0,
	    MALE = 1
	};
	AnalyticsFlurry();
	~AnalyticsFlurry();
	virtual bool init();
	
	/** @brief Enable or disable detailed location reporting.
	 *  @note It must be invoked before calling startSession.
	 */
	void setReportLocation(bool enabled);
	/** Log a page view. */
	void logPageView();
	/** Get the version of the Flurry SDK. */
	int  getAgentVersion();
	/** Set the version name of the app. */
	void setVersionName(const char* versionName);
	/** Sets the age of the user at the time of this session. */
	void setAge(int age);
	/** Sets the gender of the user. */
	void setGender(Gender gender);
	/** Sets the Flurry userId for this session. */
	void setUserId(const char* userId);
	/** Enable the use of HTTPS communications. */
	void setUseHttps(bool useHttps);
	
	virtual void logTimedEventBegin(const char* eventId);
	/** Log a timed event with parameters. */
	void logTimedEventBegin(const char* eventId, const LogEventParamMap* paramMap);
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_ANALYTICS_FLURRY_H__ */
