#ifndef NWG_HPP
#define NWG_HPP

#include "nwg_core.hpp"

#include "core/nwg_engine.h"
#include "core/nwg_script.h"
#include "core/nwg_pass.h"

#include "ecs/nwg_ent.h"
#include "ecs/ent/nwg_ent_idx.h"
#include "ecs/ent/nwg_ent_vtx.h"
#include "ecs/ent/nwg_ent_mesh.h"
#include "ecs/ent/nwg_ent_prim.h"

#include "ecs/nwg_rsc.h"
#include "ecs/mtl/nwg_mtl.h"

#include "ecs/fmbuf/nwg_fmbuf.h"

#include "ecs/stt/nwg_stt.h"
#include "ecs/stt/nwg_stt_blend.h"
#include "ecs/stt/nwg_stt_draw.h"
#include "ecs/stt/nwg_stt_ds.h"
#include "ecs/stt/nwg_stt_rstr.h"

#include "ecs/buf/nwg_buf.h"
#include "ecs/buf/nwg_buf_vtx.h"
#include "ecs/buf/nwg_buf_idx.h"
#include "ecs/buf/nwg_buf_shd.h"

#include "ecs/shd/nwg_shd.h"
#include "ecs/shd/nwg_shd_vtx.h"
#include "ecs/shd/nwg_shd_pxl.h"
#include "ecs/shd/nwg_shd_gmt.h"
#include "ecs/shd/nwg_shd_layt.h"

#include "ecs/txr/nwg_txr.h"
#include "ecs/txr/nwg_txr_2d.h"
#include "ecs/txr/nwg_txr_3d.h"
#include "ecs/txr/nwg_txr_smp.h"

#include "lib/nwg_img.h"
#include "lib/nwg_cam_lad.h"
#include "lib/nwg_cam.h"
#include "lib/nwg_const.h"

#ifdef NW_BUILD_DLL
#	undef NW_BUILD_DLL
#endif

#endif	// NWG_HPP