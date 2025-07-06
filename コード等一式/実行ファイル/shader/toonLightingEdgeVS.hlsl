#pragma once
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{
    // ���_�̕ϊ�
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    
    //���f���̊g������
    float4 pos = In.Position;
    float4 norm = normalize(In.Normal) * 0.02f;
    norm.w = 0.0f;
    pos += norm;
    Out.Position = mul(pos, wvp);

    // ���_�@�������[���h�s��ŕϊ�(���_�Ɠ�����]��������)
    float4 worldNormal, normal;
    normal = float4(In.Normal.xyz, 0.0f);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);
    Out.Normal = worldNormal;

    Out.Diffuse.rgb = 0.0f;
    Out.Diffuse.a = 1.0f;    
    Out.TexCoord = In.TexCoord; // �e�N�X�`�����W���o��
   
    // ���[���h�ϊ��������_���W���o��
    Out.WorldPosition = mul(pos, World);
}