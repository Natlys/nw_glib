#ifndef NW_GFX_HPP
#define NW_GFX_HPP

#include "nw_gfx_core.hpp"

#include "core/nw_gfx_engine.h"
#include "core/nw_gfx_rsc.h"

#include "ecs/nw_gfx_ent.h"
#include "ecs/ent/nw_gfx_ent_idx.h"
#include "ecs/ent/nw_gfx_ent_vtx.h"
#include "ecs/ent/nw_gfx_ent_mesh.h"
#include "ecs/ent/nw_gfx_ent_prim.h"

#include "ecs/nw_gfx_cmp.h"

#include "ecs/mtl/nw_gfx_mtl.h"

#include "ecs/fmbuf/nw_gfx_fmbuf.h"

#include "ecs/stt/nw_gfx_stt.h"
#include "ecs/stt/nw_gfx_stt_blend.h"
#include "ecs/stt/nw_gfx_stt_draw.h"
#include "ecs/stt/nw_gfx_stt_ds.h"
#include "ecs/stt/nw_gfx_stt_rstr.h"

#include "ecs/buf/nw_gfx_buf.h"
#include "ecs/buf/nw_gfx_buf_vtx.h"
#include "ecs/buf/nw_gfx_buf_idx.h"
#include "ecs/buf/nw_gfx_buf_shd.h"

#include "ecs/shd/nw_gfx_shd.h"
#include "ecs/shd/nw_gfx_shd_vtx.h"
#include "ecs/shd/nw_gfx_shd_pxl.h"
#include "ecs/shd/nw_gfx_shd_gmt.h"
#include "ecs/shd/nw_gfx_shd_layt.h"

#include "ecs/txr/nw_gfx_txr.h"
#include "ecs/txr/nw_gfx_txr_2d.h"
#include "ecs/txr/nw_gfx_txr_3d.h"
#include "ecs/txr/nw_gfx_txr_smp.h"
// standard
#include "lib/nw_gfx_img.h"
#include "lib/nw_gfx_cam_lad.h"
#include "lib/nw_gfx_cam.h"
#include "lib/nw_gfx_const.h"
// loaders
#include "lib/nw_gfx_load.h"
#include "lib/nw_gfx_load_core.h"
#include "lib/nw_gfx_load_wapi.h"
#include "lib/nw_gfx_load_buf.h"
#include "lib/nw_gfx_load_fmbuf.h"
#include "lib/nw_gfx_load_shd.h"
#include "lib/nw_gfx_load_mtl.h"
#include "lib/nw_gfx_load_txr.h"
#include "lib/nw_gfx_load_smp.h"
#include "lib/nw_gfx_load_layt.h"

#endif	// NW_GFX_HPP
