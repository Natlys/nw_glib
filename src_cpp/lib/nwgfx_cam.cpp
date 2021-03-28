#include "nwgfx_pch.hpp"
#include "nwgfx_cam.h"
#if (defined NW_GAPI)
namespace NWGFX
{
	gfx_cam::gfx_cam() :
		m_fov(1.0f), m_ratio(16.0f / 9.0f),
		m_clips{ 0.01f, 100.0f },
		m_crd{ 0.0f, 0.0f, 1.0f }, m_rtn{ 0.0f, 0.0f, 0.0f },
		m_right{ 1.0f, 0.0f, 0.0f }, m_upper{ 0.0f, 1.0f, 0.0f }, m_front{ 0.0f, 0.0f, 1.0f },
		m_mode(CAM_2D),
		m_tform(m4f(1.0f)), m_proj(m4f(1.0f)), m_view(m4f(1.0f))
	{
		set_mode(CAM_2D);
	}
	// --getters
	void gfx_cam::set_fov(v1f field_of_view) {
		m_fov = field_of_view;
	}
	void gfx_cam::set_ratio(v1f aspect_ratio) {
		m_ratio = aspect_ratio;
	}
	void gfx_cam::set_ratio(v1f size_x, v1f size_y) {
		m_ratio = size_x / size_y;
	}
	void gfx_cam::set_clips(const v2f& near_and_far) {
		m_clips = near_and_far;
	}
	void gfx_cam::set_crd(const v3f& coord) {
		m_crd = coord;
	}
	void gfx_cam::set_rtn(const v3f& rotation) {
		m_rtn = rotation;
	}
	void gfx_cam::set_mode(mode mode) {
		m_mode = mode;
		switch (mode) {
		case CAM_2D:
			m_clips = { -1000.0f, +1000.0f };
			m_fov = 1.0f;
			break;
		case CAM_3D:
			m_clips = { 0.01f, 100.0f };
			m_fov = 45.0f;
			break;
		}
	}
	// --==<core_methods>==--
	void gfx_cam::update()
	{
		m_ratio = get_max(m_ratio, 0.01f);

		v3f next_front = v3f(0.0f, 0.0f, 0.0f);
		v1f pitch_rad = deg_to_rad(m_rtn.x);
		v1f yaw_rad = deg_to_rad(m_rtn.y);
		v1f roll_rad = deg_to_rad(m_rtn.z);

		switch (m_mode) {
		case CAM_2D:
			next_front.x = cosf(roll_rad);
			next_front.y = sinf(roll_rad);

			v2f bounds = { m_fov * m_ratio, m_fov };
			m_proj = mat_ortho(-bounds[0], +bounds[0], -bounds[1], +bounds[1], m_clips[0], m_clips[1]);
			m_tform = mat_move(m4f(1.0f), -m_crd);
			break;
		case CAM_3D:
			next_front.x = sinf(yaw_rad) * cosf(pitch_rad);
			next_front.y = sinf(pitch_rad);
			next_front.z = cosf(yaw_rad) * cosf(pitch_rad);
			
			m_proj = mat_perspect(deg_to_rad(m_fov), m_ratio, m_clips[0], m_clips[1]);
			m_tform = mat_move(m4f(1.0f), m_crd);
			break;
		}
		/// i advice you not to change this order;
		/// we were suffering two weeks with "drunk" gfx_cam because of this;
		m_tform = m_tform
			* mat_rotate(m4f(1.0f), yaw_rad, v3f(0.0f, 1.0f, 0.0f))
			* mat_rotate(m4f(1.0f), pitch_rad, v3f(1.0f, 0.0f, 0.0f))
			* mat_rotate(m4f(1.0f), roll_rad, v3f(0.0f, 0.0f, 1.0f));
		m_view = mat_inverse(m_tform);
		
		m_front = glm::normalize(next_front);
		m_right = glm::normalize(glm::cross(m_front, { 0.0f, 1.0f, 0.0f }));
		m_upper = glm::normalize(glm::cross(m_right, m_front));
	}
	// --==</core_methods>==--
}
#endif	// NW_GAPI