#include "AnalyticsUtils.h"

namespace cocos2d { namespace plugin {

jobject createJavaMapObject(JniMethodInfo&t, const LogEventParamMap* pParamMap)
{
	jclass class_Hashtable = t.env->FindClass("java/util/Hashtable"); 
	jmethodID construct_method = t.env->GetMethodID( class_Hashtable, "<init>","()V"); 
	jobject obj_Map = t.env->NewObject( class_Hashtable, construct_method, "");
	if (pParamMap != NULL)
	{
		jmethodID add_method= t.env->GetMethodID( class_Hashtable,"put","(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;"); 
		for (LogEventParamMap::const_iterator it = pParamMap->begin(); it != pParamMap->end(); ++it)
		{
			t.env->CallObjectMethod(obj_Map, add_method, t.env->NewStringUTF(it->first.c_str()), t.env->NewStringUTF(it->second.c_str()));  
		}
	}
    t.env->DeleteLocalRef(class_Hashtable);
    return obj_Map;
}

}}// namespace cocos2d { namespace plugin {
