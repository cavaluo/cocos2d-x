#include "jsproxy.h"
#include "spidermonkey_specifics.h"
#include "ScriptingCore.h"

JSProxy* JSBindingProxy::GetProxyByNativeObj(CCObject* nobj) const
{
    bool bFound = false;
    bFound = m_nativeKeyMap.find(nobj) != m_nativeKeyMap.end();
    if (bFound) return m_nativeKeyMap.at(nobj);
    return NULL;
}

JSProxy* JSBindingProxy::GetProxyByJSObj(JSObject* jsobj) const
{
    bool bFound = false;
    bFound = m_jsKeyMap.find(jsobj) != m_jsKeyMap.end();
    if (bFound) return m_jsKeyMap.at(jsobj);
    return NULL;
}
    
void JSBindingProxy::NewProxy(CCObject* nobj, JSObject* jsobj, struct js_proxy* p_old)
{
    JSProxy* p = new JSProxy();
    p->nobj = nobj;
    p->jsobj = jsobj;
    p->p_old = p_old;

    strncpy(p->class_name, typeid(*nobj).name(), sizeof(p->class_name));
    if (m_nativeKeyMap.find(nobj) != m_nativeKeyMap.end())
    {
        CCAssert(false, "native key pair exists");
    }
    m_nativeKeyMap.insert(NativePair(nobj, p));

    if (m_jsKeyMap.find(jsobj) != m_jsKeyMap.end())
    {
        CCAssert(false, "js key pair exists");
    }
    m_jsKeyMap.insert(JSPair(jsobj, p));
#ifdef DEBUG
    JS_AddNamedObjectRoot(ScriptingCore::getInstance()->getGlobalContext(), &p->jsobj, typeid(*nobj).name());
#else
    JS_AddObjectRoot(ScriptingCore::getInstance()->getGlobalContext(), &p->jsobj);
#endif
}

void JSBindingProxy::RemoveProxy(CCObject* nobj, JSObject* jsobj)
{
    bool bFound = false;
    JSProxy* nativeProxy = NULL;
    JSProxy* jsobjectProxy = NULL;

    bFound = m_nativeKeyMap.find(nobj) != m_nativeKeyMap.end();
    CCAssert(bFound, "no found proxy need to be removed");
    nativeProxy = m_nativeKeyMap.at(nobj);
    
    bFound = m_jsKeyMap.find(jsobj) != m_jsKeyMap.end();
    CCAssert(bFound, "no found proxy need to be removed");
    jsobjectProxy = m_jsKeyMap.at(jsobj);
    CCAssert(nativeProxy == jsobjectProxy, "need equal.");

    JS_RemoveObjectRoot(ScriptingCore::getInstance()->getGlobalContext(), &nativeProxy->jsobj);

    m_nativeKeyMap.erase(nobj);
    m_jsKeyMap.erase(jsobj);

    free(nativeProxy->p_old);
    delete nativeProxy;
}

void JSBindingProxy::RemoveAll()
{
    NativeKeyMap::iterator nativeIter = m_nativeKeyMap.begin();
    for (; nativeIter != m_nativeKeyMap.end(); ++nativeIter)
    {
        JSObject* jsobj = nativeIter->second->jsobj;
        JS_RemoveObjectRoot(ScriptingCore::getInstance()->getGlobalContext(), &jsobj);
        free(nativeIter->second->p_old);
        delete(nativeIter->second);
    }
    m_nativeKeyMap.clear();
    m_jsKeyMap.clear();
}

const NativeKeyMap& JSBindingProxy::GetNativeKeyMap() const
{
    return m_nativeKeyMap;
}

const JSObjectKeyMap& JSBindingProxy::GetJSObjectKeyMap() const
{
    return m_jsKeyMap;
}
