#include"common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t1);
SamplerState g_SamplerState : register(s0);

static float PI = 3.141592853589;
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //視線ベクトル
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    
    //法線ベクトル
    float3 normal = normalize(In.Normal.xyz); //ラープしないため
    
    //反射ベクトル
    float3 refColor;
    {
        float3 refv = reflect(eyev.xyz, normal);
        refv = normalize(refv);
    
    //環境マッピングテクスチャ
        float2 envTexCoord;
        envTexCoord.x = atan2(refv.x, refv.z) / (PI * 2);
        envTexCoord.y = acos(refv.y) / PI;
    
    //環境マッピング
        refColor = g_Texture.Sample(g_SamplerState, envTexCoord);
    }
    
    float3 refrColor;
    {
    //屈折ベクトル
        float3 refrv = refract(eyev.xyz, normal, 1.0 / 1.5);
        refrv = normalize(refrv);
    
    //環境マッピングテクスチャ(パノラマ)
        float2 envTexCoord;
        envTexCoord.x = atan2(refrv.x, refrv.z) / (PI * 2);
        envTexCoord.y = acos(refrv.y) / PI;
    
    //環境マッピング
        refrColor = g_Texture.Sample(g_SamplerState, envTexCoord);
    }
    
    //フレネル反射率
    float f0 = 0.04;
    float d = saturate(dot(-eyev, normal));
    float fresnel = f0 + (1.0 - f0) * pow((1.0 - d), 5.0);

    outDiffuse.rgb = lerp(refrColor, refColor, fresnel);
    outDiffuse.a = fresnel * 0.5f;
}

