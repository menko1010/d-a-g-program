#include"common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
	
    float4 WorldNormal, Normal;
    Normal = float4(In.Normal.xyz, 0.0);
    WorldNormal = mul(Normal, World);
    WorldNormal = normalize(WorldNormal);

    float light = -dot(Light.Direction.xyz, WorldNormal.xyz) * 0.5 + 0.5;
    light = saturate(light);

    Out.Diffuse = In.Diffuse * Material.Diffuse * light * Light.Diffuse;
    Out.Diffuse += In.Diffuse * Material.Ambient * Light.Ambient;
    Out.Diffuse += Material.Emission;
    Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;

    Out.Position = mul(In.Position, wvp);
    Out.TexCoord = In.TexCoord;

    Out.Normal.xyz = WorldNormal.xyz;
    Out.WorldPosition = mul(In.Position, World);
}