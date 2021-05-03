#version 460 core
// iput;
layout(location = 0)in vec4 vsi_vtx_crd;
layout(location = 1)in vec2 vsi_txr_crd;
layout(location = 2)in vec4 vsi_nrm_crd;
// oput;
out VS_INFO{vec4 vtx_crd;vec2 txr_crd;vec4 nrm_crd;}vso;
// functions;
void main()
{
	gl_Position.x = vsi_vtx_crd.x / vsi_vtx_crd.z / vsi_vtx_crd.w;
	gl_Position.y = vsi_vtx_crd.y / vsi_vtx_crd.z / vsi_vtx_crd.w;
	gl_Position.z = vsi_vtx_crd.z;
	gl_Position.w = 1.0f;

	vso.vtx_crd = gl_Position;
	vso.txr_crd = vsi_txr_crd;
	vso.nrm_crd = vsi_nrm_crd;
}