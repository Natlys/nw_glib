#ifndef GLIB_GMATERIAL_H
#define GLIB_GMATERIAL_H
<<<<<<< HEAD
#include <core/glib_res.h>
=======

>>>>>>> 9ad0d477aed6a69908705117542e1a84eda465e1
#include <glib_tools.h>

namespace GLIB
{
	/// GraphicsMaterial Class
	/// Description:
<<<<<<< HEAD
	class GLIB_API GMaterial : public AGRes
=======
	class GLIB_API GMaterial
>>>>>>> 9ad0d477aed6a69908705117542e1a84eda465e1
	{
	public:
		using Textures = HashMap<String, ATexture*>;
		using Colors = HashMap<String, V4f>;
	public:
		GMaterial(const char* strName);
<<<<<<< HEAD
		GMaterial(GMaterial& rCpy);
=======
>>>>>>> 9ad0d477aed6a69908705117542e1a84eda465e1
		virtual ~GMaterial();

		// --getters
		inline AShader* GetShader() { return m_pShader; }
		inline UInt8 GetTexCount() { return m_Textures.size(); }
		inline Textures& GetTextures() { return m_Textures; }
		inline Colors& GetColors() { return m_Colors; }
		inline ATexture* GetTexture(const char* strType = "") {
			if (strcmp(strType, "") == 0) { return m_Textures.begin()->second; }
			auto itTex = m_Textures.find(&strType[0]);
			return itTex == m_Textures.end() ? nullptr : itTex->second;
		}
		inline V4f* GetColor(const char* strType = "") {
			if (strcmp(strType, "") == 0) { return &m_Colors.begin()->second; }
			auto itClr = m_Colors.find(&strType[0]);
			return itClr == m_Colors.end() ? nullptr : &itClr->second;
		}
		// --setters
		void SetShader(AShader* pShader);
		void SetTexture(ATexture* pTex, const char* strType = "");
		void SetColor(const V4f& rgbaClr, const char* strType = "");
		// --core_methods
		void Enable();
		void Disable();
<<<<<<< HEAD
		// --data_methods
		virtual bool SaveF(const char* strFPath) override;
		virtual bool LoadF(const char* strFPath) override;
	public:
=======
	public:
		String m_strName;
>>>>>>> 9ad0d477aed6a69908705117542e1a84eda465e1
		AShader* m_pShader;
		Textures m_Textures;
		Colors m_Colors;
	};
}

#endif // GLIB_AGMATERIAL_H