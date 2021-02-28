#include <nwg_pch.hpp>
#include "nwg_buf.h"
#if (defined NWG_GAPI)
namespace NWG
{
	GfxBufInfo::GfxBufInfo(Size sizeOfData, Size sizeOfStride, Size sizeOfOffset,
		Ptr ptrToData, DataTypes dataType) :
		szData(sizeOfData), szStride(sizeOfStride), szOffset(sizeOfOffset),
		pData(ptrToData), sdType(dataType) { }
	GfxBufInfo::GfxBufInfo(Size sizeOfData, Size sizeOfStride, Size sizeOfOffset, Ptr ptrToData) :
		szData(sizeOfData), szStride(static_cast<UInt32>(sizeOfStride)), szOffset(static_cast<UInt32>(sizeOfOffset)),
		pData(ptrToData), sdType(DT_DEFAULT) { }
	// --operators
	OutStream& GfxBufInfo::operator<<(OutStream& rStream) const {
		return rStream <<
			"--==<graphics_buffer_info>==--" << std::endl <<
			"--==</graphics_buffer_info>==--" << std::endl;
	}
	InStream& GfxBufInfo::operator>>(InStream& rStream) {
		return rStream;
	}
}
#if (NWG_GAPI & NWG_GAPI_OGL)
#include <lib/nwg_ogl_v1.h>
namespace NWG
{
	AGfxBuf::AGfxBuf(GfxEngine& rGfx) :
		AGfxRes(rGfx),
		m_Info(GfxBufInfo()) { }
	AGfxBuf::~AGfxBuf() { if (m_unRId != 0) { glDeleteBuffers(1, &m_unRId); m_unRId = 0; } }
}
#endif
#if (NWG_GAPI & NWG_GAPI_DX)
#include <lib/nwg_dx_loader.h>
namespace NWG
{
	AGfxBuf::AGfxBuf(GfxEngine& rGfx) :
		AGfxRes(rGfx),
		m_Info(GfxBufInfo()),
		m_pNative(nullptr) { }
	AGfxBuf::~AGfxBuf() { if (m_pNative != nullptr) { m_pNative->Release(); m_pNative = nullptr; } }
}
#endif
#endif	// NWG_API