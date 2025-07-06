#pragma once
#include "common.hlsl"

Texture2D g_Texture : register(t0); // 0番テクスチャの情報
Texture2D g_TextureToon : register(t1);//1番テクスチャ//テクスチャ側で明るさ情報を持っておく
Texture2D g_TextureToon2 : register(t2);

SamplerState g_SamplerState : register(s0); // サンプラー0番
SamplerState g_SamplerStateToon : register(s1); // サンプラー1番

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // ピクセルの法線を正規化
    float4 normal = normalize(In.Normal);
    // 光源計算
    float light = 2.5f  - dot(normal.xyz, Light.Direction.xyz); // ハーフランバート

    //light <= 明るさの調整（段階分け）
    //明るさの値をクランプする
    float toon = clamp(light, 0.1f, 2.0f); //適当にクランプ
    float3 uv;
    float4 Prameter = (1.0f, 0.0f, 0.0f, 0.0f);

    uv.x = toon; //クランプした値
    uv.y = 0.1f; //vはとりあえず0.5で固定
    uv += Prameter;

    //通常のテクスチャ取得
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.gb *= g_TextureToon.Sample(g_SamplerState, uv).gb;
    
    //頂点色
    outDiffuse.r *= In.Diffuse.r;

    //α値
    outDiffuse.a = In.Diffuse.a;
}