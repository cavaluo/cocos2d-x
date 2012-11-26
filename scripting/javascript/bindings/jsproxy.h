#ifndef __JSPROXY_H__
#define __JSPROXY_H__

#include <map>
#include "cocos2d.h"
#include "jsapi.h"


USING_NS_CC;

struct js_proxy;
class JSScheduleWrapper;

typedef struct tagJSProxy
{
    CCObject *nobj;
    JSObject *jsobj;
    char class_name[50];
    struct js_proxy* p_old;
}JSProxy;

typedef std::map<CCObject*, JSProxy*> NativeKeyMap;
typedef std::pair<CCObject*, JSProxy*> NativePair;

typedef std::map<JSObject*, JSProxy*> JSObjectKeyMap;
typedef std::pair<JSObject*, JSProxy*> JSPair;

class JSBindingProxy
{
public:
    JSProxy* GetProxyByNativeObj(CCObject* nobj) const;
    JSProxy* GetProxyByJSObj(JSObject* jsobj) const;
    void NewProxy(CCObject* nobj, JSObject* jsobj, struct js_proxy* p_old);
    void RemoveProxy(CCObject* nobj, JSObject* jsobj);
    void RemoveAll();
    const NativeKeyMap& GetNativeKeyMap() const;
    const JSObjectKeyMap& GetJSObjectKeyMap() const;
protected:
    NativeKeyMap m_nativeKeyMap;
    JSObjectKeyMap m_jsKeyMap;
};


#endif /* __JSPROXY_H__ */
