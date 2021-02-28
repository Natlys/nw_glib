#include <nwg_pch.hpp>
#include "nwg_ogl_v1.h"
#include "nwg_ogl_loader.h"
namespace NWG
{
	void OglLoadV1()
	{
#if (defined GL_VERSION_1_0)
		// --drawing
		OglBegin = (PFNGLBEGINPROC)OglGetProc("glBegin");
		OglEnd = (PFNGLENDPROC)OglGetProc("glEnd");
		OglVertex2si16 = (PFNGLVERTEX2SPROC)OglGetProc("glVertex2s");
		OglVertex3si16 = (PFNGLVERTEX3SPROC)OglGetProc("glVertex3s");
		OglVertex4si16 = (PFNGLVERTEX4SPROC)OglGetProc("glVertex4s");
		OglVertex2si32 = (PFNGLVERTEX2IPROC)OglGetProc("glVertex2i");
		OglVertex3si32 = (PFNGLVERTEX3IPROC)OglGetProc("glVertex3i");
		OglVertex4si32 = (PFNGLVERTEX4IPROC)OglGetProc("glVertex4i");
		OglVertex2f32 = (PFNGLVERTEX2FPROC)OglGetProc("glVertex2f");
		OglVertex3f32 = (PFNGLVERTEX3FPROC)OglGetProc("glVertex3f");
		OglVertex4f32 = (PFNGLVERTEX4FPROC)OglGetProc("glVertex4f");
		OglVertex2f64 = (PFNGLVERTEX2DPROC)OglGetProc("glVertex2d");
		OglVertex3f64 = (PFNGLVERTEX3DPROC)OglGetProc("glVertex3d");
		OglVertex4f64 = (PFNGLVERTEX4DPROC)OglGetProc("glVertex4d");
		OglColor3si8 = (PFNGLCOLOR3BPROC)OglGetProc("glColor3b");
		OglColor4si8 = (PFNGLCOLOR4BPROC)OglGetProc("glColor4b");
		OglColor3ui8 = (PFNGLCOLOR3UBPROC)OglGetProc("glColor3ub");
		OglColor4ui8 = (PFNGLCOLOR4UBPROC)OglGetProc("glColor4ub");
		OglColor3si16 = (PFNGLCOLOR3SPROC)OglGetProc("glColor3s");
		OglColor4si16 = (PFNGLCOLOR4SPROC)OglGetProc("glColor4s");
		OglColor3ui16 = (PFNGLCOLOR3USPROC)OglGetProc("glColor3us");
		OglColor4ui16 = (PFNGLCOLOR4USPROC)OglGetProc("glColor4us");
		OglColor3si32 = (PFNGLCOLOR3IPROC)OglGetProc("glColor3i");
		OglColor4si32 = (PFNGLCOLOR4IPROC)OglGetProc("glColor4i");
		OglColor3ui32 = (PFNGLCOLOR3UIPROC)OglGetProc("glColor3ui");
		OglColor4ui32 = (PFNGLCOLOR4UIPROC)OglGetProc("glColor4ui");
		OglColor3f32 = (PFNGLCOLOR3FPROC)OglGetProc("glColor3f");
		OglColor4f32 = (PFNGLCOLOR4FPROC)OglGetProc("glColor4f");
		OglColor3f64 = (PFNGLCOLOR3DPROC)OglGetProc("glColor3d");
		OglColor4f64 = (PFNGLCOLOR4DPROC)OglGetProc("glColor4d");
		// --configs
		OglCullFace = (PFNGLCULLFACEPROC)OglGetProc("glCullFace");
		OglFrontFace = (PFNGLFRONTFACEPROC)OglGetProc("glFrontFace");
		OglHint = (PFNGLHINTPROC)OglGetProc("glHint");
		OglLineWidth = (PFNGLLINEWIDTHPROC)OglGetProc("glLineWidth");
		OglPointSize = (PFNGLPOINTSIZEPROC)OglGetProc("glPointSize");
		OglPolygonMode = (PFNGLPOLYGONMODEPROC)OglGetProc("glPolygonMode");
		OglScissor = (PFNGLSCISSORPROC)OglGetProc("glScissor");
		// --textures
		OglTexParameterf = (PFNGLTEXPARAMETERFPROC)OglGetProc("glTexParameterf");
		OglTexParameterfv = (PFNGLTEXPARAMETERFVPROC)OglGetProc("glTexParameterfv");
		OglTexParameteri = (PFNGLTEXPARAMETERIPROC)OglGetProc("glTexParameteri");
		OglTexParameteriv = (PFNGLTEXPARAMETERIVPROC)OglGetProc("glTexParameteriv");
		OglTexImage1D = (PFNGLTEXIMAGE1DPROC)OglGetProc("glTexImage1D");
		OglTexImage2D = (PFNGLTEXIMAGE2DPROC)OglGetProc("glTexImage2D");
		// --framebuffers
		OglDrawBuffer = (PFNGLDRAWBUFFERPROC)OglGetProc("glDrawBuffer");
		OglDrawPixels = (PFNGLDRAWPIXELSPROC)OglGetProc("glDrawPixels");
		OglClear = (PFNGLCLEARPROC)OglGetProc("glClear");
		OglClearColor = (PFNGLCLEARCOLORPROC)OglGetProc("glClearColor");
		OglClearStencil = (PFNGLCLEARSTENCILPROC)OglGetProc("glClearStencil");
		OglClearDepth = (PFNGLCLEARDEPTHPROC)OglGetProc("glClearDepth");
		OglStencilMask = (PFNGLSTENCILMASKPROC)OglGetProc("glStencilMask");
		OglColorMask = (PFNGLCOLORMASKPROC)OglGetProc("glColorMask");
		OglDepthMask = (PFNGLDEPTHMASKPROC)OglGetProc("glDepthMask");
		OglDisable = (PFNGLDISABLEPROC)OglGetProc("glDisable");
		OglEnable = (PFNGLENABLEPROC)OglGetProc("glEnable");
		OglFinish = (PFNGLFINISHPROC)OglGetProc("glFinish");
		OglFlush = (PFNGLFLUSHPROC)OglGetProc("glFlush");
		OglBlendFunc = (PFNGLBLENDFUNCPROC)OglGetProc("glBlendFunc");
		OglLogicOp = (PFNGLLOGICOPPROC)OglGetProc("glLogicOp");
		OglStencilFunc = (PFNGLSTENCILFUNCPROC)OglGetProc("glStencilFunc");
		OglStencilOp = (PFNGLSTENCILOPPROC)OglGetProc("glStencilOp");
		OglDepthFunc = (PFNGLDEPTHFUNCPROC)OglGetProc("glDepthFunc");
		OglPixelStoref = (PFNGLPIXELSTOREFPROC)OglGetProc("glPixelStoref");
		OglPixelStorei = (PFNGLPIXELSTOREIPROC)OglGetProc("glPixelStorei");
		OglReadBuffer = (PFNGLREADBUFFERPROC)OglGetProc("glReadBuffer");
		OglReadPixels = (PFNGLREADPIXELSPROC)OglGetProc("glReadPixels");
		OglGetBooleanv = (PFNGLGETBOOLEANVPROC)OglGetProc("glGetBooleanv");
		OglGetDoublev = (PFNGLGETDOUBLEVPROC)OglGetProc("glGetDoublev");
		OglGetError = (PFNGLGETERRORPROC)OglGetProc("glGetError");
		OglGetFloatv = (PFNGLGETFLOATVPROC)OglGetProc("glGetFloatv");
		OglGetIntegerv = (PFNGLGETINTEGERVPROC)OglGetProc("glGetIntegerv");
		OglGetString = (PFNGLGETSTRINGPROC)OglGetProc("glGetString");
		OglGetTexImage = (PFNGLGETTEXIMAGEPROC)OglGetProc("glGetTexImage");
		OglGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)OglGetProc("glGetTexParameterfv");
		OglGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)OglGetProc("glGetTexParameteriv");
		OglGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC)OglGetProc("glGetTexLevelParameterfv");
		OglGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC)OglGetProc("glGetTexLevelParameteriv");
		OglIsEnabled = (PFNGLISENABLEDPROC)OglGetProc("glIsEnabled");
		OglDepthRange = (PFNGLDEPTHRANGEPROC)OglGetProc("glDepthRange");
		OglViewport = (PFNGLVIEWPORTPROC)OglGetProc("glViewport");
#endif	// GL_VERSION_1_0
#if (defined GL_VERSION_1_1)
		OglDrawArrays = (PFNGLDRAWARRAYSPROC)OglGetProc("glDrawArrays");
		OglDrawElements = (PFNGLDRAWELEMENTSPROC)OglGetProc("glDrawElements");
		OglGetPointerv = (PFNGLGETPOINTERVPROC)OglGetProc("glGetPointerv");
		OglPolygonOffset = (PFNGLPOLYGONOFFSETPROC)OglGetProc("glPolygonOffset");
		OglCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC)OglGetProc("glCopyTexImage1D");
		OglCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)OglGetProc("glCopyTexImage2D");
		OglCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC)OglGetProc("glCopyTexSubImage1D");
		OglCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)OglGetProc("glCopyTexSubImage2D");
		OglTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)OglGetProc("glTexSubImage1D");
		OglTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)OglGetProc("glTexSubImage2D");
		OglBindTexture = (PFNGLBINDTEXTUREPROC)OglGetProc("glBindTexture");
		OglDeleteTextures = (PFNGLDELETETEXTURESPROC)OglGetProc("glDeleteTextures");
		OglGenTextures = (PFNGLGENTEXTURESPROC)OglGetProc("glGenTextures");
		OglIsTexture = (PFNGLISTEXTUREPROC)OglGetProc("glIsTexture");
#endif	// GL_VERSION_1_1
#if (defined GL_VERSION_1_2)
		OglBlendColor = (PFNGLBLENDCOLORPROC)OglGetProc("glBlendColor");
		OglBlendEquation = (PFNGLBLENDEQUATIONPROC)OglGetProc("glBlendEquation");
		OglDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)OglGetProc("glDrawRangeElements");
		OglTexImage3D = (PFNGLTEXIMAGE3DPROC)OglGetProc("glTexImage3D");
		OglTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)OglGetProc("glTexSubImage3D");
		OglCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)OglGetProc("glCopyTexSubImage3D");
#endif	// GL_VERSION_1_2
#if (defined GL_VERSION_1_3)
		OglActiveTexture = (PFNGLACTIVETEXTUREPROC)OglGetProc("glActiveTexture");
		OglSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)OglGetProc("glSampleCoverage");
		OglCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)OglGetProc("glCompressedTexImage3D");
		OglCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)OglGetProc("glCompressedTexImage2D");
		OglCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)OglGetProc("glCompressedTexImage1D");
		OglCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)OglGetProc("glCompressedTexSubImage3D");
		OglCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)OglGetProc("glCompressedTexSubImage2D");
		OglCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)OglGetProc("glCompressedTexSubImage1D");
		OglGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)OglGetProc("glGetCompressedTexImage");
#endif	// GL_VERSION_1_3
#if (defined GL_VERSION_1_4)
		OglBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)OglGetProc("glBlendFuncSeparate");
		OglMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)OglGetProc("glMultiDrawArrays");
		OglMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)OglGetProc("glMultiDrawElements");
		OglPointParameterf = (PFNGLPOINTPARAMETERFPROC)OglGetProc("glPointParameterf");
		OglPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)OglGetProc("glPointParameterfv");
		OglPointParameteri = (PFNGLPOINTPARAMETERIPROC)OglGetProc("glPointParameteri");
		OglPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)OglGetProc("glPointParameteriv");
#endif	// GL_VERSION_1_4
#if (defined GL_VERSION_1_5)
		OglGenQueries = (PFNGLGENQUERIESPROC)OglGetProc("glGenQueries");
		OglDeleteQueries = (PFNGLDELETEQUERIESPROC)OglGetProc("glDeleteQueries");
		OglIsQuery = (PFNGLISQUERYPROC)OglGetProc("glIsQuery");
		OglBeginQuery = (PFNGLBEGINQUERYPROC)OglGetProc("glBeginQuery");
		OglEndQuery = (PFNGLENDQUERYPROC)OglGetProc("glEndQuery");
		OglGetQueryiv = (PFNGLGETQUERYIVPROC)OglGetProc("glGetQueryiv");
		OglGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)OglGetProc("glGetQueryObjectiv");
		OglGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)OglGetProc("glGetQueryObjectuiv");
		OglBindBuffer = (PFNGLBINDBUFFERPROC)OglGetProc("glBindBuffer");
		OglDeleteBuffers = (PFNGLDELETEBUFFERSPROC)OglGetProc("glDeleteBuffers");
		OglGenBuffers = (PFNGLGENBUFFERSPROC)OglGetProc("glGenBuffers");
		OglIsBuffer = (PFNGLISBUFFERPROC)OglGetProc("glIsBuffer");
		OglBufferData = (PFNGLBUFFERDATAPROC)OglGetProc("glBufferData");
		OglBufferSubData = (PFNGLBUFFERSUBDATAPROC)OglGetProc("glBufferSubData");
		OglGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)OglGetProc("glGetBufferSubData");
		OglMapBuffer = (PFNGLMAPBUFFERPROC)OglGetProc("glMapBuffer");
		OglUnmapBuffer = (PFNGLUNMAPBUFFERPROC)OglGetProc("glUnmapBuffer");
		OglGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)OglGetProc("glGetBufferParameteriv");
		OglGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)OglGetProc("glGetBufferPointerv");
#endif	// GL_VERSION_1_5
	}
}
// --==<function_definitions>==--
#ifdef GL_VERSION_1_0
// --drawing
PFNGLBEGINPROC OglBegin = NULL;
PFNGLENDPROC OglEnd = NULL;
PFNGLVERTEX2SPROC OglVertex2si16 = NULL;
PFNGLVERTEX3SPROC OglVertex3si16 = NULL;
PFNGLVERTEX4SPROC OglVertex4si16 = NULL;
PFNGLVERTEX2IPROC OglVertex2si32 = NULL;
PFNGLVERTEX3IPROC OglVertex3si32 = NULL;
PFNGLVERTEX4IPROC OglVertex4si32 = NULL;
PFNGLVERTEX2FPROC OglVertex2f32 = NULL;
PFNGLVERTEX3FPROC OglVertex3f32 = NULL;
PFNGLVERTEX4FPROC OglVertex4f32 = NULL;
PFNGLVERTEX2DPROC OglVertex2f64 = NULL;
PFNGLVERTEX3DPROC OglVertex3f64 = NULL;
PFNGLVERTEX4DPROC OglVertex4f64 = NULL;
PFNGLCOLOR3BPROC OglColor3si8 = NULL;
PFNGLCOLOR4BPROC OglColor4si8 = NULL;
PFNGLCOLOR3UBPROC OglColor3ui8 = NULL;
PFNGLCOLOR4UBPROC OglColor4ui8 = NULL;
PFNGLCOLOR3SPROC OglColor3si16 = NULL;
PFNGLCOLOR4SPROC OglColor4si16 = NULL;
PFNGLCOLOR3USPROC OglColor3ui16 = NULL;
PFNGLCOLOR4USPROC OglColor4ui16 = NULL;
PFNGLCOLOR3IPROC OglColor3si32 = NULL;
PFNGLCOLOR4IPROC OglColor4si32 = NULL;
PFNGLCOLOR3UIPROC OglColor3ui32 = NULL;
PFNGLCOLOR4UIPROC OglColor4ui32 = NULL;
PFNGLCOLOR3FPROC OglColor3f32 = NULL;
PFNGLCOLOR4FPROC OglColor4f32 = NULL;
PFNGLCOLOR3DPROC OglColor3f64 = NULL;
PFNGLCOLOR4DPROC OglColor4f64 = NULL;
// --configs
PFNGLCULLFACEPROC OglCullFace;
PFNGLFRONTFACEPROC OglFrontFace;
PFNGLHINTPROC OglHint;
PFNGLLINEWIDTHPROC OglLineWidth;
PFNGLPOINTSIZEPROC OglPointSize;
PFNGLPOLYGONMODEPROC OglPolygonMode;
PFNGLSCISSORPROC OglScissor;
PFNGLTEXPARAMETERFPROC OglTexParameterf;
PFNGLTEXPARAMETERFVPROC OglTexParameterfv;
PFNGLTEXPARAMETERIPROC OglTexParameteri;
PFNGLTEXPARAMETERIVPROC OglTexParameteriv;
PFNGLTEXIMAGE1DPROC OglTexImage1D;
PFNGLTEXIMAGE2DPROC OglTexImage2D;
PFNGLDRAWBUFFERPROC OglDrawBuffer;
PFNGLDRAWPIXELSPROC OglDrawPixels;
PFNGLCLEARPROC OglClear;
PFNGLCLEARCOLORPROC OglClearColor;
PFNGLCLEARSTENCILPROC OglClearStencil;
PFNGLCLEARDEPTHPROC OglClearDepth;
PFNGLSTENCILMASKPROC OglStencilMask;
PFNGLCOLORMASKPROC OglColorMask;
PFNGLDEPTHMASKPROC OglDepthMask;
PFNGLDISABLEPROC OglDisable;
PFNGLENABLEPROC OglEnable;
PFNGLFINISHPROC OglFinish;
PFNGLFLUSHPROC OglFlush;
PFNGLBLENDFUNCPROC OglBlendFunc;
PFNGLLOGICOPPROC OglLogicOp;
PFNGLSTENCILFUNCPROC OglStencilFunc;
PFNGLSTENCILOPPROC OglStencilOp;
PFNGLDEPTHFUNCPROC OglDepthFunc;
PFNGLPIXELSTOREFPROC OglPixelStoref;
PFNGLPIXELSTOREIPROC OglPixelStorei;
PFNGLREADBUFFERPROC OglReadBuffer;
PFNGLREADPIXELSPROC OglReadPixels;
PFNGLGETBOOLEANVPROC OglGetBooleanv;
PFNGLGETDOUBLEVPROC OglGetDoublev;
PFNGLGETFLOATVPROC OglGetFloatv;
PFNGLGETERRORPROC OglGetError = NULL;
PFNGLGETINTEGERVPROC OglGetIntegerv;
PFNGLGETSTRINGPROC OglGetString;
PFNGLGETTEXIMAGEPROC OglGetTexImage;
PFNGLGETTEXPARAMETERFVPROC OglGetTexParameterfv;
PFNGLGETTEXPARAMETERIVPROC OglGetTexParameteriv;
PFNGLGETTEXLEVELPARAMETERFVPROC OglGetTexLevelParameterfv;
PFNGLGETTEXLEVELPARAMETERIVPROC OglGetTexLevelParameteriv;
PFNGLISENABLEDPROC OglIsEnabled;
PFNGLDEPTHRANGEPROC OglDepthRange;
PFNGLVIEWPORTPROC OglViewport;
#endif	// GL_VERSION_1_0

#ifdef GL_VERSION_1_1
PFNGLDRAWARRAYSPROC OglDrawArrays;
PFNGLDRAWELEMENTSPROC OglDrawElements;
PFNGLGETPOINTERVPROC OglGetPointerv;
PFNGLPOLYGONOFFSETPROC OglPolygonOffset;
PFNGLCOPYTEXIMAGE1DPROC OglCopyTexImage1D;
PFNGLCOPYTEXIMAGE2DPROC OglCopyTexImage2D;
PFNGLCOPYTEXSUBIMAGE1DPROC OglCopyTexSubImage1D;
PFNGLCOPYTEXSUBIMAGE2DPROC OglCopyTexSubImage2D;
PFNGLTEXSUBIMAGE1DPROC OglTexSubImage1D;
PFNGLTEXSUBIMAGE2DPROC OglTexSubImage2D;
PFNGLBINDTEXTUREPROC OglBindTexture;
PFNGLDELETETEXTURESPROC OglDeleteTextures;
PFNGLGENTEXTURESPROC OglGenTextures;
PFNGLISTEXTUREPROC OglIsTexture;
#endif	// GL_VERSION_1_1

#ifdef GL_VERSION_1_2
PFNGLBLENDCOLORPROC OglBlendColor;
PFNGLBLENDEQUATIONPROC OglBlendEquation;
PFNGLDRAWRANGEELEMENTSPROC OglDrawRangeElements;
PFNGLTEXIMAGE3DPROC OglTexImage3D;
PFNGLTEXSUBIMAGE3DPROC OglTexSubImage3D;
PFNGLCOPYTEXSUBIMAGE3DPROC OglCopyTexSubImage3D;
#endif	// GL_VERSION_1_2

#ifdef GL_VERSION_1_3
PFNGLACTIVETEXTUREPROC OglActiveTexture;
PFNGLSAMPLECOVERAGEPROC OglSampleCoverage;
PFNGLCOMPRESSEDTEXIMAGE3DPROC OglCompressedTexImage3D;
PFNGLCOMPRESSEDTEXIMAGE2DPROC OglCompressedTexImage2D;
PFNGLCOMPRESSEDTEXIMAGE1DPROC OglCompressedTexImage1D;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC OglCompressedTexSubImage3D;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC OglCompressedTexSubImage2D;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC OglCompressedTexSubImage1D;
PFNGLGETCOMPRESSEDTEXIMAGEPROC OglGetCompressedTexImage;
#endif	// GL_VERSION_1_3

#ifdef GL_VERSION_1_4
PFNGLBLENDFUNCSEPARATEPROC OglBlendFuncSeparate;
PFNGLMULTIDRAWARRAYSPROC OglMultiDrawArrays;
PFNGLMULTIDRAWELEMENTSPROC OglMultiDrawElements;
PFNGLPOINTPARAMETERFPROC OglPointParameterf;
PFNGLPOINTPARAMETERFVPROC OglPointParameterfv;
PFNGLPOINTPARAMETERIPROC OglPointParameteri;
PFNGLPOINTPARAMETERIVPROC OglPointParameteriv;
#endif	// GL_VERSION_1_4

#ifdef GL_VERSION_1_5
PFNGLGENQUERIESPROC OglGenQueries;
PFNGLDELETEQUERIESPROC OglDeleteQueries;
PFNGLISQUERYPROC OglIsQuery;
PFNGLBEGINQUERYPROC OglBeginQuery;
PFNGLENDQUERYPROC OglEndQuery;
PFNGLGETQUERYIVPROC OglGetQueryiv;
PFNGLGETQUERYOBJECTIVPROC OglGetQueryObjectiv;
PFNGLGETQUERYOBJECTUIVPROC OglGetQueryObjectuiv;
PFNGLBINDBUFFERPROC OglBindBuffer;
PFNGLDELETEBUFFERSPROC OglDeleteBuffers;
PFNGLGENBUFFERSPROC OglGenBuffers;
PFNGLISBUFFERPROC OglIsBuffer;
PFNGLBUFFERDATAPROC OglBufferData;
PFNGLBUFFERSUBDATAPROC OglBufferSubData;
PFNGLGETBUFFERSUBDATAPROC OglGetBufferSubData;
PFNGLMAPBUFFERPROC OglMapBuffer;
PFNGLUNMAPBUFFERPROC OglUnmapBuffer;
PFNGLGETBUFFERPARAMETERIVPROC OglGetBufferParameteriv;
PFNGLGETBUFFERPOINTERVPROC OglGetBufferPointerv;
#endif	// GL_VERSION_1_5
// --==</function_definitions>==--