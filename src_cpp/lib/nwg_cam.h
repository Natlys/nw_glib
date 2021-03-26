#ifndef NWG_CAMERA_H
#define NWG_CAMERA_H
#include <nwg_core.hpp>
#if (defined NW_GAPI)
#include <lib/nwg_const.h>
namespace NW
{
	enum camera_modes : v1ui {
		CAM_DEFAULT = 0,
		CAM_2D = 2, CAM_3D = 3,
	};
	/// camera class
	/// description:
	/// --makes all relevant rotation and movement calculations
	/// --makes projection and view-lookAt matricies
	/// interface:
	/// ->config Frustrum, tarGet, 
	/// ->set coordinates and rotation
	/// ->get transform matricies: proj and view
	class NW_API camera
	{
	public:
		using mode = camera_modes;
	public:
		camera();
		// --getters
		inline v1f get_fov() const   { return m_fov; }
		inline v1f get_ratio() const { return m_ratio; }
		inline v2f get_clips() const { return m_clips; }
		inline v3f get_crd() const   { return m_crd; }
		inline v3f get_rtn() const   { return m_rtn; }
		inline v3f get_right_dir(v1f scalar = 1.0f) const { return v3f{ -m_right.x, +m_right.y, -m_right.z } * scalar; }
		inline v3f get_upper_dir(v1f scalar = 1.0f) const { return v3f{ -m_upper.x, +m_upper.y, -m_upper.z } * scalar; }
		inline v3f get_front_dir(v1f scalar = 1.0f) const { return v3f{ -m_front.x, +m_front.y, -m_front.z } * scalar; }
		inline v3f get_right_crd(v1f scalar = 1.0f) const { return m_right * -scalar + m_crd; }
		inline v3f get_upper_crd(v1f scalar = 1.0f) const { return m_upper * -scalar + m_crd; }
		inline v3f get_front_crd(v1f scalar = 1.0f) const { return get_front_dir(scalar) + m_crd; }
		inline const m4f& get_proj() const  { return m_proj; }
		inline const m4f& get_view() const  { return m_view; }
		inline const m4f& get_tform() const { return m_tform; }
		inline const mode& get_mode() const { return m_mode; }
		// --setters
		void set_fov(v1f field_of_view);
		void set_ratio(v1f aspect_ratio);
		void set_ratio(v1f size_x, v1f size_y);
		void set_clips(const v2f& near_and_far);
		void set_crd(const v3f& coord);
		void set_rtn(const v3f& rotation);
		void set_mode(mode mode);
		// --core_methods
		void update();
	protected:
		v1f m_fov;
		v1f m_ratio;
		v2f m_clips;
		v3f m_crd, m_rtn;
		v3f m_right, m_upper, m_front;
		m4f m_tform, m_view, m_proj;
		camera_modes m_mode;
	};
}
#endif	// NW_GAPI
#endif // NWG_CAMERA_H