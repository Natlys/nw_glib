#version 400 core

out vec4 pso_pxlClr;

in VS_INFO {
	vec4 vtxCrd;
	vec2 texCrd;
} psi;

uniform vec4 unf_abdClr;
uniform sampler2D unf_texIdx;

void main()
{
	pso_pxlClr = vec4(texture(unf_texIdx, psi.texCrd).rgba);
	//pso_pxlClr *= unf_abdClr;
}