#pragma once
#include "common.hlsl"

Texture2D g_Tecture : register(t0); // 0番テクスチャの情報

SamplerState g_SamplerState : register(s0); // サンプラー0番

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    outDiffuse = In.Diffuse; // 頂点の色を出力
    
    // ピクセルの法線を正規化
    float4 normal = normalize(In.Normal);
    // 光源計算
    float light = 0.5f - 0.5f * dot(normal.xyz, Light.Direction.xyz); // ハーフランバート

    //light <= 明るさの調整（段階分け）
    //light >= 0.7f --> 1.0f;
    //light >= 0.5f --> 0.8f;
    //それ以外なら --> 0.4f;
    if(light >= 0.7f){
        light = 1.0f;
    }
    else if(light >= 0.5f){
        light = 0.8f;
    }
    else{
        light = 0.4f;
    }

    // テクスチャのピクセルの色を取得
    outDiffuse = g_Tecture.Sample(g_SamplerState, In.TexCoord);

    outDiffuse.rgb *= In.Diffuse.rgb * light;   // 明るさを乗算
    outDiffuse.a *= In.Diffuse.a;               // α値に明るさは関係ない
}