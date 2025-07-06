#include"common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t1);
SamplerState g_SamplerState : register(s0);

static float PI = 3.141592853589;
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //�����x�N�g��
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    
    //�@���x�N�g��
    float3 normal = normalize(In.Normal.xyz); //���[�v���Ȃ�����
    
    //���˃x�N�g��
    float3 refColor;
    {
        float3 refv = reflect(eyev.xyz, normal);
        refv = normalize(refv);
    
    //���}�b�s���O�e�N�X�`��
        float2 envTexCoord;
        envTexCoord.x = atan2(refv.x, refv.z) / (PI * 2);
        envTexCoord.y = acos(refv.y) / PI;
    
    //���}�b�s���O
        refColor = g_Texture.Sample(g_SamplerState, envTexCoord);
    }
    
    float3 refrColor;
    {
    //���܃x�N�g��
        float3 refrv = refract(eyev.xyz, normal, 1.0 / 1.5);
        refrv = normalize(refrv);
    
    //���}�b�s���O�e�N�X�`��(�p�m���})
        float2 envTexCoord;
        envTexCoord.x = atan2(refrv.x, refrv.z) / (PI * 2);
        envTexCoord.y = acos(refrv.y) / PI;
    
    //���}�b�s���O
        refrColor = g_Texture.Sample(g_SamplerState, envTexCoord);
    }
    
    //�t���l�����˗�
    float f0 = 0.04;
    float d = saturate(dot(-eyev, normal));
    float fresnel = f0 + (1.0 - f0) * pow((1.0 - d), 5.0);

    outDiffuse.rgb = lerp(refrColor, refColor, fresnel);
    outDiffuse.a = fresnel * 0.5f;
}

