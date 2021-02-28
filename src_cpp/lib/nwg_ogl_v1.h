#ifndef NWG_OGL_V1_H
#define NWG_OGL_V1_H
#include "nwg_ogl_native.h"
namespace NWG
{
	extern void OglLoadV1();
}
#ifndef GL_VERSION_1_0
#define GL_VERSION_1_0 1
// --drawing
typedef void (APIENTRYP PFNGLBEGINPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLENDPROC) ();
typedef void (APIENTRYP PFNGLVERTEX2SPROC)(GLshort x, GLshort y);
typedef void (APIENTRYP PFNGLVERTEX3SPROC)(GLshort x, GLshort y, GLshort z);
typedef void (APIENTRYP PFNGLVERTEX4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (APIENTRYP PFNGLVERTEX2IPROC)(GLint x, GLint y);
typedef void (APIENTRYP PFNGLVERTEX3IPROC)(GLint x, GLint y, GLint z);
typedef void (APIENTRYP PFNGLVERTEX4IPROC)(GLint x, GLint y, GLint z, GLint w);
typedef void (APIENTRYP PFNGLVERTEX2FPROC)(GLfloat x, GLfloat y);
typedef void (APIENTRYP PFNGLVERTEX3FPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRYP PFNGLVERTEX4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRYP PFNGLVERTEX2DPROC)(GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLVERTEX3DPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLVERTEX4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLCOLOR3BPROC)(GLbyte r, GLbyte g, GLbyte b);
typedef void (APIENTRYP PFNGLCOLOR4BPROC)(GLbyte r, GLbyte g, GLbyte b, GLbyte a);
typedef void (APIENTRYP PFNGLCOLOR3UBPROC)(GLubyte r, GLubyte g, GLubyte b);
typedef void (APIENTRYP PFNGLCOLOR4UBPROC)(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
typedef void (APIENTRYP PFNGLCOLOR3SPROC)(GLshort r, GLshort g, GLshort b);
typedef void (APIENTRYP PFNGLCOLOR4SPROC)(GLshort r, GLshort g, GLshort b, GLshort a);
typedef void (APIENTRYP PFNGLCOLOR3USPROC)(GLushort r, GLushort g, GLushort b);
typedef void (APIENTRYP PFNGLCOLOR4USPROC)(GLushort r, GLushort g, GLushort b, GLushort a);
typedef void (APIENTRYP PFNGLCOLOR3IPROC)(GLint r, GLint g, GLint b);
typedef void (APIENTRYP PFNGLCOLOR4IPROC)(GLint r, GLint g, GLint b, GLint a);
typedef void (APIENTRYP PFNGLCOLOR3UIPROC)(GLuint r, GLuint g, GLuint b);
typedef void (APIENTRYP PFNGLCOLOR4UIPROC)(GLuint r, GLuint g, GLuint b, GLuint a);
typedef void (APIENTRYP PFNGLCOLOR3FPROC)(GLfloat r, GLfloat g, GLfloat b);
typedef void (APIENTRYP PFNGLCOLOR4FPROC)(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
typedef void (APIENTRYP PFNGLCOLOR3DPROC)(GLdouble r, GLdouble g, GLdouble b);
typedef void (APIENTRYP PFNGLCOLOR4DPROC)(GLdouble r, GLdouble g, GLdouble b, GLdouble a);
// --configs
typedef void (APIENTRYP PFNGLCULLFACEPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLFRONTFACEPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLHINTPROC) (GLenum target, GLenum mode);
typedef void (APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat width);
typedef void (APIENTRYP PFNGLPOINTSIZEPROC) (GLfloat size);
typedef void (APIENTRYP PFNGLPOLYGONMODEPROC) (GLenum face, GLenum mode);
typedef void (APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
typedef void (APIENTRYP PFNGLLOGICOPPROC) (GLenum opcode);
typedef void (APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
typedef void (APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
typedef void (APIENTRYP PFNGLDEPTHRANGEPROC) (GLdouble near, GLdouble far);
typedef void (APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
// --textures
typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, const GLfloat* params);
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, const GLint* params);
typedef void (APIENTRYP PFNGLTEXIMAGE1DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
// --framebuffers
typedef void (APIENTRYP PFNGLDRAWBUFFERPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLDRAWPIXELSPROC) (GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
typedef void (APIENTRYP PFNGLCLEARPROC) (GLbitfield mask);
typedef void (APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
typedef void (APIENTRYP PFNGLCLEARDEPTHPROC) (GLdouble depth);
typedef void (APIENTRYP PFNGLSTENCILMASKPROC) (GLuint mask);
typedef void (APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
typedef void (APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLENABLEPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLFINISHPROC) (void);
typedef void (APIENTRYP PFNGLFLUSHPROC) (void);
typedef void (APIENTRYP PFNGLPIXELSTOREFPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLREADBUFFERPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels);
// --getters
typedef void (APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean* params);
typedef void (APIENTRYP PFNGLGETDOUBLEVPROC) (GLenum pname, GLdouble* params);
typedef GLenum(APIENTRYP PFNGLGETERRORPROC) (void);
typedef void (APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat* params);
typedef void (APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint* params);
typedef const GLubyte* (APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
typedef void (APIENTRYP PFNGLGETTEXIMAGEPROC) (GLenum target, GLint level, GLenum format, GLenum type, GLvoid* pixels);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat* params);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint* params);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum target, GLint level, GLenum pname, GLfloat* params);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum target, GLint level, GLenum pname, GLint* params);
typedef GLboolean(APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
// --drawing
extern PFNGLBEGINPROC OglBegin;
extern PFNGLENDPROC OglEnd;
extern PFNGLVERTEX2SPROC OglVertex2si16;
extern PFNGLVERTEX3SPROC OglVertex3si16;
extern PFNGLVERTEX4SPROC OglVertex4si16;
extern PFNGLVERTEX2IPROC OglVertex2si32;
extern PFNGLVERTEX3IPROC OglVertex3si32;
extern PFNGLVERTEX4IPROC OglVertex4si32;
extern PFNGLVERTEX2FPROC OglVertex2f32;
extern PFNGLVERTEX3FPROC OglVertex3f32;
extern PFNGLVERTEX4FPROC OglVertex4f32;
extern PFNGLVERTEX2DPROC OglVertex2f64;
extern PFNGLVERTEX3DPROC OglVertex3f64;
extern PFNGLVERTEX4DPROC OglVertex4f64;
extern PFNGLCOLOR3BPROC OglColor3si8;
extern PFNGLCOLOR4BPROC OglColor4si8;
extern PFNGLCOLOR3UBPROC OglColor3ui8;
extern PFNGLCOLOR4UBPROC OglColor4ui8;
extern PFNGLCOLOR3SPROC OglColor3si16;
extern PFNGLCOLOR4SPROC OglColor4si16;
extern PFNGLCOLOR3USPROC OglColor3ui16;
extern PFNGLCOLOR4USPROC OglColor4ui16;
extern PFNGLCOLOR3IPROC OglColor3si32;
extern PFNGLCOLOR4IPROC OglColor4si32;
extern PFNGLCOLOR3UIPROC OglColor3ui32;
extern PFNGLCOLOR4UIPROC OglColor4ui32;
extern PFNGLCOLOR3FPROC OglColor3f32;
extern PFNGLCOLOR4FPROC OglColor4f32;
extern PFNGLCOLOR3DPROC OglColor3f64;
extern PFNGLCOLOR4DPROC OglColor4f64;
// --configs
extern PFNGLCULLFACEPROC OglCullFace;
extern PFNGLFRONTFACEPROC OglFrontFace;
extern PFNGLHINTPROC OglHint;
extern PFNGLLINEWIDTHPROC OglLineWidth;
extern PFNGLPOINTSIZEPROC OglPointSize;
extern PFNGLPOLYGONMODEPROC OglPolygonMode;
extern PFNGLSCISSORPROC OglScissor;
// --textures
extern PFNGLTEXPARAMETERFPROC OglTexParameterf;
extern PFNGLTEXPARAMETERFVPROC OglTexParameterfv;
extern PFNGLTEXPARAMETERIPROC OglTexParameteri;
extern PFNGLTEXPARAMETERIVPROC OglTexParameteriv;
extern PFNGLTEXIMAGE1DPROC OglTexImage1D;
extern PFNGLTEXIMAGE2DPROC OglTexImage2D;
// --framebuffers
extern PFNGLDRAWBUFFERPROC OglDrawBuffer;
extern PFNGLDRAWPIXELSPROC OglDrawPixels;
extern PFNGLCLEARPROC OglClear;
extern PFNGLCLEARCOLORPROC OglClearColor;
extern PFNGLCLEARSTENCILPROC OglClearStencil;
extern PFNGLCLEARDEPTHPROC OglClearDepth;
extern PFNGLSTENCILMASKPROC OglStencilMask;
extern PFNGLCOLORMASKPROC OglColorMask;
extern PFNGLDEPTHMASKPROC OglDepthMask;
extern PFNGLDISABLEPROC OglDisable;
extern PFNGLENABLEPROC OglEnable;
extern PFNGLFINISHPROC OglFinish;
extern PFNGLFLUSHPROC OglFlush;
extern PFNGLBLENDFUNCPROC OglBlendFunc;
extern PFNGLLOGICOPPROC OglLogicOp;
extern PFNGLSTENCILFUNCPROC OglStencilFunc;
extern PFNGLSTENCILOPPROC OglStencilOp;
extern PFNGLDEPTHFUNCPROC OglDepthFunc;
extern PFNGLPIXELSTOREFPROC OglPixelStoref;
extern PFNGLPIXELSTOREIPROC OglPixelStorei;
extern PFNGLREADBUFFERPROC OglReadBuffer;
extern PFNGLREADPIXELSPROC OglReadPixels;
// --getters
extern PFNGLGETBOOLEANVPROC OglGetBooleanv;
extern PFNGLGETDOUBLEVPROC OglGetDoublev;
extern PFNGLGETERRORPROC OglGetError;
extern PFNGLGETFLOATVPROC OglGetFloatv;
extern PFNGLGETINTEGERVPROC OglGetIntegerv;
extern PFNGLGETSTRINGPROC OglGetString;
extern PFNGLGETTEXIMAGEPROC OglGetTexImage;
extern PFNGLGETTEXPARAMETERFVPROC OglGetTexParameterfv;
extern PFNGLGETTEXPARAMETERIVPROC OglGetTexParameteriv;
extern PFNGLGETTEXLEVELPARAMETERFVPROC OglGetTexLevelParameterfv;
extern PFNGLGETTEXLEVELPARAMETERIVPROC OglGetTexLevelParameteriv;
extern PFNGLISENABLEDPROC OglIsEnabled;
extern PFNGLDEPTHRANGEPROC OglDepthRange;
extern PFNGLVIEWPORTPROC OglViewport;
// --drawing
// --drawing
#define glBegin			OglBegin;
#define glEnd			OglEnd;
#define glVertex2s		OglVertex2si16;
#define glVertex3s		OglVertex3si16;
#define glVertex4s		OglVertex4si16;
#define glVertex2i		OglVertex2si32;
#define glVertex3i		OglVertex3si32;
#define glVertex4i		OglVertex4si32;
#define glVertex2f		OglVertex2f32;
#define glVertex3f		OglVertex3f32;
#define glVertex4f		OglVertex4f32;
#define glVertex2d		OglVertex2f64;
#define glVertex3d		OglVertex3f64;
#define glVertex4d		OglVertex4f64;
#define glColor3b		OglColor3si8;
#define glColor4b		OglColor4si8;
#define glColor3ub		OglColor3ui8;
#define glColor4ub		OglColor4ui8;
#define glColor3s		OglColor3si16;
#define glColor4s		OglColor4si16;
#define glColor3us		OglColor3ui16;
#define glColor4us		OglColor4ui16;
#define glColor3i		OglColor3si32;
#define glColor4i		OglColor4si32;
#define glColor3ui		OglColor3ui32;
#define glColor4ui		OglColor4ui32;
#define glColor3f		OglColor3f32;
#define glColor4f		OglColor4f32;
#define glColor3d		OglColor3f64;
#define glColor4d		OglColor4f64;
// --configs
#define glCullFace		OglCullFace
#define glFrontFace		OglFrontFace
#define glHint			OglHint
#define glLineWidth		OglLineWidth
#define glPointSize		OglPointSize
#define glPolygonMode	OglPolygonMode
#define glScissor		OglScissor
// --textures
#define glTexParameterf		OglTexParameterf
#define glTexParameterfv	OglTexParameterfv
#define glTexParameteri		OglTexParameteri
#define glTexParameteriv	OglTexParameteriv
#define glTexImage1D		OglTexImage1D
#define glTexImage2D		OglTexImage2D
// --framebuffers
#define glDrawBuffer	OglDrawBuffer
#define glDrawPixels	OglDrawPixels
#define glClear			OglClear
#define glClearColor	OglClearColor
#define glClearStencil	OglClearStencil
#define glClearDepth	OglClearDepth
#define glStencilMask	OglStencilMask
#define glColorMask		OglColorMask
#define glDepthMask		OglDepthMask
#define glDisable		OglDisable
#define glEnable		OglEnable
#define glFinish		OglFinish
#define glFlush			OglFlush
#define glBlendFunc		OglBlendFunc
#define glLogicOp		OglLogicOp
#define glStencilFunc	OglStencilFunc
#define glStencilOp		OglStencilOp
#define glDepthFunc		OglDepthFunc
#define glPixelStoref	OglPixelStoref
#define glPixelStorei	OglPixelStorei
#define glReadBuffer	OglReadBuffer
#define glReadPixels	OglReadPixels
#define glGetBooleanv	OglGetBooleanv
#define glGetDoublev	OglGetDoublev
#define glGetError		OglGetError
#define glGetFloatv		OglGetFloatv
#define glGetIntegerv	OglGetIntegerv
#define glGetString		OglGetString
#define glGetTexImage		OglGetTexImage
#define glGetTexParameterfv		OglGetTexParameterfv
#define glGetTexParameteriv		OglGetTexParameteriv
#define glGetTexLevelParameterfv		OglGetTexLevelParameterfv
#define glGetTexLevelParameteriv		OglGetTexLevelParameteriv
#define glIsEnabled		OglIsEnabled
#define glDepthRange	OglDepthRange
#define glViewport		OglViewport
#endif	// GL_VERSION_1_0

#ifndef GL_VERSION_1_1
#define GL_VERSION_1_1 1
// AttribMask
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000
// Boolean
#define GL_FALSE                          0
#define GL_TRUE                           1
// BeginMode
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_QUADS                          0x0007
// AlphaFunction
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207
// BlendingFactorDest
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
// BlendingFactorSrc
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
// DrawBufferMode
#define GL_NONE                           0
#define GL_FRONT_LEFT                     0x0400
#define GL_FRONT_RIGHT                    0x0401
#define GL_BACK_LEFT                      0x0402
#define GL_BACK_RIGHT                     0x0403
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_LEFT                           0x0406
#define GL_RIGHT                          0x0407
#define GL_FRONT_AND_BACK                 0x0408
// ErrorCode
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_OUT_OF_MEMORY                  0x0505
// FrontFaceDirection
#define GL_CW                             0x0900
#define GL_CCW                            0x0901
// GetPName
#define GL_POINT_SIZE                     0x0B11
#define GL_POINT_SIZE_RANGE               0x0B12
#define GL_POINT_SIZE_GRANULARITY         0x0B13
#define GL_LINE_SMOOTH                    0x0B20
#define GL_LINE_WIDTH                     0x0B21
#define GL_LINE_WIDTH_RANGE               0x0B22
#define GL_LINE_WIDTH_GRANULARITY         0x0B23
#define GL_POLYGON_MODE                   0x0B40
#define GL_POLYGON_SMOOTH                 0x0B41
#define GL_CULL_FACE                      0x0B44
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_TEST                     0x0B71
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_VALUE              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_STENCIL_TEST                   0x0B90
#define GL_STENCIL_CLEAR_VALUE            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_VALUE_MASK             0x0B93
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_VIEWPORT                       0x0BA2
#define GL_DITHER                         0x0BD0
#define GL_BLEND_DST                      0x0BE0
#define GL_BLEND_SRC                      0x0BE1
#define GL_BLEND                          0x0BE2
#define GL_LOGIC_OP_MODE                  0x0BF0
#define GL_COLOR_LOGIC_OP                 0x0BF2
#define GL_DRAW_BUFFER                    0x0C01
#define GL_READ_BUFFER                    0x0C02
#define GL_SCISSOR_BOX                    0x0C10
#define GL_SCISSOR_TEST                   0x0C11
#define GL_COLOR_CLEAR_VALUE              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_DOUBLEBUFFER                   0x0C32
#define GL_STEREO                         0x0C33
#define GL_LINE_SMOOTH_HINT               0x0C52
#define GL_POLYGON_SMOOTH_HINT            0x0C53
#define GL_UNPACK_SWAP_BYTES              0x0CF0
#define GL_UNPACK_LSB_FIRST               0x0CF1
#define GL_UNPACK_ROW_LENGTH              0x0CF2
#define GL_UNPACK_SKIP_ROWS               0x0CF3
#define GL_UNPACK_SKIP_PIXELS             0x0CF4
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_SWAP_BYTES                0x0D00
#define GL_PACK_LSB_FIRST                 0x0D01
#define GL_PACK_ROW_LENGTH                0x0D02
#define GL_PACK_SKIP_ROWS                 0x0D03
#define GL_PACK_SKIP_PIXELS               0x0D04
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_POLYGON_OFFSET_UNITS           0x2A00
#define GL_POLYGON_OFFSET_POINT           0x2A01
#define GL_POLYGON_OFFSET_LINE            0x2A02
#define GL_POLYGON_OFFSET_FILL            0x8037
#define GL_POLYGON_OFFSET_FACTOR          0x8038
#define GL_TEXTURE_BINDING_1D             0x8068
#define GL_TEXTURE_BINDING_2D             0x8069
// GetTextureParameter
#define GL_TEXTURE_WIDTH                  0x1000
#define GL_TEXTURE_HEIGHT                 0x1001
#define GL_TEXTURE_INTERNAL_FORMAT        0x1003
#define GL_TEXTURE_BORDER_COLOR           0x1004
#define GL_TEXTURE_RED_SIZE               0x805C
#define GL_TEXTURE_GREEN_SIZE             0x805D
#define GL_TEXTURE_BLUE_SIZE              0x805E
#define GL_TEXTURE_ALPHA_SIZE             0x805F
// HintMode
#define GL_DONT_CARE                      0x1100
#define GL_FASTEST                        0x1101
#define GL_NICEST                         0x1102
// DataType
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_DOUBLE                         0x140A
// ErrorCode
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
// LogicOp
#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F
// MatrixMode (for gl3.h, FBO attachment type)
#define GL_TEXTURE                        0x1702
// PixelCopyType
#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802
// PixelFormat
#define GL_STENCIL_INDEX                  0x1901
#define GL_DEPTH_COMPONENT                0x1902
#define GL_RED                            0x1903
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
// PolygonMode
#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02
// StencilOp
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
// StringName
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03
// TextureMagFilter
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
// TextureMinFilter
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703
// TextureParameterName
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
// TextureTarget
#define GL_PROXY_TEXTURE_1D               0x8063
#define GL_PROXY_TEXTURE_2D               0x8064
// TextureWrapMode
#define GL_REPEAT                         0x2901
// PixelInternalFormat
#define GL_R3_G3_B2                       0x2A10
#define GL_RGB4                           0x804F
#define GL_RGB5                           0x8050
#define GL_RGB8                           0x8051
#define GL_RGB10                          0x8052
#define GL_RGB12                          0x8053
#define GL_RGB16                          0x8054
#define GL_RGBA2                          0x8055
#define GL_RGBA4                          0x8056
#define GL_RGB5_A1                        0x8057
#define GL_RGBA8                          0x8058
#define GL_RGB10_A2                       0x8059
#define GL_RGBA12                         0x805A
#define GL_RGBA16                         0x805B
typedef void (APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei count);
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
typedef void (APIENTRYP PFNGLGETPOINTERVPROC) (GLenum pname, GLvoid** params);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat factor, GLfloat units);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid* pixels);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, const GLuint* textures);
typedef void (APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint* textures);
typedef GLboolean(APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
extern PFNGLDRAWARRAYSPROC OglDrawArrays;
extern PFNGLDRAWELEMENTSPROC OglDrawElements;
extern PFNGLGETPOINTERVPROC OglGetPointerv;
extern PFNGLPOLYGONOFFSETPROC OglPolygonOffset;
extern PFNGLCOPYTEXIMAGE1DPROC OglCopyTexImage1D;
extern PFNGLCOPYTEXIMAGE2DPROC OglCopyTexImage2D;
extern PFNGLCOPYTEXSUBIMAGE1DPROC OglCopyTexSubImage1D;
extern PFNGLCOPYTEXSUBIMAGE2DPROC OglCopyTexSubImage2D;
extern PFNGLTEXSUBIMAGE1DPROC OglTexSubImage1D;
extern PFNGLTEXSUBIMAGE2DPROC OglTexSubImage2D;
extern PFNGLBINDTEXTUREPROC OglBindTexture;
extern PFNGLDELETETEXTURESPROC OglDeleteTextures;
extern PFNGLGENTEXTURESPROC OglGenTextures;
extern PFNGLISTEXTUREPROC OglIsTexture;
#define glDrawArrays		OglDrawArrays
#define glDrawElements		OglDrawElements
#define glGetPointerv		OglGetPointerv
#define glPolygonOffset		OglPolygonOffset
#define glCopyTexImage1D		OglCopyTexImage1D
#define glCopyTexImage2D		OglCopyTexImage2D
#define glCopyTexSubImage1D		OglCopyTexSubImage1D
#define glCopyTexSubImage2D		OglCopyTexSubImage2D
#define glTexSubImage1D		OglTexSubImage1D
#define glTexSubImage2D		OglTexSubImage2D
#define glBindTexture		OglBindTexture
#define glDeleteTextures		OglDeleteTextures
#define glGenTextures		OglGenTextures
#define glIsTexture		OglIsTexture
#endif	// GL_VERSION_1_1

#ifndef GL_VERSION_1_2
#define GL_VERSION_1_2 1

#define GL_UNSIGNED_BYTE_3_3_2            0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_INT_8_8_8_8           0x8035
#define GL_UNSIGNED_INT_10_10_10_2        0x8036
#define GL_TEXTURE_BINDING_3D             0x806A
#define GL_PACK_SKIP_IMAGES               0x806B
#define GL_PACK_IMAGE_HEIGHT              0x806C
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_TEXTURE_3D                     0x806F
#define GL_PROXY_TEXTURE_3D               0x8070
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_UNSIGNED_BYTE_2_3_3_REV        0x8362
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV       0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV     0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV     0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#define GL_BGR                            0x80E0
#define GL_BGRA                           0x80E1
#define GL_MAX_ELEMENTS_VERTICES          0x80E8
#define GL_MAX_ELEMENTS_INDICES           0x80E9
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_TEXTURE_MIN_LOD                0x813A
#define GL_TEXTURE_MAX_LOD                0x813B
#define GL_TEXTURE_BASE_LEVEL             0x813C
#define GL_TEXTURE_MAX_LEVEL              0x813D
#define GL_SMOOTH_POINT_SIZE_RANGE        0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY  0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE        0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY  0x0B23
#define GL_ALIASED_LINE_WIDTH_RANGE       0x846E

typedef void (APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid* indices);
typedef void (APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* pixels);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern PFNGLBLENDCOLORPROC OglBlendColor;
extern PFNGLBLENDEQUATIONPROC OglBlendEquation;
extern PFNGLDRAWRANGEELEMENTSPROC OglDrawRangeElements;
extern PFNGLTEXIMAGE3DPROC OglTexImage3D;
extern PFNGLTEXSUBIMAGE3DPROC OglTexSubImage3D;
extern PFNGLCOPYTEXSUBIMAGE3DPROC OglCopyTexSubImage3D;
#define glBlendColor		OglBlendColor
#define glBlendEquation		OglBlendEquation
#define glDrawRangeElements		OglDrawRangeElements
#define glTexImage3D		OglTexImage3D
#define glTexSubImage3D		OglTexSubImage3D
#define glCopyTexSubImage3D		OglCopyTexSubImage3D
#endif	// GL_VERSION_1_2

#ifndef GL_VERSION_1_3
#define GL_VERSION_1_3 1

#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_MULTISAMPLE                    0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_ALPHA_TO_ONE            0x809F
#define GL_SAMPLE_COVERAGE                0x80A0
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB
#define GL_TEXTURE_CUBE_MAP               0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP         0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE      0x851C
#define GL_COMPRESSED_RGB                 0x84ED
#define GL_COMPRESSED_RGBA                0x84EE
#define GL_TEXTURE_COMPRESSION_HINT       0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE  0x86A0
#define GL_TEXTURE_COMPRESSED             0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#define GL_CLAMP_TO_BORDER                0x812D

typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat value, GLboolean invert);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid* data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid* data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid* data);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint level, GLvoid* img);
extern PFNGLACTIVETEXTUREPROC OglActiveTexture;
extern PFNGLSAMPLECOVERAGEPROC OglSampleCoverage;
extern PFNGLCOMPRESSEDTEXIMAGE3DPROC OglCompressedTexImage3D;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC OglCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXIMAGE1DPROC OglCompressedTexImage1D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC OglCompressedTexSubImage3D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC OglCompressedTexSubImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC OglCompressedTexSubImage1D;
extern PFNGLGETCOMPRESSEDTEXIMAGEPROC OglGetCompressedTexImage;
#define glActiveTexture		OglActiveTexture
#define glSampleCoverage		OglSampleCoverage
#define glCompressedTexImage3D		OglCompressedTexImage3D
#define glCompressedTexImage2D		OglCompressedTexImage2D
#define glCompressedTexImage1D		OglCompressedTexImage1D
#define glCompressedTexSubImage3D		OglCompressedTexSubImage3D
#define glCompressedTexSubImage2D		OglCompressedTexSubImage2D
#define glCompressedTexSubImage1D		OglCompressedTexSubImage1D
#define glGetCompressedTexImage		OglGetCompressedTexImage
#endif	// GL_VERSION_1_3

#ifndef GL_VERSION_1_4
#define GL_VERSION_1_4 1

#define GL_BLEND_DST_RGB                  0x80C8
#define GL_BLEND_SRC_RGB                  0x80C9
#define GL_BLEND_DST_ALPHA                0x80CA
#define GL_BLEND_SRC_ALPHA                0x80CB
#define GL_POINT_FADE_THRESHOLD_SIZE      0x8128
#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7
#define GL_MIRRORED_REPEAT                0x8370
#define GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#define GL_TEXTURE_LOD_BIAS               0x8501
#define GL_INCR_WRAP                      0x8507
#define GL_DECR_WRAP                      0x8508
#define GL_TEXTURE_DEPTH_SIZE             0x884A
#define GL_TEXTURE_COMPARE_MODE           0x884C
#define GL_TEXTURE_COMPARE_FUNC           0x884D

typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSPROC) (GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSPROC) (GLenum mode, const GLsizei* count, GLenum type, const GLvoid* const* indices, GLsizei drawcount);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFVPROC) (GLenum pname, const GLfloat* params);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIPROC) (GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIVPROC) (GLenum pname, const GLint* params);
extern PFNGLBLENDFUNCSEPARATEPROC OglBlendFuncSeparate;
extern PFNGLMULTIDRAWARRAYSPROC OglMultiDrawArrays;
extern PFNGLMULTIDRAWELEMENTSPROC OglMultiDrawElements;
extern PFNGLPOINTPARAMETERFPROC OglPointParameterf;
extern PFNGLPOINTPARAMETERFVPROC OglPointParameterfv;
extern PFNGLPOINTPARAMETERIPROC OglPointParameteri;
extern PFNGLPOINTPARAMETERIVPROC OglPointParameteriv;
#define glBlendFuncSeparate		OglBlendFuncSeparate
#define glMultiDrawArrays		OglMultiDrawArrays
#define glMultiDrawElements		OglMultiDrawElements
#define glPointParameterf		OglPointParameterf
#define glPointParameterfv		OglPointParameterfv
#define glPointParameteri		OglPointParameteri
#define glPointParameteriv		OglPointParameteriv
#endif	// GL_VERSION_1_4

#ifndef GL_VERSION_1_5
#define GL_VERSION_1_5 1
#define GL_BUFFER_SIZE                    0x8764
#define GL_BUFFER_USAGE                   0x8765
#define GL_QUERY_COUNTER_BITS             0x8864
#define GL_CURRENT_QUERY                  0x8865
#define GL_QUERY_RESULT                   0x8866
#define GL_QUERY_RESULT_AVAILABLE         0x8867
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_ARRAY_BUFFER_BINDING           0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#define GL_READ_ONLY                      0x88B8
#define GL_WRITE_ONLY                     0x88B9
#define GL_READ_WRITE                     0x88BA
#define GL_BUFFER_ACCESS                  0x88BB
#define GL_BUFFER_MAPPED                  0x88BC
#define GL_BUFFER_MAP_POINTER             0x88BD
#define GL_STREAM_DRAW                    0x88E0
#define GL_STREAM_READ                    0x88E1
#define GL_STREAM_COPY                    0x88E2
#define GL_STATIC_DRAW                    0x88E4
#define GL_STATIC_READ                    0x88E5
#define GL_STATIC_COPY                    0x88E6
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA
#define GL_SAMPLES_PASSED                 0x8914
#define GL_SRC1_ALPHA                     0x8589

typedef void (APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint* ids);
typedef void (APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, const GLuint* ids);
typedef GLboolean(APIENTRYP PFNGLISQUERYPROC) (GLuint id);
typedef void (APIENTRYP PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
typedef void (APIENTRYP PFNGLENDQUERYPROC) (GLenum target);
typedef void (APIENTRYP PFNGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint* params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTIVPROC) (GLuint id, GLenum pname, GLint* params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint* params);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint* buffers);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint* buffers);
typedef GLboolean(APIENTRYP PFNGLISBUFFERPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
typedef void (APIENTRYP PFNGLGETBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, GLvoid* data);
typedef GLvoid* (APIENTRYP PFNGLMAPBUFFERPROC) (GLenum target, GLenum access);
typedef GLboolean(APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum target);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint* params);
typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum target, GLenum pname, GLvoid** params);
extern PFNGLGENQUERIESPROC OglGenQueries;
extern PFNGLDELETEQUERIESPROC OglDeleteQueries;
extern PFNGLISQUERYPROC OglIsQuery;
extern PFNGLBEGINQUERYPROC OglBeginQuery;
extern PFNGLENDQUERYPROC OglEndQuery;
extern PFNGLGETQUERYIVPROC OglGetQueryiv;
extern PFNGLGETQUERYOBJECTIVPROC OglGetQueryObjectiv;
extern PFNGLGETQUERYOBJECTUIVPROC OglGetQueryObjectuiv;
extern PFNGLBINDBUFFERPROC OglBindBuffer;
extern PFNGLDELETEBUFFERSPROC OglDeleteBuffers;
extern PFNGLGENBUFFERSPROC OglGenBuffers;
extern PFNGLISBUFFERPROC OglIsBuffer;
extern PFNGLBUFFERDATAPROC OglBufferData;
extern PFNGLBUFFERSUBDATAPROC OglBufferSubData;
extern PFNGLGETBUFFERSUBDATAPROC OglGetBufferSubData;
extern PFNGLMAPBUFFERPROC OglMapBuffer;
extern PFNGLUNMAPBUFFERPROC OglUnmapBuffer;
extern PFNGLGETBUFFERPARAMETERIVPROC OglGetBufferParameteriv;
extern PFNGLGETBUFFERPOINTERVPROC OglGetBufferPointerv;
#define glGenQueries		OglGenQueries
#define glDeleteQueries		OglDeleteQueries
#define glIsQuery		OglIsQuery
#define glBeginQuery		OglBeginQuery
#define glEndQuery		OglEndQuery
#define glGetQueryiv		OglGetQueryiv
#define glGetQueryObjectiv		OglGetQueryObjectiv
#define glGetQueryObjectuiv		OglGetQueryObjectuiv
#define glBindBuffer		OglBindBuffer
#define glDeleteBuffers		OglDeleteBuffers
#define glGenBuffers		OglGenBuffers
#define glIsBuffer		OglIsBuffer
#define glBufferData		OglBufferData
#define glBufferSubData		OglBufferSubData
#define glGetBufferSubData		OglGetBufferSubData
#define glMapBuffer		OglMapBuffer
#define glUnmapBuffer		OglUnmapBuffer
#define glGetBufferParameteriv		OglGetBufferParameteriv
#define glGetBufferPointerv		OglGetBufferPointerv
#endif	// GL_VERSION_1_5

#endif // NWG_OGL_V1_H