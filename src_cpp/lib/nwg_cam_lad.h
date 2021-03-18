#ifndef NWG_CAMERA_LAD_H
#define NWG_CAMERA_LAD_H
#include <nwg_core.hpp>
#include "nwg_cam.h"
namespace NW
{
	/// graphics_camera_lad class
	class NW_API camera_lad : public camera
	{
	public: // configurable Attributes
		f32 rtn_speed, move_speed, zoom_speed;
		v3f rtn_limit;
	public:
		camera_lad();
		// --core_methods
		void update(const keyboard_state* keyboard, const mouse_state* mouse, const time_state* timer);
	};
}

#endif	// NW_CAMERA_LAD_H