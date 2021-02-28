#ifndef NWG_CORE_HPP
#define NWG_CORE_HPP

// --==<configuration>==--
#if defined NWG_BUILD_LIB
#	define NWG_API
#else
#	if defined NWG_BUILD_DLL
#		define NWG_API __declspec(dllexport)
#	else
#		define NWG_API __declspec(dllimport)
#	endif
#endif

#define NWG_GAPI_OGL	1 << 1
#define NWG_GAPI_DX		1 << 2
#define NWG_GAPI		NWG_GAPI_OGL

#if (NWG_GAPI & NWG_GAPI_OGL)
using GfxDevice = HDC;
using GfxContext = HGLRC;
using GfxLib = HMODULE;
#endif	// NWG_GAPI
#if (NWG_GAPI & NWG_GAPI_DX)
using GfxDevice = ID3D11Device*;
using GfxContext = ID3D11DeviceContext*;
using GfxLib = HMODULE;
#endif	// NWG_GAPI
// --==</configurations>==--
#include <nwg_pch.hpp>
namespace NWG
{
	class NWG_API GfxEngine;
	class NWG_API FrameBuf;

	class NWG_API AGfxRes;
	class NWG_API ADrawCmp;
	class NWG_API DrawVtxCmp;
	class NWG_API DrawIdxCmp;

	class NWG_API VertexBuf;
	class NWG_API IndexBuf;
	class NWG_API ShaderBuf;

	class NWG_API ShaderProg;
	class NWG_API Shader;
	class NWG_API VertexShader;
	class NWG_API PixelShader;
	class NWG_API GeometryShader;

	class NWG_API Texture;
	class NWG_API GfxMaterial;

	struct NWG_API GfxCamera;
}
#endif	// NWG_CORE_HPP