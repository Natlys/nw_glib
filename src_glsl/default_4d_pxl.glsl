#version 460 core
// iput;
in VS_INFO{vec4 vtx_crd;vec2 txr_crd;vec4 nrm_crd;}psi;
layout(location=0)uniform sampler2D txr_idx;
// oput;
layout(location=0)out vec4 pso_pxl_clr_0;
// functions;
void main()
{
	vec4 txr_clr;
	
	txr_clr = texture(txr_idx, psi.txr_crd).rgba;

	pso_pxl_clr_0 = txr_clr;
}