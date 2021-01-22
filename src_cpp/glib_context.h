#ifndef GLIB_ACONTEXT_H
#define GLIB_ACONTEXT_H

#include <glib_decl.hpp>

#if (defined GLIB_GAPI)
namespace GLIB
{
	/// GraphicsContextInfo struct
	struct GLIB_API GContextInfo
	{
		const char* strRenderer = "none", *strVersion = "1.0.0", *strVendor = "none",
			*strShadingLanguage = "none";
		Int32 nMaxVertexAttribs = 0;
		Int32 nActiveTextureId = 0;
		Int32 nMaxTextures = 0;
		GContextInfo() = default;
		explicit GContextInfo(CString sRenderer, CString sVersion,
			CString sVendor, CString sShadingLanguage) :
			strRenderer(sRenderer), strVersion(sVersion),
			strVendor(sVendor), strShadingLanguage(sShadingLanguage) { }
		explicit GContextInfo(const UChar* sRenderer, const UChar* sVersion,
			const UChar* sVendor, const UChar* sShadingLanguage) :
			strRenderer((CString)sRenderer), strVersion((CString)sVersion),
			strVendor((CString)sVendor), strShadingLanguage((CString)sShadingLanguage) { }
	};
	/// GraphicalContext Abstract Class
	/// Interface:
	/// -> Create the graphical context -> Initialize it
	/// -> Swap buffers after rendering
	class GLIB_API AGContext
	{
	public:
		virtual ~AGContext() = default;

		// --getters
		virtual inline const GContextInfo& GetInfo() = 0;
		// --setters

		// Interface Methods
		virtual bool OnInit() = 0;
		virtual void OnQuit() = 0;

		virtual void SwapBuffers() = 0;
	};
}
#endif	// GLIB_GAPI
#if (GLIB_GAPI & GLIB_GAPI_OGL)
namespace GLIB
{
	class GLIB_API GContextOgl : public AGContext
	{
	public:
		GContextOgl(GLFWwindow* pNativeWindow);
		~GContextOgl();

		// --getters
		virtual inline const GContextInfo& GetInfo() override { return m_GContextInfo; }
		// --setters

		// --core_methods
		virtual bool OnInit() override;
		virtual void OnQuit() override;

		virtual void SwapBuffers() override;
	private: 
		GLFWwindow* m_pNativeWindow;
		GContextInfo m_GContextInfo;
	};
}
#endif // GLIB_GAPI
#endif // GLIB_CONTEXT_H