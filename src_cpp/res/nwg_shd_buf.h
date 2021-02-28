#ifndef NWG_SHADER_BUFFER_H
#define NWG_SHADER_BUFFER_H
#include <nwg_core.hpp>
#if (defined NWG_GAPI)
#include <res/nwg_buf.h>
#include <res/nwg_layout.h>
namespace NWG
{
	/// ShaderBuffer class
	/// Description:
	/// -- Is used by shaders as opengl uniform buffer, or as directx constant buffer
	class NWG_API ShaderBuf : public AGfxBuf
	{
	public:
		ShaderBuf(GfxEngine& rGfx);
		virtual ~ShaderBuf();
		// --setters
		template<typename CType> void SetData(CType* pData = nullptr);
		void SetSubData(Size szData, const Ptr pData, Size szOffset = 0);
		void SetLayout(ShaderLayout& rShdLayout);
		// --core_methods
		virtual void OnDraw() override;
		void Bind(UInt32 unPoint);
		void Bind(UInt32 unPoint, Size szData, Size szOffset = 0);
	private:
		bool Remake(const GfxBufInfo& rInfo);
	};
	template<typename CType> void ShaderBuf::SetData(CType* pData) {
		GfxBufInfo gdInfo(sizeof(CType), sizeof(CType), 0, pData);
		Remake(gdInfo);
	}
}
#endif	// NWG_GAPI
#endif	// NWG_BUFFER_H