#ifndef NWG_FRAME_BUFFER_H
#define NWG_FRAME_BUFFER_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <res/nwg_res.h>
#include <res/nwg_texture.h>
namespace NWG
{
	/// FrameBufInfo struct
	struct NWG_API FrameBufInfo : public AInfo
	{
	public:
		V4i rectViewport = { 0, 0, 1, 1 };
		Bit bSwapTarget = false;
		Bit bResizable = true;
		Bit bHasDepth = false;
		Bit bHasStencil = false;
		UInt32 unColorCount = 0u;
	public:
		// --getters
		inline Int32 GetSizeW() const { return { rectViewport.z - rectViewport.x }; }
		inline Int32 GetSizeH() const { return { rectViewport.w - rectViewport.y }; }
		// --operators
		virtual OutStream& operator<<(OutStream& rStream) const override;
		virtual InStream& operator>>(InStream& rStream) override;
	};
}
namespace NWG
{
	/// FrameBuffer class
	class NWG_API FrameBuf : public AGfxRes, public ADataRes
	{
	public:
		FrameBuf(GfxEngine& rGfx, const char* strName, const FrameBufInfo& rFbInfo);
		virtual ~FrameBuf();
		// --getters
		inline Int32 GetSizeW() const { return m_Info.GetSizeW(); }
		inline Int32 GetSizeH() const { return m_Info.GetSizeH(); }
		inline const V4i& GetViewport() const { return m_Info.rectViewport; }
		inline const V4f GetClearColor() const { return m_rgbaClear; }
		inline const FrameBufInfo& GetInfo() const { return m_Info; }
		inline Texture* GetAttachment(UInt32 unIdx = 0) { return m_Attachments[unIdx]; }
		// --setters
		void SetViewport(V4i rectViewport);
		void SetClearColor(V4f rgbaClear);
		void AttachTexture(RefKeeper<Texture>& rTex);
		void DetachTexture(UInt32 unIdx);
		// --core_methods
		virtual void OnDraw() override;
		void Remake();
		void Clear();
		void ReadPixels(Ptr pData, UInt32 unAttachIdx, Int32 nX, Int32 nY, Int32 nWidth = 1, Int32 nHeight = 1);
		void WritePixels(Ptr pData, UInt32 unAttachIdx, Int32 nX, Int32 nY, Int32 nWidth = 1, Int32 nHeight = 1);
		// --data_methods
		virtual bool SaveF(const char* strFPath) override;
		virtual bool LoadF(const char* strFPath) override;
	protected:
		FrameBufInfo m_Info;
		V4f m_rgbaClear;
		DArray<Texture*> m_Attachments;
	};
}
#endif	// NWG_GAPI
#endif // NWG_FRAME_BUFFER_H