#include "AnalyticsFlurry.h"
#include "jni/JniHelper.h"
#include <android/log.h>
#include "AnalyticsUtils.h"
#include "AnalyticsData_android.h"

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
	AnalyticsData* pData = (AnalyticsData*)this->getUserData();
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, pData->jclassName.c_str()
		, "init"
		, "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

AnalyticsFlurry::~AnalyticsFlurry()
{

}

void AnalyticsFlurry::setReportLocation(bool enabled)
{
	AnalyticsData* pData = (AnalyticsData*)this->getUserData();
	JniMethodInfo t; 
	if (JniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setReportLocation"
		, "(Z)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, enabled);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::logPageView()
{
	AnalyticsData* pData = (AnalyticsData*)this->getUserData();
	JniMethodInfo t; 
	if (JniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "logPageView"
		, "()V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

int  AnalyticsFlurry::getAgentVersion()
{
	AnalyticsData* pData = (AnalyticsData*)this->getUserData();
	int ret = 0;
	JniMethodInfo t; 
	if (JniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "getAgentVersion"
		, "()I"))
	{
		ret = t.env->CallIntMethod(pData->jobj, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
	return ret;
}

void AnalyticsFlurry::setVersionName(const char* versionName)
{
	return_if_fails(versionName != NULL && strlen(versionName) > 0);
	AnalyticsData* pData = (AnalyticsData*)this->getUserData();
	JniMethodInfo t; 
	if (JniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setVersionName"
		, "(Ljava/lang/String;)V"))
	{
		jstring jversionName = t.env->NewStringUTF(versionName);
		t.env->CallVoidMethod(pData->jobj, t.methodID, jversionName);
		t.env->DeleteLocalRef(jversionName);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setAge(int age)
{
	AnalyticsData* pData = (AnalyticsData*)this->getUserData();
	JniMethodInfo t; 
	if (JniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setAge"
		, "(I)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, age);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setGender(Gender gender)
{
	AnalyticsData* pData = (AnalyticsData*)this->getUserData();
	JniMethodInfo t; 
	if (JniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setGender"
		, "(B)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, (jbyte)gender);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setUserId(const char* userId)
{
	AnalyticsData* pData = (AnalyticsData*)this->getUserData();
	return_if_fails(userId != NULL && strlen(userId) > 0);
	JniMethodInfo t; 
	if (JniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setUserId"
		, "(Ljava/lang/String;)V"))
	{
		jstring juserId = t.env->NewStringUTF(userId);
		t.env->CallVoidMethod(pData->jobj, t.methodID, juserId);
		t.env->DeleteLocalRef(juserId);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setUseHttps(bool useHttps)
{
	AnalyticsData* pData = (AnalyticsData*)this->getUserData();
	JniMethodInfo t; 
	if (JniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setUseHttps"
		, "(Z)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, useHttps);
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
		AnalyticsData* pData = (AnalyticsData*)this->getUserData();
		JniMethodInfo t;
		if (JniHelper::getMethodInfo(t
			, pData->jclassName.c_str()
			, "logTimedEventBegin"
			, "(Ljava/lang/String;Ljava/util/Hashtable;)V"))
		{
			jstring jeventId = t.env->NewStringUTF(eventId);
			jobject jparamMap= createJavaMapObject(t, pParamMap);
			t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId, jparamMap);
			t.env->DeleteLocalRef(jeventId);
			t.env->DeleteLocalRef(jparamMap);
			t.env->DeleteLocalRef(t.classID);
		}
	}
}

}} // namespace cocos2d { namespace plugin {