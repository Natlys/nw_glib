#ifndef NWG_DATA_HPP
#define NWG_DATA_HPP
#include <lib/nwg_data.h>
// vertex
namespace NW
{
	static inline const darray<vtx_2f2f> vtx_quad_2f2f = {
	{ { -1.0f,	-1.0f },	{ 0.00f,	0.00f } },	// lt-bt
	{ { -1.0f,	+1.0f },	{ 0.00f,	1.00f } },	// lt-tp
	{ { +1.0f,	+1.0f },	{ 1.00f,	1.00f } },	// rt-tp
	{ { +1.0f,	-1.0f },	{ 1.00f,	0.00f } },	// rt-bt
	};
	static inline const darray<vtx_3f> vtx_cube_3f = {
		// lt
		{ { -1.0f, -1.0f,  1.0f } },
		{ { -1.0f, -1.0f, -1.0f } },
		{ { -1.0f,  1.0f, -1.0f } },
		{ { -1.0f,  1.0f,  1.0f } },
		// rt
		{  { 1.0f, -1.0f, -1.0f } },
		{  { 1.0f, -1.0f,  1.0f } },
		{  { 1.0f,  1.0f,  1.0f } },
		{  { 1.0f,  1.0f, -1.0f } },
		// bt
		{ { -1.0f, -1.0f, -1.0f } },
		{ { -1.0f, -1.0f,  1.0f } },
		{ {  1.0f, -1.0f, -1.0f } },
		{ { -1.0f, -1.0f,  1.0f } },
		// tp
		{ { -1.0f,  1.0f, -1.0f } },
		{ {  1.0f,  1.0f, -1.0f } },
		{ {  1.0f,  1.0f,  1.0f } },
		{ { -1.0f,  1.0f,  1.0f } },
		// bk
		{ { -1.0f,  1.0f, -1.0f } },
		{ { -1.0f, -1.0f, -1.0f } },
		{ {  1.0f, -1.0f, -1.0f } },
		{ {  1.0f,  1.0f, -1.0f } },
		// ft
		{ { -1.0f, -1.0f,  1.0f } },
		{ { -1.0f,  1.0f,  1.0f } },
		{ {  1.0f,  1.0f,  1.0f } },
		{ {  1.0f, -1.0f,  1.0f } },
	};
	static inline const darray<vtx_3f2f3f> vtx_cube_3f2f3f = {
		// lt
		{ { -0.5f,	-0.5f,	-0.5f },	{ 0.00f,	0.00f },	{ -1.0f,	+0.0f,	+0.0f } },
		{ { -0.5f,	-0.5f,	+0.5f },	{ 0.00f,	1.00f },	{ -1.0f,	+0.0f,	+0.0f } },
		{ { -0.5f,	+0.5f,	+0.5f },	{ 1.00f,	1.00f },	{ -1.0f,	+0.0f,	+0.0f } },
		{ { -0.5f,	+0.5f,	-0.5f },	{ 1.00f,	0.00f },	{ -1.0f,	+0.0f,	+0.0f } },
		// rt
		{ { +0.5f,	-0.5f,	-0.5f },	{ 0.00f,	0.00f },	{ +1.0f,	+0.0f,	+0.0f } },
		{ { +0.5f,	-0.5f,	+0.5f },	{ 0.00f,	1.00f },	{ +1.0f,	+0.0f,	+0.0f } },
		{ { +0.5f,	+0.5f,	+0.5f },	{ 1.00f,	1.00f },	{ +1.0f,	+0.0f,	+0.0f } },
		{ { +0.5f,	+0.5f,	-0.5f },	{ 1.00f,	0.00f },	{ +1.0f,	+0.0f,	+0.0f } },
		// bt
		{ { -0.5f,	-0.5f,	-0.5f },	{ 0.00f,	0.00f },	{ +0.0f,	-1.0f,	+0.0f } },
		{ { -0.5f,	-0.5f,	+0.5f },	{ 0.00f,	1.00f },	{ +0.0f,	-1.0f,	+0.0f } },
		{ { +0.5f,	-0.5f,	+0.5f },	{ 1.00f,	1.00f },	{ +0.0f,	-1.0f,	+0.0f } },
		{ { +0.5f,	-0.5f,	-0.5f },	{ 1.00f,	0.00f },	{ +0.0f,	-1.0f,	+0.0f } },
		// tp
		{ { -0.5f,	+0.5f,	-0.5f },	{ 0.00f,	1.00f },	{ +0.0f,	+1.0f,	+0.0f } },
		{ { -0.5f,	+0.5f,	-0.5f },	{ 0.00f,	1.00f },	{ +0.0f,	+1.0f,	+0.0f } },
		{ { +0.5f,	+0.5f,	+0.5f },	{ 1.00f,	1.00f },	{ +0.0f,	+1.0f,	+0.0f } },
		{ { +0.5f,	-0.5f,	+0.5f },	{ 1.00f,	0.00f },	{ +0.0f,	+1.0f,	+0.0f } },
		// bk
		{ { -0.5f,	-0.5f,	-0.5f },	{ 0.00f,	0.00f },	{ +0.0f,	+0.0f,	-1.0f} },
		{ { -0.5f,	+0.5f,	-0.5f },	{ 0.00f,	1.00f },	{ +0.0f,	+0.0f,	-1.0f} },
		{ { +0.5f,	+0.5f,	-0.5f },	{ 1.00f,	1.00f },	{ +0.0f,	+0.0f,	-1.0f} },
		{ { +0.5f,	-0.5f,	-0.5f },	{ 1.00f,	0.00f },	{ +0.0f,	+0.0f,	-1.0f} },
		// ft
		{ { -0.5f,	-0.5f,	+0.5f },	{ 0.00f,	0.00f },	{ +0.0f,	+0.0f,	+1.0f } },
		{ { -0.5f,	+0.5f,	+0.5f },	{ 0.00f,	1.00f },	{ +0.0f,	+0.0f,	+1.0f } },
		{ { +0.5f,	+0.5f,	+0.5f },	{ 1.00f,	1.00f },	{ +0.0f,	+0.0f,	+1.0f } },
		{ { +0.5f,	-0.5f,	+0.5f },	{ 1.00f,	0.00f },	{ +0.0f,	+0.0f,	+1.0f } },
	};
}
// index
namespace NW
{
	static inline const darray<v1ui> idx_cube = {
		0,	1,	2,
		3,	4,	5,

		6,	7,	8,
		9,	10,	11,

		12,	13,	14,
		15,	16,	17,

		18,	19,	20,
		21,	22,	23,

		24,	25,	26,
		27,	28,	29,

		30,	31,	32,
		33,	34,	35,
	};
}
// shader code
namespace NW
{
#if (NW_GAPI & NW_GAPI_OGL)
static inline const cstr shd_default_3d_vtx = R"(
#version 460 core

layout(location = 0)in vec3 vsi_vtx_crd;
layout(location = 1)in vec2 vsi_txr_crd;
layout(location = 2)in vec3 vsi_nrm_crd;

out VS_INFO{vec4 vtx_crd;vec2 txr_crd;vec3 nrm_crd;}vso;

layout(std140)uniform cst_transform{mat4 cst_model;mat4 cst_view;mat4 cst_proj;};

void main()
{
	gl_Position =
		cst_proj *
		cst_view *
		cst_model *
		vec4(vsi_vtx_crd.xyz, 1.0f);

	vso.vtx_crd = gl_Position;
	vso.txr_crd = vsi_txr_crd;
	vso.nrm_crd = vsi_nrm_crd;
}
)";
static inline const cstr shd_default_3d_pxl = R"(
#version 460 core

in VS_INFO{vec4 vtx_crd;vec2 txr_crd;vec3 nrm_crd;}psi;

layout(location=0)out vec4 pso_pxl_clr_0;

layout(location=0)uniform sampler2D cst_txr_idx_0;
//layout(location=1)uniform sampler2D cst_txr_idx_1;
//layout(location=2)uniform sampler2D cst_txr_idx_2;

void main()
{
	vec4 txr_clr;
	
	txr_clr = texture(cst_txr_idx_0, psi.txr_crd).rgba;
/*
	txr_clr = mix(
		txr_clr,
		texture(cst_txr_idx_0, psi.txr_crd).rgba,
		0.33f
	);

	txr_clr = mix(
		txr_clr,
		texture(cst_txr_idx_1, psi.txr_crd).rgba,
		0.33f
	);
	txr_clr = mix(
		txr_clr,
		texture(cst_txr_idx_2, psi.txr_crd).rgba,
		0.33f
	);
*/

	if (txr_clr.r == 0.0f || txr_clr.g == 0.0f || txr_clr.b == 0.0f) { discard; }
	
	pso_pxl_clr_0 = txr_clr;
}
)";
#endif
#if (NW_GAPI & NW_GAPI_DX)
static inline const cstr shd_default_3d_vtx = R"(
struct VS_IN {
	float3 vtx_crd : vsi_vtx_crd;
	float2 txr_crd : vsi_txr_crd;
	float3 nrm_crd : vsi_nrm_crd;
};
struct VS_OUT {
	float4 vtx_crd : sv_position;
	float2 txr_crd : vso_txr_crd;
	float3 nrm_crd : vso_nrm_crd;
};

cbuffer cbf_transform {
	row_major matrix cst_model;
	row_major matrix cst_view;
	row_major matrix cst_proj;
};

VS_OUT main(VS_IN vsi)
{
	VS_OUT vso;
	vso.vtx_crd = float4(vsi.vtx_crd.x, vsi.vtx_crd.y, vsi.vtx_crd.z, 1.0f);
	vso.vtx_crd = mul(vso.vtx_crd, cst_model);
	vso.vtx_crd = mul(vso.vtx_crd, cst_view);
	vso.vtx_crd = mul(vso.vtx_crd, cst_proj);
	vso.txr_crd = vsi.txr_crd;
	vso.nrm_crd = vsi.nrm_crd;
	return vso;
}
)";
static inline const cstr shd_default_3d_pxl = R"(
Texture2D cst_txr : register(ps, t[0]);
SamplerState cst_smp : register(ps, s[0]);

float4 main(float4 vtx_crd : sv_position, float2 txr_crd : vso_txr_crd, float3 nrm_crd : vso_nrm_crd) : sv_target
{
	//float4 pxl_clr = cst_txr.Sample(cst_smp, txr_crd);
	//float4 pxl_clr = float4(txr_crd.x, txr_crd.y, txr_crd.x, 1.0f);
	float4 pxl_clr = float4(vtx_crd.x, vtx_crd.y, vtx_crd.z, 1.0f);
	
	return pxl_clr;
}
)";
#endif
}
#endif	// NWG_DATA_HPP