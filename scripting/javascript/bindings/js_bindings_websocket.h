#ifndef __JS_BINDINGS_WEBSOCKET_REGISTRATION_H__
#define __JS_BINDINGS_WEBSOCKET_REGISTRATION_H__

#include <string>

#include "jsapi.h"
#include "WSClient.h"
using namespace socketio;



extern JSClass  *jsb_websocket_class;
extern JSObject *jsb_websocket_prototype;

JSBool jsb_websocket_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void jsb_websocket_finalize(JSFreeOp *fop, JSObject *obj);

JSBool jsb_websocket_send(JSContext *cx, uint32_t argc, jsval *vp);
JSBool jsb_websocket_close(JSContext *cx, uint32_t argc, jsval *vp);

void jsb_register_websocket( JSContext *globalC, JSObject *globalO);

enum WsEventType{
    WS_EVENT_NONE,
    WS_EVENT_OPENED,
    WS_EVENT_CLOSED,
    WS_EVENT_MSG,
    WS_EVENT_ERROR
};

typedef struct tagWsEvent
{
    void* handler;
    WsEventType type;
    std::string msg;
    tagWsEvent()
    {
        handler = NULL;
        type = WS_EVENT_NONE;
        msg = "";
    }
}WsEvent;

//void postWebsocketEvent(websocketchat::chat_client_handler handler, WsEvent evt);

#endif /* __JS_BINDINGS_WEBSOCKET_REGISTRATION_H__ */
