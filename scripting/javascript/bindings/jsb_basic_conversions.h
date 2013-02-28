#ifndef __JSB_BASIC_CONVERSION_H__
#define __JSB_BASIC_CONVERSION_H__

#include "jsapi.h"
#include "jsfriendapi.h"
#include "cocos2d.h"
#include <string>
#include "js_bindings_config.h"

using namespace std;
USING_NS_CC;

// some utility functions
// to native
JSBool jsval_to_int32( JSContext *cx, jsval vp, int32_t *ret );
JSBool jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *ret );
JSBool jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *ret );
JSBool jsval_to_long_long(JSContext *cx, jsval v, long long* ret);
JSBool jsval_to_std_string(JSContext *cx, jsval v, std::string* ret);
JSBool jsval_to_ccpoint(JSContext *cx, jsval v, CCPoint* ret);
JSBool jsval_to_ccrect(JSContext *cx, jsval v, CCRect* ret);
JSBool jsval_to_ccsize(JSContext *cx, jsval v, CCSize* ret);
JSBool jsval_to_cccolor4b(JSContext *cx, jsval v, ccColor4B* ret);
JSBool jsval_to_cccolor4f(JSContext *cx, jsval v, ccColor4F* ret);
JSBool jsval_to_cccolor3b(JSContext *cx, jsval v, ccColor3B* ret);
JSBool jsval_to_ccarray_of_CCPoint(JSContext* cx, jsval v, CCPoint **points, int *numPoints);
JSBool jsval_to_ccarray(JSContext* cx, jsval v, CCArray** ret);
JSBool jsval_to_ccdictionary(JSContext* cx, jsval v, CCDictionary** ret);
JSBool jsval_to_ccacceleration(JSContext* cx,jsval v, CCAcceleration* ret);
JSBool jsvals_variadic_to_ccarray( JSContext *cx, jsval *vp, int argc, CCArray** ret);
//JSBool jsval_to_charptr( JSContext *cx, jsval vp, const char **ret );

// from native
jsval int32_to_jsval( JSContext *cx, int32_t l);
jsval uint32_to_jsval( JSContext *cx, uint32_t number );
jsval long_long_to_jsval(JSContext* cx, long long v);
jsval std_string_to_jsval(JSContext* cx, string& v);
jsval c_string_to_jsval(JSContext* cx, const char* v);
jsval ccpoint_to_jsval(JSContext* cx, CCPoint& v);
jsval ccrect_to_jsval(JSContext* cx, CCRect& v);
jsval ccsize_to_jsval(JSContext* cx, CCSize& v);
jsval cccolor4b_to_jsval(JSContext* cx, ccColor4B& v);
jsval cccolor4f_to_jsval(JSContext* cx, ccColor4F& v);
jsval cccolor3b_to_jsval(JSContext* cx, const ccColor3B& v);
jsval ccdictionary_to_jsval(JSContext* cx, CCDictionary *dict);
jsval ccarray_to_jsval(JSContext* cx, CCArray *arr);
jsval ccacceleration_to_jsval(JSContext* cx, CCAcceleration& v);
jsval jsval_from_charptr( JSContext *cx, const char *str);

JSBool JSB_get_arraybufferview_dataptr( JSContext *cx, jsval vp, GLsizei *count, GLvoid **data );
JSBool jsval_typedarray_to_dataptr( JSContext *cx, jsval vp, GLsizei *count, void **data, JSArrayBufferViewType t);

#endif /* __JSB_BASIC_CONVERSION_H__ */
