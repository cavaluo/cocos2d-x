#include "jsb_basic_conversions.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"

#pragma mark - Conversion Routines
JSBool jsval_to_int32( JSContext *cx, jsval vp, int32_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    
    *outval = (int32_t)dp;
    
    return ok;
}

JSBool jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    
    *outval = (uint32_t)dp;
    
    return ok;
}

JSBool jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    
    *outval = (uint16_t)dp;
    
    return ok;
}

JSBool jsval_to_long_long(JSContext *cx, jsval vp, long long* r) {
	JSObject *tmp_arg;
	JSBool ok = JS_ValueToObject( cx, vp, &tmp_arg );
	JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error converting value to object");
	JSB_PRECONDITION2( tmp_arg && JS_IsTypedArrayObject( tmp_arg ), cx, JS_FALSE, "Not a TypedArray object");
	JSB_PRECONDITION2( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(long long), cx, JS_FALSE, "Invalid Typed Array length");
	
	uint32_t* arg_array = (uint32_t*)JS_GetArrayBufferViewData( tmp_arg );
	long long ret =  arg_array[0];
	ret = ret << 32;
	ret |= arg_array[1];
	
	*r = ret;
	return JS_TRUE;
}

JSBool jsval_to_std_string(JSContext *cx, jsval v, std::string* ret) {
    JSString *tmp = JS_ValueToString(cx, v);
    JSB_PRECONDITION2(tmp, cx, JS_FALSE, "Error processing arguments");
    
    JSStringWrapper str(tmp);
    *ret = str.get();
    return JS_TRUE;
}

JSBool jsval_to_ccpoint(JSContext *cx, jsval v, CCPoint* ret) {
    JSObject *tmp;
    jsval jsx, jsy;
    double x, y;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_ValueToNumber(cx, jsx, &x) &&
    JS_ValueToNumber(cx, jsy, &y);
    
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    
    ret->x = (float)x;
    ret->y = (float)y;
    return JS_TRUE;
}

JSBool jsval_to_ccacceleration(JSContext* cx,jsval v, CCAcceleration* ret) {
    JSObject *tmp;
    jsval jsx, jsy, jsz, jstimestamp;
    double x, y, timestamp, z;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_GetProperty(cx, tmp, "z", &jsz) &&
    JS_GetProperty(cx, tmp, "timestamp", &jstimestamp) &&
    JS_ValueToNumber(cx, jsx, &x) &&
    JS_ValueToNumber(cx, jsy, &y) &&
    JS_ValueToNumber(cx, jsz, &z) &&
    JS_ValueToNumber(cx, jstimestamp, &timestamp);
    
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    
    ret->x = x;
    ret->y = y;
    ret->z = z;
    ret->timestamp = timestamp;
    return JS_TRUE;
}

JSBool jsvals_variadic_to_ccarray( JSContext *cx, jsval *vp, int argc, CCArray** ret)
{
    JSBool ok = JS_TRUE;
    CCArray* pArray = CCArray::create();
    for( int i=0; i < argc; i++ )
    {
        double num = 0.0;
        // optimization: JS_ValueToNumber is expensive. And can convert an string like "12" to a number
        if( JSVAL_IS_NUMBER(*vp)) {
            ok &= JS_ValueToNumber(cx, *vp, &num );
            if (!ok) {
                break;
            }
            pArray->addObject(CCInteger::create((int)num));
        }
        else if (JSVAL_IS_STRING(*vp))
        {
            JSStringWrapper str(JSVAL_TO_STRING(*vp), cx);
            pArray->addObject(CCString::create(str));
        }
        else
        {
            js_proxy_t* p;
            JSObject* obj = JSVAL_TO_OBJECT(*vp);
            JS_GET_NATIVE_PROXY(p, obj);
            if (p) {
                pArray->addObject((CCObject*)p->ptr);
            }
        }
        // next
        vp++;
    }
    *ret = pArray;
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    return ok;
}

JSBool jsval_to_ccrect(JSContext *cx, jsval v, CCRect* ret) {
    JSObject *tmp;
    jsval jsx, jsy, jswidth, jsheight;
    double x, y, width, height;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_GetProperty(cx, tmp, "width", &jswidth) &&
    JS_GetProperty(cx, tmp, "height", &jsheight) &&
    JS_ValueToNumber(cx, jsx, &x) &&
    JS_ValueToNumber(cx, jsy, &y) &&
    JS_ValueToNumber(cx, jswidth, &width) &&
    JS_ValueToNumber(cx, jsheight, &height);
    
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    
    ret->origin.x = x;
    ret->origin.y = y;
    ret->size.width = width;
    ret->size.height = height;
    return JS_TRUE;
}

JSBool jsval_to_ccsize(JSContext *cx, jsval v, CCSize* ret) {
    JSObject *tmp;
    jsval jsw, jsh;
    double w, h;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "width", &jsw) &&
    JS_GetProperty(cx, tmp, "height", &jsh) &&
    JS_ValueToNumber(cx, jsw, &w) &&
    JS_ValueToNumber(cx, jsh, &h);
    
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ret->width = w;
    ret->height = h;
    return JS_TRUE;
}

JSBool jsval_to_cccolor4b(JSContext *cx, jsval v, ccColor4B* ret) {
    JSObject *tmp;
    jsval jsr, jsg, jsb, jsa;
    double r, g, b, a;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "g", &jsg) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_GetProperty(cx, tmp, "a", &jsa) &&
    JS_ValueToNumber(cx, jsr, &r) &&
    JS_ValueToNumber(cx, jsg, &g) &&
    JS_ValueToNumber(cx, jsb, &b) &&
    JS_ValueToNumber(cx, jsa, &a);
    
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    
    ret->r = r;
    ret->g = g;
    ret->b = b;
    ret->a = a;
    return JS_TRUE;
}

JSBool jsval_to_cccolor4f(JSContext *cx, jsval v, ccColor4F* ret) {
    JSObject *tmp;
    jsval jsr, jsg, jsb, jsa;
    double r, g, b, a;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "g", &jsg) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_GetProperty(cx, tmp, "a", &jsa) &&
    JS_ValueToNumber(cx, jsr, &r) &&
    JS_ValueToNumber(cx, jsg, &g) &&
    JS_ValueToNumber(cx, jsb, &b) &&
    JS_ValueToNumber(cx, jsa, &a);
    
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ret->r = r;
    ret->g = g;
    ret->b = b;
    ret->a = a;
    return JS_TRUE;
}

JSBool jsval_to_cccolor3b(JSContext *cx, jsval v, ccColor3B* ret) {
    JSObject *tmp;
    jsval jsr, jsg, jsb;
    double r, g, b;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "g", &jsg) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_ValueToNumber(cx, jsr, &r) &&
    JS_ValueToNumber(cx, jsg, &g) &&
    JS_ValueToNumber(cx, jsb, &b);
    
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    
    ret->r = r;
    ret->g = g;
    ret->b = b;
    return JS_TRUE;
}

JSBool jsval_to_ccarray_of_CCPoint(JSContext* cx, jsval v, CCPoint **points, int *numPoints) {
    // Parsing sequence
    JSObject *jsobj;
    JSBool ok = JS_ValueToObject( cx, v, &jsobj );
    JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error converting value to object");
    JSB_PRECONDITION2( jsobj && JS_IsArrayObject( cx, jsobj), cx, JS_FALSE, "Object must be an array");
    
    uint32_t len;
    JS_GetArrayLength(cx, jsobj, &len);
    
    CCPoint *array = (CCPoint*)malloc( sizeof(CCPoint) * len);
    
    for( uint32_t i=0; i< len;i++ ) {
        jsval valarg;
        JS_GetElement(cx, jsobj, i, &valarg);
        
        ok = jsval_to_ccpoint(cx, valarg, &array[i]);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    }
    
    *numPoints = len;
    *points = array;
    
    return JS_TRUE;
}


JSBool jsval_to_ccarray(JSContext* cx, jsval v, CCArray** ret) {
    JSObject *jsobj;
    JSBool ok = JS_ValueToObject( cx, v, &jsobj );
    JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error converting value to object");
    JSB_PRECONDITION2( jsobj && JS_IsArrayObject( cx, jsobj),  cx, JS_FALSE, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    CCArray* arr = CCArray::createWithCapacity(len);
    for (uint32_t i=0; i < len; i++) {
        jsval elt;
        JSObject *elto;
        if (JS_GetElement(cx, jsobj, i, &elt) && JS_ValueToObject(cx, elt, &elto)) {
            js_proxy_t *proxy;
            JS_GET_NATIVE_PROXY(proxy, elto);
            JSB_PRECONDITION2( proxy, cx, JS_FALSE, "Error getting proxy.");
            
            arr->addObject((CCObject *)proxy->ptr);
        }
    }
    *ret = arr;
    return JS_TRUE;
}


jsval ccarray_to_jsval(JSContext* cx, CCArray *arr) {
    
    JSObject *jsretArr = JS_NewArrayObject(cx, 0, NULL);
    
    for(unsigned int i = 0; i < arr->count(); ++i) {
        jsval arrElement;
        CCObject *obj = arr->objectAtIndex(i);
        
        CCString *testString = dynamic_cast<cocos2d::CCString *>(obj);
        CCDictionary* testDict = NULL;
        CCArray* testArray = NULL;
        // XXX: Only supports string, since all data read from plist files will be stored as string in cocos2d-x
        // Do we need to convert string to js base type ?
        if(testString) {
            arrElement = c_string_to_jsval(cx, testString->getCString());
        } else if ((testDict = dynamic_cast<cocos2d::CCDictionary*>(obj))) {
            arrElement = ccdictionary_to_jsval(cx, testDict);
        } else if ((testArray = dynamic_cast<cocos2d::CCArray*>(obj))) {
            arrElement = ccarray_to_jsval(cx, testArray);
        } else {
            js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCObject>(cx, obj);
            arrElement = OBJECT_TO_JSVAL(proxy->obj);
        }
        
        if(!JS_SetElement(cx, jsretArr, i, &arrElement)) {
            break;
        }
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval ccdictionary_to_jsval(JSContext* cx, CCDictionary* dict)
{
    JSObject* jsRet = JS_NewObject(cx, NULL, NULL, NULL);
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(dict, pElement)
    {
        jsval dictElement;
        CCString* obj = dynamic_cast<CCString*>(pElement->getObject());
        
        CCString *testString = dynamic_cast<cocos2d::CCString *>(obj);
        CCDictionary* testDict = NULL;
        CCArray* testArray = NULL;
        // XXX: Only supports string, since all data read from plist files will be stored as string in cocos2d-x
        // Do we need to convert string to js base type ?
        if(testString) {
            dictElement = c_string_to_jsval(cx, testString->getCString());
        } else if ((testDict = dynamic_cast<cocos2d::CCDictionary*>(obj))) {
            dictElement = ccdictionary_to_jsval(cx, testDict);
        } else if ((testArray = dynamic_cast<cocos2d::CCArray*>(obj))) {
            dictElement = ccarray_to_jsval(cx, testArray);
        } else {
            js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCObject>(cx, obj);
            dictElement = OBJECT_TO_JSVAL(proxy->obj);
        }
        
        const char* key = pElement->getStrKey();
        if (key && strlen(key) > 0)
        {
            JS_SetProperty(cx, jsRet, key, &dictElement);
        }
    }
    return OBJECT_TO_JSVAL(jsRet);
}

JSBool jsval_to_ccdictionary(JSContext* cx, jsval v, CCDictionary** ret) {
    
    if(JSVAL_IS_NULL(v) || JSVAL_IS_VOID(v))
    {
        *ret = NULL;
        return JS_TRUE;
    }
    
    JSObject *itEl = JS_NewPropertyIterator(cx, JSVAL_TO_OBJECT(v));
    JSBool ok = JS_TRUE;
    CCDictionary* dict = NULL;
    jsid propId;
    do {
        
        jsval prop;
        JS_GetPropertyById(cx, JSVAL_TO_OBJECT(v), propId, &prop);
        
        js_proxy_t *proxy;
        JSObject *tmp = JSVAL_TO_OBJECT(prop);
        JS_GET_NATIVE_PROXY(proxy, tmp);
        cocos2d::CCObject* cobj = (cocos2d::CCObject *)(proxy ? proxy->ptr : NULL);
        TEST_NATIVE_OBJECT(cx, cobj)
        
        jsval key;
        std::string keyStr;
        if(JSID_IS_STRING(propId)) {
            JS_IdToValue(cx, propId, &key);
            ok &= jsval_to_std_string(cx, key, &keyStr);
            JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        }
        
        if(JSVAL_IS_NULL(key)) continue;
        
        if(!dict) {
            dict = CCDictionary::create();
        }
        dict->setObject(cobj, keyStr);
        
    } while(JS_NextProperty(cx, itEl, &propId));
    *ret = dict;
    return JS_TRUE;
}

// From native type to jsval
jsval int32_to_jsval( JSContext *cx, int32_t number )
{
    return INT_TO_JSVAL(number);
}

jsval uint32_to_jsval( JSContext *cx, uint32_t number )
{
    return UINT_TO_JSVAL(number);
}

jsval long_long_to_jsval(JSContext* cx, long long v) {
    JSObject *tmp = JS_NewUint32Array(cx, 2);
    uint32_t *data = (uint32_t *)JS_GetArrayBufferViewData(tmp);
    data[0] = ((uint32_t *)(&v))[0];
    data[1] = ((uint32_t *)(&v))[1];
    return OBJECT_TO_JSVAL(tmp);
}

jsval std_string_to_jsval(JSContext* cx, std::string& v) {
    JSString *str = JS_NewStringCopyZ(cx, v.c_str());
    return STRING_TO_JSVAL(str);
}

jsval c_string_to_jsval(JSContext* cx, const char* v) {
    JSString *str = JS_NewStringCopyZ(cx, v);
    return STRING_TO_JSVAL(str);
}

jsval ccpoint_to_jsval(JSContext* cx, CCPoint& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccacceleration_to_jsval(JSContext* cx, CCAcceleration& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "z", DOUBLE_TO_JSVAL(v.z), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "timestamp", DOUBLE_TO_JSVAL(v.timestamp), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccrect_to_jsval(JSContext* cx, CCRect& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v.origin.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v.origin.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "width", DOUBLE_TO_JSVAL(v.size.width), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "height", DOUBLE_TO_JSVAL(v.size.height), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccsize_to_jsval(JSContext* cx, CCSize& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "width", DOUBLE_TO_JSVAL(v.width), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "height", DOUBLE_TO_JSVAL(v.height), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor4b_to_jsval(JSContext* cx, ccColor4B& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "r", INT_TO_JSVAL(v.r), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "g", INT_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", INT_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "a", INT_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor4f_to_jsval(JSContext* cx, ccColor4F& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "r", DOUBLE_TO_JSVAL(v.r), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "g", DOUBLE_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", DOUBLE_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "a", DOUBLE_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor3b_to_jsval(JSContext* cx, const ccColor3B& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "r", INT_TO_JSVAL(v.r), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "g", INT_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", INT_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

//JSBool jsval_to_charptr( JSContext *cx, jsval vp, const char **ret )
//{
//	JSString *jsstr = JS_ValueToString( cx, vp );
//	JSB_PRECONDITION2( jsstr, cx, JS_FALSE, "invalid string" );
//	
//	JSStringWrapper strWrapper(jsstr);
//    CCString* ccstr = CCString::create(strWrapper.get());
//	*ret = ccstr->getCString();
//    
//	return JS_TRUE;
//}

jsval jsval_from_charptr( JSContext *cx, const char *str)
{
	JSString *ret_obj = JS_NewStringCopyZ(cx, str);
	return STRING_TO_JSVAL(ret_obj);
}

JSBool JSB_get_arraybufferview_dataptr( JSContext *cx, jsval vp, GLsizei *count, GLvoid **data )
{
	JSObject *jsobj;
	JSBool ok = JS_ValueToObject( cx, vp, &jsobj );
	JSB_PRECONDITION2( ok && jsobj, cx, JS_FALSE, "Error converting value to object");
	JSB_PRECONDITION2( JS_IsArrayBufferViewObject(jsobj), cx, JS_FALSE, "Not an ArrayBufferView object");
    
	*data = JS_GetArrayBufferViewData(jsobj);
	*count = JS_GetArrayBufferViewByteLength(jsobj);
    
	return JS_TRUE;
}

JSBool jsval_typedarray_to_dataptr( JSContext *cx, jsval vp, GLsizei *count, void **data, JSArrayBufferViewType t)
{
	JSObject *jsobj;
	JSBool ok = JS_ValueToObject( cx, vp, &jsobj );
	JSB_PRECONDITION2( ok && jsobj, cx, JS_FALSE, "Error converting value to object");
    
	// WebGL supports TypedArray and sequences for some of its APIs. So when converting a TypedArray, we should
	// also check for a possible non-Typed Array JS object, like a JS Array.
    
	if( JS_IsTypedArrayObject( jsobj ) ) {
        
		*count = JS_GetTypedArrayLength(jsobj);
		JSArrayBufferViewType type = JS_GetArrayBufferViewType(jsobj);
		JSB_PRECONDITION2(t==type, cx, JS_FALSE, "TypedArray type different than expected type");
        
		switch (t) {
			case js::ArrayBufferView::TYPE_INT8:
			case js::ArrayBufferView::TYPE_UINT8:
				*data = JS_GetUint8ArrayData(jsobj);
				break;
                
			case js::ArrayBufferView::TYPE_INT16:
			case js::ArrayBufferView::TYPE_UINT16:
				*data = JS_GetUint16ArrayData(jsobj);
				break;
                
			case js::ArrayBufferView::TYPE_INT32:
			case js::ArrayBufferView::TYPE_UINT32:
				*data = JS_GetUint32ArrayData(jsobj);
				break;
                
			case js::ArrayBufferView::TYPE_FLOAT32:
				*data = JS_GetFloat32ArrayData(jsobj);
				break;
                
			default:
				JSB_PRECONDITION2(false, cx, JS_FALSE, "Unsupported typedarray type");
				break;
		}
	} else if( JS_IsArrayObject(cx, jsobj)) {
		// Slow... avoid it. Use TypedArray instead
		uint32_t lenghthp;
		JS_GetArrayLength(cx, jsobj, &lenghthp);
        
		for( uint32_t i=0; i<lenghthp;i++ ) {
            
			jsval valarg;
			JS_GetElement(cx, jsobj, i, &valarg);
            
			switch(t) {
				case js::ArrayBufferView::TYPE_INT32:
				case js::ArrayBufferView::TYPE_UINT32:
				{
					uint32_t e = JSVAL_TO_INT(valarg);
					((uint32_t*)data)[i] = e;
					break;
				}
				case js::ArrayBufferView::TYPE_FLOAT32:
				{
					double e = JSVAL_TO_DOUBLE(valarg);
					((GLfloat*)data)[i] = (GLfloat)e;
					break;
				}
				default:
					JSB_PRECONDITION2(false, cx, JS_FALSE, "Unsupported typedarray type");
					break;
			}
		}
        
	} else
		JSB_PRECONDITION2(false, cx, JS_FALSE, "Object shall be a TypedArray or Sequence");
    
	return JS_TRUE;
}
