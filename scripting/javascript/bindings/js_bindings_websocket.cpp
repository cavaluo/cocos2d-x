#include "js_bindings_websocket.h"
#include "chat_client_handler.hpp"
#include "cocos2d.h"
#include "js_bindings_config.h"
#include "js_bindings_core.h"

#include "spidermonkey_specifics.h"
#include "ScriptingCore.h"

#include "handshake.h"

using namespace websocketchat;


chat_client_handler_ptr createWebSocket(const char* url);

typedef std::pair<JSObject*, chat_client_handler_ptr> ClientPair;
typedef std::map<JSObject*, chat_client_handler_ptr> ClientMap;

static ClientMap s_client_map;

JSClass  *jsb_websocket_class = NULL;
JSObject *jsb_websocket_prototype = NULL;

class WebsocketSchedulerWrapper : public CCObject
{
public:
    void scheduleUpdate(float dt);
};

static pthread_mutex_t s_ws_mutex;
static WsEvent s_evt;

//
void WebsocketSchedulerWrapper::scheduleUpdate(float dt)
{
    pthread_mutex_lock(&s_ws_mutex);
    do
    {
        if (s_evt.type == WS_EVENT_NONE) {
            
            break;
        }
        
        const char* jsFuncName = NULL;
        if (s_evt.type == WS_EVENT_OPENED) {
            jsFuncName = "onopen";
        }
        else if (s_evt.type == WS_EVENT_CLOSED) {
            jsFuncName = "onclose";
        }
        else if (s_evt.type == WS_EVENT_MSG) {
            jsFuncName = "onmessage";
        }
        else if (s_evt.type == WS_EVENT_ERROR) {
            jsFuncName = "onerror";
        }
        else {
            CCAssert(0, "Unknown event type");
        }
        CCLog("msg = %d, %s", s_evt.type, s_evt.msg.c_str());
        for (ClientMap::iterator it = s_client_map.begin(); it != s_client_map.end(); ++it) {
            if (it->second.get() == (chat_client_handler*)(s_evt.handler)) {
                CCLog("Found.");
                JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
                JSString* str = JS_NewStringCopyZ(cx, s_evt.msg.c_str());
                JSObject* jsEvtObj = JS_NewObject(cx, NULL, NULL, NULL);
                jsval arg = STRING_TO_JSVAL(str);
                JS_SetProperty(cx, jsEvtObj, "data", &arg);
                
                ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(it->first), jsFuncName, OBJECT_TO_JSVAL(jsEvtObj));
                break;
            }
        }
    }while(false);
    s_evt.type = WS_EVENT_NONE;
    s_evt.msg = "";
    pthread_mutex_unlock(&s_ws_mutex);
}

void postWebsocketEvent(const WsEvent& evt)
{
    pthread_mutex_lock(&s_ws_mutex);
    s_evt.handler = evt.handler;
    s_evt.type = evt.type;
    s_evt.msg = evt.msg;
    pthread_mutex_unlock(&s_ws_mutex);
}

static JSBool jsb_handshake(JSContext* cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
        JSBool ok  = JS_TRUE;
        jsval *argv = JS_ARGV(cx, vp);
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        std::string url;
        ok &= jsval_to_std_string(cx, argv[0], &url);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        std::string ret = handshake(url);
        JSString* jsstrRet = JS_NewStringCopyZ(cx, ret.c_str());
        JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(jsstrRet));
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

void jsb_register_websocket(JSContext *cx, JSObject *global) {
    
    JS_DefineFunction(cx, global, "__handshake", jsb_handshake, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    jsb_websocket_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_websocket_class->name = "WebSocket";
    jsb_websocket_class->addProperty = JS_PropertyStub;
    jsb_websocket_class->delProperty = JS_PropertyStub;
    jsb_websocket_class->getProperty = JS_PropertyStub;
    jsb_websocket_class->setProperty = JS_StrictPropertyStub;
    jsb_websocket_class->enumerate = JS_EnumerateStub;
    jsb_websocket_class->resolve = JS_ResolveStub;
    jsb_websocket_class->convert = JS_ConvertStub;
    jsb_websocket_class->finalize = jsb_websocket_finalize;
    jsb_websocket_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {0, 0, 0, 0, 0}
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("send", jsb_websocket_send, 1, JSPROP_PERMANENT | JSPROP_SHARED),
        JS_FN("close", jsb_websocket_close, 0, JSPROP_PERMANENT | JSPROP_SHARED),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FS_END
    };

    jsb_websocket_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_websocket_class,
        jsb_websocket_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "WebSocket", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
    // add the proto and JSClass to the type->js info hash table
	js_type_class_t *p;
	uint32_t typeId = cocos2d::getHashCodeByString("WebSocket"); 
    
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_websocket_class;
		p->proto = jsb_websocket_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
    
    pthread_mutex_init(&s_ws_mutex, NULL);
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    WebsocketSchedulerWrapper* pWrapper = new WebsocketSchedulerWrapper();
    pWrapper->autorelease();
    pDirector->getScheduler()->scheduleSelector(schedule_selector(WebsocketSchedulerWrapper::scheduleUpdate), pWrapper, 0.0f, false);
}

JSBool jsb_websocket_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
        JSBool ok = JS_TRUE;
        jsval *argv = JS_ARGV(cx, vp);
		js_type_class_t *typeClass;
		uint32_t typeId = cocos2d::getHashCodeByString("WebSocket"); 
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);

		std::string url;
        ok &= jsval_to_std_string(cx, argv[0], &url);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
        // createWebSocket need to return an object, it will be used in 'close' function.
        chat_client_handler_ptr handler = createWebSocket(url.c_str());
        handler->setJSObject(obj);
        
        s_client_map.insert(ClientPair(obj, handler));
        
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return JS_FALSE;
}


void jsb_websocket_finalize(JSFreeOp *fop, JSObject *obj) {
}


JSBool jsb_websocket_send(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
        JSBool ok  = JS_TRUE;
        jsval *argv = JS_ARGV(cx, vp);
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        std::string msg;
        ok &= jsval_to_std_string(cx, argv[0], &msg);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        ClientMap::iterator iter = s_client_map.find(obj);
        if (iter != s_client_map.end())
        {
            iter->second->send(msg);
        }
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool jsb_websocket_close(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        ClientMap::iterator iter = s_client_map.find(obj);
        if (iter != s_client_map.end())
        {
            iter->second->close();
        }
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
