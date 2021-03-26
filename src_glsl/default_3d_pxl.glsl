#version 460 core

in VS_INFO{vec4 vtx_crd;vec2 txr_crd;vec3 nrm_crd;}psi;

layout(location=0)out vec4 pso_pxl_clr_0;

layout(location=0)uniform sampler2D cst_txr_idx_0;
layout(location=1)uniform sampler2D cst_txr_idx_1;

void main()
{
	vec4 txr_clr;
	
	txr_clr = mix(
		texture(cst_txr_idx_0, psi.txr_crd).rgba,
		texture(cst_txr_idx_1, psi.txr_crd).rgba,
		0.2f
	);

	if (txr_clr.r == 0.0f || txr_clr.g == 0.0f || txr_clr.b == 0.0f) { discard; }
	
	pso_pxl_clr_0 = txr_clr;
}