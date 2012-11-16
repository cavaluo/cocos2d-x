#ifndef __ANALYTICSDATA_ANDROID_H__
#define __ANALYTICSDATA_ANDROID_H__

#include <string>
#include <jni.h>

namespace cocos2d { namespace plugin {

typedef struct tagAnalyticsData
{
	jobject jobj;
	std::string  jclassName;
}AnalyticsData;

}} //namespace cocos2d { namespace plugin {

#endif /* __ANALYTICSDATA_ANDROID_H__ */
