/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __CCGL_H__
#define __CCGL_H__
#include <D3D11_1.h>
#define CC_GL_DEPTH24_STENCIL8		GL_DEPTH24_STENCIL8
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;

typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
typedef float GLfloat;
typedef char GLchar;

#define CC_TRUE                           1
#define CC_FALSE                          0
#define GL_ZERO                           0
#define GL_ONE                            1

/* TextureMagFilter */
#define CC_NEAREST                        0x2600
#define CC_LINEAR                         0x2601
#define CC_NEAREST_MIPMAP_NEAREST         0x2700
#define CC_LINEAR_MIPMAP_NEAREST          0x2701
#define CC_NEAREST_MIPMAP_LINEAR          0x2702
#define CC_LINEAR_MIPMAP_LINEAR           0x2703
#define CC_TEXTURE_MAG_FILTER             0x2800
#define CC_TEXTURE_MIN_FILTER             0x2801
#define CC_TEXTURE_WRAP_S                 0x2802
#define CC_TEXTURE_WRAP_T                 0x2803
#define CC_CLAMP                          0x2900
#define CC_REPEAT                         0x2901
#define CC_CLAMP_TO_EDGE                  0x812F

/* BlendingFactorDest */
#define CC_ZERO                           0
#define CC_ONE                            1
#define CC_SRC_COLOR                      0x0300
#define CC_ONE_MINUS_SRC_COLOR            0x0301
#define CC_SRC_ALPHA                      0x0302
#define CC_ONE_MINUS_SRC_ALPHA            0x0303
#define CC_DST_ALPHA                      0x0304
#define CC_ONE_MINUS_DST_ALPHA            0x0305
#define CC_DST_COLOR                      0x0306
#define CC_ONE_MINUS_DST_COLOR            0x0307
#define CC_SRC_ALPHA_SATURATE             0x0308

/* BlendingFactorDest */
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305

/* BlendingFactorSrc */
/*      GL_ZERO */
/*      GL_ONE */
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308

#define CC_MODELVIEW                      0x1700
#define CC_PROJECTION                     0x1701

/* AlphaFunction */
#define CC_NEVER                          0x0200
#define CC_LESS                           0x0201
#define CC_EQUAL                          0x0202
#define CC_LEQUAL                         0x0203
#define CC_GREATER                        0x0204
#define CC_NOTEQUAL                       0x0205
#define CC_GEQUAL                         0x0206
#define CC_ALWAYS                         0x0207


#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
/* Boolean */
#define GL_TRUE                           1
#define GL_FALSE                          0

/* AccumOp */
#define GL_ACCUM                          0x0100
#define GL_LOAD                           0x0101
#define GL_RETURN                         0x0102
#define GL_MULT                           0x0103
#define GL_ADD                            0x0104

/* AlphaFunction */
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

#endif // __CCGL_H__
