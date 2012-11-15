#include "AnalyticsFlurry.h"
#include "jni/JniHelper.h"
#include <android/log.h>
#include "AnalyticsUtils.h"

#if 1
#define  LOG_TAG    "AnalyticsFlurry"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

namespace cocos2d { namespace plugin {

PLUGIN_REGISTER_IMPL(AnalyticsFlurry)

AnalyticsFlurry::AnalyticsFlurry()
{
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsFlurry"
		, "init"
		, "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setReportLocation(bool enabled)
{
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsFlurry"
		, "setReportLocation"
		, "(Z)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, enabled);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::logPageView()
{
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsFlurry"
		, "logPageView"
		, "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

int  AnalyticsFlurry::getAgentVersion()
{
	int ret = 0;
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsFlurry"
		, "getAgentVersion"
		, "()I"))
	{
		ret = t.env->CallStaticIntMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
	return ret;
}

void AnalyticsFlurry::setVersionName(const char* versionName)
{
	return_if_fails(versionName != NULL && strlen(versionName) > 0);
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsFlurry"
		, "setVersionName"
		, "(Ljava/lang/String;)V"))
	{
		jstring jversionName = t.env->NewStringUTF(versionName);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jversionName);
		t.env->DeleteLocalRef(jversionName);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setAge(int age)
{
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsFlurry"
		, "setAge"
		, "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, age);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setGender(Gender gender)
{
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsFlurry"
		, "setGender"
		, "(B)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, (jbyte)gender);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setUserId(const char* userId)
{
	return_if_fails(userId != NULL && strlen(userId) > 0);
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsFlurry"
		, "setUserId"
		, "(Ljava/lang/String;)V"))
	{
		jstring juserId = t.env->NewStringUTF(userId);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, juserId);
		t.env->DeleteLocalRef(juserId);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setUseHttps(bool useHttps)
{
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsFlurry"
		, "setUseHttps"
		, "(Z)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, useHttps);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::logTimedEventBegin(const char* eventId)
{
	AnalyticsProtocol::logTimedEventBegin(eventId);
}

void AnalyticsFlurry::logTimedEventBegin(const char* eventId, const LogEventParamMap* pParamMap)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	
	if (pParamMap == NULL)
	{
		AnalyticsProtocol::logTimedEventBegin(eventId);
	}
	else
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t
			, "org/cocos2dx/plugin/AnalyticsFlurry"
			, "logTimedEventBegin"
			, "(Ljava/lang/String;Ljava/util/Hashtable;)V"))
		{
			jstring jeventId = t.env->NewStringUTF(eventId);
			jobject jparamMap= createJavaMapObject(t, pParamMap);
			t.env->CallStaticVoidMethod(t.classID, t.methodID, jeventId, jparamMap);
			t.env->DeleteLocalRef(jeventId);
			t.env->DeleteLocalRef(jparamMap);
			t.env->DeleteLocalRef(t.classID);
		}
	}
}

}} // namespace cocos2d { namespace plugin {