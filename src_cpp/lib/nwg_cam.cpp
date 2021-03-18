#include <nwg_pch.hpp>
#include "nwg_cam.h"
#if (defined NW_GAPI)
#include <math/math_tform.h>
namespace NW
{
	camera::camera() :
		m_fov(1.0f), m_ratio(16.0f / 9.0f),
		m_clips{ 0.01f, 100.0f },
		m_crd{ 0.0f, 0.0f, 1.0f }, m_rtn{ 0.0f, 0.0f, 0.0f },
		m_right{ 1.0f, 0.0f, 0.0f }, m_upper{ 0.0f, 1.0f, 0.0f }, m_front{ 0.0f, 0.0f, 1.0f },
		m_mode(GCM_2D), m_type(GCT_ORTHO),
		m_tform(m4f(1.0f)), m_proj(m4f(1.0f)), m_view(m4f(1.0f))
	{
		set_type(GCT_ORTHO);
		set_mode(GCM_2D);
	}
	// --getters
	void camera::set_fov(f32 field_of_view) {
		m_fov = field_of_view;
	}
	void camera::set_ratio(f32 aspect_ratio) {
		m_ratio = aspect_ratio;
	}
	void camera::set_ratio(f32 size_x, f32 size_y) {
		m_ratio = size_x / size_y;
	}
	void camera::set_clips(const v2f& near_and_far) {
		m_clips = near_and_far;
	}
	void camera::set_crd(const v3f& coord) {
		m_crd = coord;
	}
	void camera::set_rtn(const v3f& rotation) {
		m_rtn = rotation;
	}
	void camera::set_mode(mode mode) {
		m_mode = mode;
		switch (mode) {
		case GCM_2D:
			break;
		case GCM_3D:
			break;
		}
	}
	void camera::set_type(type type) {
		m_type = type;
		switch (type) {
		case GCT_ORTHO:
			m_clips = { -1000.0f, +1000.0f };
			m_fov = 1.0f;
			break;
		case GCT_PERSPECT:
			m_clips = { 0.01f, 100.0f };
			m_fov = 45.0f;
			break;
		}
	}
	// --==<core_methods>==--
	void camera::update()
	{
		m_ratio = get_max(m_ratio, 0.01f);

		v3f next_front = v3f(0.0f, 0.0f, 0.0f);
		f32 pitch_rad = deg_to_rad(m_rtn.x);
		f32 yaw_rad = deg_to_rad(m_rtn.y);
		f32 roll_rad = deg_to_rad(m_rtn.z);

		/// i advice you not to change this order;
		/// we were suffering two weeks with "drunk" camera because of this;
		switch (m_type) {
		case GCT_ORTHO:
			next_front.x = cosf(roll_rad);
			next_front.y = sinf(roll_rad);

			v2f bounds = { m_fov * m_ratio, m_fov };
			m_proj = mat_ortho(-bounds[0], +bounds[0], -bounds[1], +bounds[1], m_clips[0], m_clips[1]);
			m_tform = mat_move(m4f(1.0f), -m_crd);
			break;
		case GCT_PERSPECT:
			next_front.x = sinf(yaw_rad) * cosf(pitch_rad);
			next_front.y = sinf(pitch_rad);
			next_front.z = cosf(yaw_rad) * cosf(pitch_rad);
			
			m_proj = mat_perspect(deg_to_rad(m_fov), m_ratio, m_clips[0], m_clips[1]);
			m_tform = mat_move(m4f(1.0f), m_crd);
			break;
		}
		m_tform = m_tform *
			mat_rotate(m4f(1.0f), yaw_rad, v3f(0.0f, 1.0f, 0.0f)) *
			mat_rotate(m4f(1.0f), pitch_rad, v3f(1.0f, 0.0f, 0.0f)) *
			mat_rotate(m4f(1.0f), roll_rad, v3f(0.0f, 0.0f, 1.0f));
		m_view = mat_inverse(m_tform);
		
		m_front = glm::normalize(next_front);
		m_right = glm::normalize(glm::cross(m_front, { 0.0f, 1.0f, 0.0f }));
		m_upper = glm::normalize(glm::cross(m_right, m_front));
	}
	// --==</core_methods>==--
}
#endif	// NW_GAPI