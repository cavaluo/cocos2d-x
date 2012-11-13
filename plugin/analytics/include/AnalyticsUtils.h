#ifndef __ANALYTICSUTILS_H__
#define __ANALYTICSUTILS_H__

#include "jni/JniHelper.h"
#include <android/log.h>
#include "AnalyticsProtocol.h"

namespace cocos2d { namespace plugin {

#define return_if_fails(cond) if (!(cond)) return; 
#define return_val_if_fails(cond, ret) if(!(cond)) return (ret);

jobject createJavaMapObject(JniMethodInfo&t, const LogEventParamMap* pParamMap);

}} // namespace cocos2d { namespace plugin {

#endif /* __ANALYTICSUTILS_H__ */
