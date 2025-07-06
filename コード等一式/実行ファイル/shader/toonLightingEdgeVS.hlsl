#pragma once
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{
    // 頂点の変換
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    
    //モデルの拡張処理
    float4 pos = In.Position;
    float4 norm = normalize(In.Normal) * 0.02f;
    norm.w = 0.0f;
    pos += norm;
    Out.Position = mul(pos, wvp);

    // 頂点法線をワールド行列で変換(頂点と同じ回転をかける)
    float4 worldNormal, normal;
    normal = float4(In.Normal.xyz, 0.0f);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);
    Out.Normal = worldNormal;

    Out.Diffuse.rgb = 0.0f;
    Out.Diffuse.a = 1.0f;    
    Out.TexCoord = In.TexCoord; // テクスチャ座標を出力
   
    // ワールド変換した頂点座標を出力
    Out.WorldPosition = mul(pos, World);
}