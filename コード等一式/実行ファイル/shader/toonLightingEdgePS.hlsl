#pragma once
#include "common.hlsl"

Texture2D g_Tecture : register(t0); // 0�ԃe�N�X�`���̏��

SamplerState g_SamplerState : register(s0); // �T���v���[0��

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    outDiffuse = In.Diffuse; // ���_�̐F���o��
    
    // �s�N�Z���̖@���𐳋K��
    float4 normal = normalize(In.Normal);
    // �����v�Z
    float light = 0.5f - 0.5f * dot(normal.xyz, Light.Direction.xyz); // �n�[�t�����o�[�g

    //light <= ���邳�̒����i�i�K�����j
    //light >= 0.7f --> 1.0f;
    //light >= 0.5f --> 0.8f;
    //����ȊO�Ȃ� --> 0.4f;
    if(light >= 0.7f){
        light = 1.0f;
    }
    else if(light >= 0.5f){
        light = 0.8f;
    }
    else{
        light = 0.4f;
    }

    // �e�N�X�`���̃s�N�Z���̐F���擾
    outDiffuse = g_Tecture.Sample(g_SamplerState, In.TexCoord);

    outDiffuse.rgb *= In.Diffuse.rgb * light;   // ���邳����Z
    outDiffuse.a *= In.Diffuse.a;               // ���l�ɖ��邳�͊֌W�Ȃ�
}