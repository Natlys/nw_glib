//#shader_type vertex
// 13d:02m:2021y_6:50 - my first shader in high_level_shading_language
// {return type} main({arg type} : {semantic}) : {semantic}
// SV_Position - system value position
// The bare minimum for rendering is vertex positions for rasterizing
struct VS_OUT {
	float3 vtxClr : color;
	float4 vtxCrd : SV_Position;
};

VS_OUT main(float3 atb_vtxCrd : coord)
{
	VS_OUT vs_out;
	vs_out.vtxCrd = float4(atb_vtxCrd.x, atb_vtxCrd.y, atb_vtxCrd.z, 1.0f);
	vs_out.vtxClr = float3(atb_vtxCrd.x, atb_vtxCrd.y, atb_vtxCrd.z);
	return vs_out;
}