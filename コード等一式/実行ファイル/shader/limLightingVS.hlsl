#include"common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
//頂点座標変換
matrix wvp;
wvp = mul(World, View); //wvp = world * view
wvp = mul(wvp, Projection); //wvp = wvp * Projection
Out.Position = mul(In.Position, wvp); // 変換結果を出力
//ここまで絶対VSシェーダーに必要

//頂点法線をワールド行列で回転させる（モデルと同じ回転を行う）
float4 worldNormal, normal;
normal = float4(In.Normal.xyz, 0.0f); //法線ベクトルのwを0としておく
worldNormal = mul(normal,World);	//コピーした法線を回転させる
worldNormal = normalize(worldNormal);	//回転させた法線を正規化
Out.Normal = worldNormal;	//出力

//頂点のデフューズを出力
Out.Diffuse = In.Diffuse;
//テクスチャ座標を出力
Out.TexCoord = In.TexCoord;
//ワールド変換した頂点座標を出力
Out.WorldPosition = mul(In.Position, World);

}