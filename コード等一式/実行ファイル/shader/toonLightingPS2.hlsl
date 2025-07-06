#pragma once
#include "common.hlsl"

Texture2D g_Texture : register(t0); // 0�ԃe�N�X�`���̏��
Texture2D g_TextureToon : register(t1);//1�ԃe�N�X�`��//�e�N�X�`�����Ŗ��邳���������Ă���
Texture2D g_TextureToon2 : register(t2);

SamplerState g_SamplerState : register(s0); // �T���v���[0��
SamplerState g_SamplerStateToon : register(s1); // �T���v���[1��

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // �s�N�Z���̖@���𐳋K��
    float4 normal = normalize(In.Normal);
    // �����v�Z
    float light = 2.5f  - dot(normal.xyz, Light.Direction.xyz); // �n�[�t�����o�[�g

    //light <= ���邳�̒����i�i�K�����j
    //���邳�̒l���N�����v����
    float toon = clamp(light, 0.1f, 2.0f); //�K���ɃN�����v
    float3 uv;
    float4 Prameter = (1.0f, 0.0f, 0.0f, 0.0f);

    uv.x = toon; //�N�����v�����l
    uv.y = 0.1f; //v�͂Ƃ肠����0.5�ŌŒ�
    uv += Prameter;

    //�ʏ�̃e�N�X�`���擾
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.gb *= g_TextureToon.Sample(g_SamplerState, uv).gb;
    
    //���_�F
    outDiffuse.r *= In.Diffuse.r;

    //���l
    outDiffuse.a = In.Diffuse.a;
}