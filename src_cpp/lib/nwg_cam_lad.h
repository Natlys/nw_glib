#ifndef NWG_CAMERA_LAD_H
#define NWG_CAMERA_LAD_H
#include <nwg_core.hpp>
#include "nwg_cam.h"
namespace NW
{
	/// graphics_camera_lad class
	class NW_API camera_lad : public camera
	{
	public:
		v1f rtn_speed;
		v1f move_speed;
		v1f zoom_speed;
		v3f rtn_limit;
	public:
		camera_lad();
		// --core_methods
		void update(const keyboard_state* keyboard, const mouse_state* mouse, const time_state* timer);
	};
}

#endif	// NW_CAMERA_LAD_H