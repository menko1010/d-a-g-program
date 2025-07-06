#include"common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_Texture_1 : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 OutDiffuse : SV_Target)
{
    OutDiffuse.rgb = g_Texture_1.Sample(g_SamplerState, In.TexCoord);
    OutDiffuse.a = 0.5f;
}