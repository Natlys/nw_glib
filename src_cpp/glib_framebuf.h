#ifndef GLIB_AFRAME_BUFFER_H
#define GLIB_AFRAME_BUFFER_H
<<<<<<< HEAD
#include <core/glib_res.h>
=======

>>>>>>> 9ad0d477aed6a69908705117542e1a84eda465e1
#include <glib_decl.hpp>

#if (defined GLIB_GAPI)
namespace GLIB
{
	/// FrameBufInfo struct
	struct GLIB_API FrameBufInfo
	{
		UInt32 unWidth = 0, unHeight = 0;
		UInt32 unSamples = 1;

		bool bSwapChainTarget = false;
	};
	/// Abstract FrameBuf class
<<<<<<< HEAD
	class GLIB_API AFrameBuf : public AGRes
=======
	class GLIB_API AFrameBuf
>>>>>>> 9ad0d477aed6a69908705117542e1a84eda465e1
	{
	public:
		AFrameBuf(const char* strName, const FrameBufInfo& rFbInfo);
		virtual ~AFrameBuf();
	
		// --getters
		inline const UInt32 GetRenderId() const { return m_unRId; }
		inline const UInt32 GetRenderIdDepth() const { return m_unRIdDepth; }
		inline const ATexture2d* GetColorAttachment() const { return m_ColorAttach; }
		inline const FrameBufInfo& GetInfo() const { return m_Info; }
		// --setters
		void SetSizeWH(UInt32 unWidth, UInt32 unHeight);
		// --core_methods
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void Remake() = 0;
		virtual void Clear(UInt32 unAttachmentsMask = FB_COLOR | FB_DEPTH | FB_STENCIL) = 0;
		
<<<<<<< HEAD
		// --data_methods
		virtual bool SaveF(const char* strFPath) override { return true; }
		virtual bool LoadF(const char* strFPath) override { return true; }

=======
>>>>>>> 9ad0d477aed6a69908705117542e1a84eda465e1
		static AFrameBuf* Create(const char* strName, const FrameBufInfo& rFbInfo);
	protected:
		UInt32 m_unRId;
		UInt32 m_unRIdDepth;
		ATexture2d* m_ColorAttach;
		FrameBufInfo m_Info;
	};
}
#endif	// GLIB_GAPI
#if (GLIB_GAPI & GLIB_GAPI_OGL)
namespace GLIB
{
	/// FrameBufOpenGL
	class FrameBufOgl : public AFrameBuf
	{
	public:
		FrameBufOgl(const char* strName, const FrameBufInfo& rFbInfo);
		virtual ~FrameBufOgl();

		// --core_methods
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Remake() override;
		virtual void Clear(UInt32 unAttachmentsMask = FB_COLOR | FB_DEPTH | FB_STENCIL) override;
	};
}
#endif // GLIB_GAPI
#endif // GLIB_AFRAME_BUFFER_H