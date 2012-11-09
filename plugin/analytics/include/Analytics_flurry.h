#ifndef __CCX_ANALYTICS_FLURRY_H__
#define __CCX_ANALYTICS_FLURRY_H__

#include "Analytics.h"

namespace cocos2d { namespace plugin {

class AnalyticsFlurry : public Analytics
{
public:
	int  getAgentVersion();
	void setVersionName(const char* versionName);
	void setAge(int age);
	void setGender(char gender);
	void setUserId(const char* userId);
	void setUseHttps(bool isUseHttps);
	
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_ANALYTICS_FLURRY_H__ */
