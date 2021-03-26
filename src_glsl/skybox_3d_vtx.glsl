#version 460 core

layout(location = 0) in vec3 vsi_vtx_crd;

out VS_INFO{vec3 txr_crd;}vso;

layout(std140)uniform cst_transform{mat4 cst_model;mat4 cst_view;mat4 cst_proj;};

void main()
{
	mat4 no_move_view = mat4(mat3(cst_view));

	gl_Position =
		cst_proj *
		no_move_view *
		vec4(vsi_vtx_crd.xyz, 1.0f);
	
	gl_Position = gl_Position.xyww;

	vso.txr_crd = vsi_vtx_crd;
}