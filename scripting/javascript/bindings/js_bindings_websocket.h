#ifndef __JS_BINDINGS_WEBSOCKET_REGISTRATION_H__
#define __JS_BINDINGS_WEBSOCKET_REGISTRATION_H__

#include "jsapi.h"

extern JSClass  *jsb_websocket_class;
extern JSObject *jsb_websocket_prototype;

JSBool jsb_websocket_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void jsb_websocket_finalize(JSFreeOp *fop, JSObject *obj);

JSBool jsb_websocket_send(JSContext *cx, uint32_t argc, jsval *vp);
JSBool jsb_websocket_close(JSContext *cx, uint32_t argc, jsval *vp);

void jsb_register_websocket( JSContext *globalC, JSObject *globalO);

#endif /* __JS_BINDINGS_WEBSOCKET_REGISTRATION_H__ */
