#include <nwg_pch.hpp>
#include "nwg_cam_lad.h"
namespace NW
{
	camera_lad::camera_lad() :
		camera(),
		zoom_speed(-100.0f), move_speed(-4.0f), rtn_speed(-180.0f),
		rtn_limit{ 89.0f, 180.0f, 180.0f }
	{
	}
	// --==<core_methods>==--
	void camera_lad::update(const keyboard_state* keyboard, const mouse_state* mouse, const time_state* timer)
	{
		camera::update();
		if (timer == nullptr) { return; }
		if (keyboard != nullptr) {
			v1f move_delta = timer->get_delta(move_speed);
			// movement
			switch (m_mode) {
			case CAM_2D:
				if (keyboard->is_held(KBC_W)) { m_crd.y += move_delta; }
				if (keyboard->is_held(KBC_S)) { m_crd.y -= move_delta; }
				if (keyboard->is_held(KBC_D)) { m_crd.x += move_delta; }
				if (keyboard->is_held(KBC_A)) { m_crd.x -= move_delta; }
				break;
			case CAM_3D:
				if (keyboard->is_held(KBC_W)) { m_crd += glm::normalize(v3f{ m_front.x, 0.0f, m_front.z }) * move_delta; }
				if (keyboard->is_held(KBC_S)) { m_crd -= glm::normalize(v3f{ m_front.x, 0.0f, m_front.z }) * move_delta; }
				if (keyboard->is_held(KBC_D)) { m_crd += m_right * move_delta; }
				if (keyboard->is_held(KBC_A)) { m_crd -= m_right * move_delta; }
				if (keyboard->is_held(KBC_SPACE)) { m_crd.y -= move_delta; }
				if (keyboard->is_held(KBC_LSHIFT)) { m_crd.y += move_delta; }
				break;
			}
			// configuration
			if (keyboard->is_held(KBC_C)) {
				if (keyboard->is_pressed(KBC_1)) {
					set_mode(CAM_2D);
					m_crd = { 0.0f, 0.0f, 0.0f };
					m_rtn = { 0.0f, 0.0f, 0.0f };
				}
				if (keyboard->is_pressed(KBC_2)) { set_mode(CAM_2D); }
				if (keyboard->is_pressed(KBC_3)) { set_mode(CAM_3D); }
			}
		}
		if (mouse != nullptr) {
			// rotation
			v1f rtn_delta = timer->get_delta(rtn_speed);
			switch (m_mode) {
			case CAM_2D:
				if (m_rtn.z < -rtn_limit.z) { m_rtn.z = +rtn_limit.z; }
				else if (m_rtn.z > +rtn_limit.z) { m_rtn.z = -rtn_limit.z; }
				break;
			case CAM_3D:
				// move around
				if (m_rtn.y > +rtn_limit.y) { m_rtn.y = -rtn_limit.y; }
				else if (m_rtn.y < -rtn_limit.y) { m_rtn.y = +rtn_limit.y; }
				m_rtn.y += mouse->get_move_delta_x() * rtn_delta;
				// don't move further
				if (m_rtn.x > +rtn_limit.x) { m_rtn.x = +rtn_limit.x; }
				else if (m_rtn.x < -rtn_limit.x) { m_rtn.x = -rtn_limit.x; }
				m_rtn.x += mouse->get_move_delta_y() * rtn_delta;
				break;
			}
			// zooming
			v1f zoom_delta = timer->get_delta(zoom_speed) * mouse->get_scroll_delta_y();
			switch (m_mode) {
			case CAM_2D:
				m_fov = get_clamped(0.0f, 1000.0f, m_fov + m_fov * zoom_delta);
				break;
			case CAM_3D:
				m_fov = get_clamped(12.5f, 170.0f, m_fov + m_fov * zoom_delta);
				break;
			}
			// panning
			if (mouse->is_held(MSC_2)) {
				v1f move_delta = timer->get_delta(move_speed);
				m_crd.x += mouse->get_move_delta_x() * move_delta * m_fov;
				m_crd.y -= mouse->get_move_delta_y() * move_delta * m_fov;
			}
		}
	}
	// --==</core_methods>==--
}