#ifndef GLIB_DECL_HPP
#define GLIB_DECL_HPP

#include <glib_core.hpp>

namespace GLIB
{
	class GLIB_API AGApi;
	class GLIB_API GEngine;
	struct GLIB_API GLayer;
	class GLIB_API GCameraLad;

	class GLIB_API AShader;
	class GLIB_API GMaterial;

	class GLIB_API ATexture;
	class GLIB_API ATexture1d;
	class GLIB_API ATexture2d;
	class GLIB_API ATexture3d;

	class GLIB_API ADrawable;
	class GLIB_API Particles;
	class GLIB_API PolyLine;
	class GLIB_API Polygons;
	class GLIB_API Triangle;
	class GLIB_API Rectangle;
	class GLIB_API Mesh3d;

	class GLIB_API AGContext;
	class GLIB_API AFrameBuf;

	class GLIB_API VertexBufLayout;
	class GLIB_API ShaderBufLayout;

	class GLIB_API AVertexBuf;
	class GLIB_API AIndexBuf;
	class GLIB_API AShaderBuf;
}
namespace GLIB
{
	struct GLIB_API GCamera;

	struct GLIB_API FrameBufInfo;
	struct GLIB_API ImageInfo;
	struct GLIB_API TextureInfo;
	struct GLIB_API RenderInfo;

	struct GLIB_API VertexBatch1d;
	struct GLIB_API VertexBatch2d;
	struct GLIB_API VertexShape3d;

	struct GLIB_API BufferElement;

	struct GLIB_API SubTexture1d;
	struct GLIB_API SubTexture2d;
	struct GLIB_API SubTexture3d;

	struct GLIB_API RenderAttribs;
	struct GLIB_API RenderLayer;
}
namespace GLIB
{
	/// window_api_types
	enum WApiTypes : UInt32 {
		WAPI_NONE = 0,
		WAPI_GLFW
	};
	/// graphics_api_types
	/// Interface:
	/// -> Give it to the GraphicsApi create function
	/// -> Check the types for the abstracted usage
	enum GApiTypes : UInt32
	{
		GAPI_NONE = 0,
		GAPI_OPENGL = GLIB_GAPI_OGL
	};
	enum GraphicsBufTypes : UInt32 {
		GBT_VERTEX = GLIB_GBUFFER_VERTEX,
		GBT_INDEX = GLIB_GBUFFER_INDEX,
		GBT_SHADER = GLIB_GBUFFER_SHADER
	};
	/// Data that can be loaded in a shader
	enum ShaderDataTypes : UInt32
	{
		SDT_NONE = GLIB_ERR_NO_DATA,
		SDT_BOOL = GLIB_BOOL, SDT_INT8 = GLIB_INT8, SDT_UINT8 = GLIB_UINT8,
		SDT_INT16 = GLIB_INT16, SDT_UINT16 = GLIB_UINT16,
		SDT_INT32 = GLIB_INT32, SDT_UINT32 = GLIB_UINT32,
		SDT_FLOAT32 = GLIB_FLOAT32, SDT_FLOAT64 = GLIB_FLOAT64,

		//SDT_FLOAT32_VEC2 = GLIB_FLOAT32_VEC2, SDT_FLOAT32_VEC3 = GLIB_FLOAT32_VEC3, SDT_FLOAT32_VEC4 = GLIB_FLOAT32_VEC4,
		//SDT_FLOAT32_MAT2 = GLIB_FLOAT32_MAT2, SDT_FLOAT32_MAT3 = GLIB_FLOAT32_MAT3, SDT_FLOAT32_MAT4 = GLIB_FLOAT32_MAT4

		SDT_SAMPLER = GLIB_SAMPLER_1D
	};
	/// Accessible (maintained) shader types
	enum ShaderTypes : UInt32
	{
		ST_SHADER = GLIB_SHADER,
		ST_VERTEX = GLIB_SHADER_VERTEX,
		ST_GEOMETRY = GLIB_SHADER_GEOMETRY,
		ST_PIXEL = GLIB_SHADER_PIXEL
	};
	enum FrameBufs : UInt32
	{
		FB_COLOR = GLIB_BUFFER_COLOR_BIT,
		FB_DEPTH = GLIB_BUFFER_DEPTH_BIT,
		FB_STENCIL = GLIB_BUFFER_STENCIL_BIT
	};
	enum GPrimitiveTypes : UInt32
	{
		PT_POINTS = GLIB_POINTS,
		PT_LINES = GLIB_LINES,
		PT_LINE_LOOP = GLIB_LINE_LOOP,
		PT_LINE_STRIP = GLIB_LINE_STRIP,
		PT_TRIANGLES = GLIB_TRIANGLES,
		PT_TRIANGLE_FAN = GLIB_TRIANGLE_FAN,
		PT_TRIANGLE_STRIP = GLIB_TRIANGLE_STRIP,
		PT_QUADS = GLIB_QUADS,
		PT_QUADS_STRIP = GLIB_QUAD_STRIP
	};
	enum DrawModes : UInt32
	{
		DM_LINE = GLIB_LINE,
		DM_FILL = GLIB_FILL
	};
	enum FacePlanes : UInt32
	{
		FP_FRONT_AND_BACK = GLIB_FRONT_AND_BACK,
		FP_FRONT = GLIB_FRONT,
		FP_BACK = GLIB_BACK,
		FP_RIGTH = GLIB_RIGHT,
		FP_LEFT = GLIB_LEFT,
	};
	enum ProcModes : UInt32
	{
		PM_BLEND = GLIB_BLEND,
		PM_DEPTH_TEST = GLIB_DEPTH_TEST,
		PM_STENCIL_TEST = GLIB_STENCIL_TEST
	};
	enum BlendConfigs : UInt32
	{
		BC_SRC_ALPHA = GLIB_SRC_ALPHA,
		BC_SRC_COLOR = GLIB_SRC_COLOR,
		BC_ONE_MINUS_SRC_ALPHA = GLIB_ONE_MINUS_SRC_ALPHA,
		BC_ONE_MINUS_SRC_COLOR = GLIB_ONE_MINUS_SRC_COLOR,
		BC_DST_ALPHA = GLIB_DST_ALPHA,
		BC_DST_COLOR = GLIB_DST_COLOR,
		BC_ONE_MUNUS_DST_ALPHA = GLIB_ONE_MINUS_DST_ALPHA,
		BC_ONE_MINUS_DST_COLOR = GLIB_ONE_MINUS_DST_COLOR,
	};
	enum DepthConfigs : UInt32
	{
		DC_EQUAL = GLIB_EQUAL,
		DC_LESS = GLIB_LESS, DC_LEQUAL = GLIB_LEQUAL,
		DC_GREATER = GLIB_GREATER, DC_GEQUAL = GLIB_GEQUAL,
		DC_NEVER = GLIB_NEVER, DC_ALWAYS = GLIB_ALWAYS
	};
	enum StencilConfigs : UInt32 {
		SC_KEEP = GLIB_KEEP, SC_ZERO = GLIB_ZERO, SC_REPLACE = GLIB_REPLACE, SC_INVERT = GLIB_INVERT,
		SC_INCR = GLIB_INCR, SC_DECR = GLIB_DECR
	};
	enum TextureTypes : UInt32 {
		TT_1D = GLIB_TEXTURE_1D, TT_2D = GLIB_TEXTURE_2D, TT_3D = GLIB_TEXTURE_3D,
	};
	enum TextureConfigs : UInt32 {
		TC_WRAP_REPEAT = GLIB_TEXTURE_WRAP_REPEAT, TC_WRAP_CLAMP = GLIB_TEXTURE_WRAP_CLAMP,
		TC_FILTER_LINEAR = GLIB_TEXTURE_FILTER_LINEAR, TC_FILTER_NEAREST = GLIB_TEXTURE_FILTER_NEAREST,
		TC_FORMAT_RED = GLIB_RED, TC_FORMAT_GREEN = GLIB_GREEN, TC_FORMAT_BLUE = GLIB_BLUE,
		TC_FORMAT_RGB = GLIB_RGB, TC_FORMAT_RGBA = GLIB_RGBA, TC_FORMAT_RGBA8 = GLIB_RGBA8,
	};
	//	--==</structs_enums>==--

#if (GLIB_GAPI & GLIB_GAPI_OGL)
	class GLIB_API GContextOgl;
	class GLIB_API FrameBufOgl;

	class GLIB_API VertexArrOgl;
	class GLIB_API VertexBufOgl;
	class GLIB_API IndexBufOgl;

	class GLIB_API ShaderOgl;
	class GLIB_API ShaderProg;
	class GLIB_API AGMaterialOgl;
	class GLIB_API Texture2dOgl;
#endif	// GLIB_GAPI
}

#define GLIB_MAX_TEXTURES 8
#define GLIB_MIN_TEXTURES 1

#define GLIB_MAX_DRAW_LAYERS 10
#define GLIB_MAX_DRAW_ORDERS 10


#endif	// GLIB_DECL_HPP