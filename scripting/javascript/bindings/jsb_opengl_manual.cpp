/*
 * JS Bindings: https://github.com/zynga/jsbindings
 *
 * Copyright (c) 2013 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "js_bindings_config.h"
#if JSB_INCLUDE_OPENGL

#include "jsapi.h"
#include "jsfriendapi.h"

#include "jsb_opengl_manual.h"
#include "jsb_basic_conversions.h"
#include "js_bindings_core.h"
#include "jsb_opengl_functions.h"
#include "js_manual_conversions.h"

// Helper functions that link "glGenXXXs" (OpenGL ES 2.0 spec), with "gl.createXXX" (WebGL spec)
JSBool JSB_glGenTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 0, cx, JS_FALSE, "Invalid number of arguments" );

	GLuint texture;
	glGenTextures(1, &texture);
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(texture));
	return JS_TRUE;
}

JSBool JSB_glGenBuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 0, cx, JS_FALSE, "Invalid number of arguments" );

	GLuint buffer;
	glGenBuffers(1, &buffer);
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(buffer));
	return JS_TRUE;
}

JSBool JSB_glGenRenderbuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 0, cx, JS_FALSE, "Invalid number of arguments" );

	GLuint renderbuffers;
	glGenRenderbuffers(1, &renderbuffers);
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(renderbuffers));
	return JS_TRUE;
}

JSBool JSB_glGenFramebuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 0, cx, JS_FALSE, "Invalid number of arguments" );

	GLuint framebuffers;
	glGenFramebuffers(1, &framebuffers);
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(framebuffers));
	return JS_TRUE;
}

JSBool JSB_glDeleteTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	glDeleteTextures(1, &arg0);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

JSBool JSB_glDeleteBuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	glDeleteBuffers(1, &arg0);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

JSBool JSB_glDeleteRenderbuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	glDeleteRenderbuffers(1, &arg0);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

JSBool JSB_glDeleteFramebuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	glDeleteFramebuffers(1, &arg0);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

JSBool JSB_glShaderSource(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 2, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0; const char *arg1;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	ok &= jsval_to_charptr(cx, *argvp++, &arg1);
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	glShaderSource(arg0, 1, &arg1, NULL);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

JSBool JSB_glGetShaderiv(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 2, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0, arg1;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	ok &= jsval_to_uint32( cx, *argvp++, &arg1 );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	GLint ret;
	glGetShaderiv(arg0, arg1, &ret);
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret));
	return JS_TRUE;
}

JSBool JSB_glGetProgramiv(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 2, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0, arg1;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	ok &= jsval_to_uint32( cx, *argvp++, &arg1 );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	GLint ret;
	glGetProgramiv(arg0, arg1, &ret);
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret));
	return JS_TRUE;
}

JSBool JSB_glGetProgramInfoLog(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	GLsizei length;
	glGetProgramiv(arg0, GL_INFO_LOG_LENGTH, &length);
	GLchar src[length];
	glGetProgramInfoLog(arg0, length, NULL, src);

	JS_SET_RVAL(cx, vp, jsval_from_charptr(cx, src));
	return JS_TRUE;
}

JSBool JSB_glGetShaderInfoLog(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	GLsizei length;
	glGetShaderiv(arg0, GL_INFO_LOG_LENGTH, &length);
	GLchar src[length];
	glGetShaderInfoLog(arg0, length, NULL, src);

	JS_SET_RVAL(cx, vp, jsval_from_charptr(cx, src));
	return JS_TRUE;
}

JSBool JSB_glGetShaderSource(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	GLsizei length;
	glGetShaderiv(arg0, GL_SHADER_SOURCE_LENGTH, &length);
	GLchar src[length];
	glGetShaderSource(arg0, length, NULL, src);

	JS_SET_RVAL(cx, vp, jsval_from_charptr(cx, src));
	return JS_TRUE;
}

// Ret Val:
//	interface WebGLActiveInfo {
//		readonly attribute GLint size;
//		readonly attribute GLenum type;
//		readonly attribute DOMString name;
//	};
JSBool JSB_glGetActiveAttrib(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 2, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0, arg1;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	ok &= jsval_to_uint32( cx, *argvp++, &arg1 );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	GLsizei length;
	glGetProgramiv(arg0, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
	GLchar buffer[length];
	GLint size = -1;
	GLenum type = -1;

	glGetActiveAttrib(arg0, arg1, length, NULL, &size, &type, buffer);

	jsval retval = JSVAL_VOID;

	JSObject *object = JS_NewObject(cx, NULL, NULL, NULL );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error creating JS Object");

	if (!JS_DefineProperty(cx, object, "size", INT_TO_JSVAL(size), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
		!JS_DefineProperty(cx, object, "type", INT_TO_JSVAL(type), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
		!JS_DefineProperty(cx, object, "name", jsval_from_charptr(cx, buffer), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
		return JS_FALSE;

	retval = OBJECT_TO_JSVAL(object);

	JS_SET_RVAL(cx, vp, retval);
	return JS_TRUE;
}

// Ret Val:
//	interface WebGLActiveInfo {
//		readonly attribute GLint size;
//		readonly attribute GLenum type;
//		readonly attribute DOMString name;
//	};
JSBool JSB_glGetActiveUniform(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 2, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0, arg1;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	ok &= jsval_to_uint32( cx, *argvp++, &arg1 );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	GLsizei length;
	glGetProgramiv(arg0, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
	GLchar buffer[length];
	GLint size = -1;
	GLenum type = -1;

	glGetActiveUniform(arg0, arg1, length, NULL, &size, &type, buffer);

	jsval retval = JSVAL_VOID;


	JSObject *object = JS_NewObject(cx, NULL, NULL, NULL );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error creating JS Object");

	if (!JS_DefineProperty(cx, object, "size", INT_TO_JSVAL(size), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
		!JS_DefineProperty(cx, object, "type", INT_TO_JSVAL(type), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
		!JS_DefineProperty(cx, object, "name", jsval_from_charptr(cx, buffer), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
		return JS_FALSE;

	retval = OBJECT_TO_JSVAL(object);

	JS_SET_RVAL(cx, vp, retval);
	return JS_TRUE;
}

// Ret Val: sequence<WebGLShader>?
JSBool JSB_glGetAttachedShaders(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	uint32_t arg0;

	ok &= jsval_to_uint32( cx, *argvp++, &arg0 );
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

	GLsizei length;
	glGetProgramiv(arg0, GL_ATTACHED_SHADERS, &length);
	GLuint buffer[length];

	glGetAttachedShaders(arg0, length, NULL, buffer);

	JSObject *jsobj = JS_NewArrayObject(cx, length, NULL);
	JSB_PRECONDITION2(jsobj, cx, JS_FALSE, "Error creating JS Object");

	for( int i=0; i<length; i++) {
		jsval e = INT_TO_JSVAL(buffer[i]);
		JS_SetElement(cx, jsobj, i, &e );
	}

	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	return JS_TRUE;

}

// Ret Val: sequence<DOMString>?
JSBool JSB_glGetSupportedExtensions(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2( argc == 0, cx, JS_FALSE, "Invalid number of arguments" );

	const GLubyte *extensions = glGetString(GL_EXTENSIONS);

	JSObject *jsobj = JS_NewArrayObject(cx, 0, NULL);
	JSB_PRECONDITION2(jsobj, cx, JS_FALSE, "Error creating JS Object");

	// copy, to be able to add '\0'
	size_t len = strlen((char*)extensions);
	GLubyte copy[len+1];
	strncpy((char*)copy, (const char*)extensions, len );

	int start_extension=0;
	int element=0;
	for( int i=0; i<len+1; i++) {
		if( copy[i]==' ' || copy[i]==',' || i==len ) {
			copy[i] = 0;

			jsval str = jsval_from_charptr(cx, (const char*)&copy[start_extension]);
			JS_SetElement(cx, jsobj, element++, &str );

			start_extension = i+1;

			i++;
		}
	}

	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	return JS_TRUE;
	
}


#endif // JSB_INCLUDE_OPENGL
