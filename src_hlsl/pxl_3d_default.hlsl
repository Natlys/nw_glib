Texture2D cst_tex0 : register(ps, t[0]);
SamplerState cst_smp0 : register(ps, s[0]);

float4 main(float2 texCrd : vs_tex_crd, float3 nrmCrd : vs_nrm_crd) : sv_target
{
	return cst_tex0.Sample(cst_smp0, texCrd);
}