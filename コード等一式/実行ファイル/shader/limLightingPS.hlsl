#include"common.hlsl"

Texture2D	g_Texture : register(t0);	//テクスチャ0番
SamplerState g_SamplerState : register(s0);	//サンプラー0番

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //テクスチャの色を取得
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);

    //α値の処理
        outDiffuse *= In.Diffuse;
    
//ピクセルの法線を正規化
        float4 normal = normalize(In.Normal);

//光源計算(ハーブランバート)
        float light = 0.5f - dot(normal.xyz, Light.Position.xyz) + 0.5f;
    
    
//光源計算の結果を乗算する
        outDiffuse.rg *= In.Diffuse.rg * light;

//光の反射ベクトル
        float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    refv = normalize(refv);
    
//スペキュラー計算
    float specular = refv;
    specular = saturate(specular);
    specular = pow(specular, 10); //スペキュラーの調整

//スペキュラーをディフューズに加算する
    outDiffuse.rgb += specular;
    

}