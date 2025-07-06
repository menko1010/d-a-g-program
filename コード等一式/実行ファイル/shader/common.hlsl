
cbuffer WorldBuffer : register(b0)
{
	matrix World;
}
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}

struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float Shininess;
	bool TextureEnable;
	float2 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}

struct LIGHT
{
	bool Enable;
	bool3 Dummy;
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;
    float4 SkyColor; //天球色
    float4 GroundColor; //地面色
    float4 GroundNormal; //地面の法線

    float4 Position; //光の位置
    float4 PointLightParam; //x 光の届く距離  y ライトの個数 z 金属感  w 滑らかさ

    matrix ViewMatrix; //ライトカメラ用//	11/18
    matrix ProjectonMatrix; //ライトプロジェクション用	11/18

};

cbuffer LightBuffer : register(b4)
{
	LIGHT Light;
}
cbuffer CameraBuffer : register(b5) // コンスタントバッファ5番で受け取る
{
    float4 CameraPosition; // カメラ型構造体として利用する(カメラの座標)
}

//汎用パラメータ
cbuffer ParameterBuffer : register(b6)
{
    float4 Parameter; //C言語から何か受け取る
}

struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
};

struct PS_IN
{
	float4 Position		: SV_POSITION;
    float4 WorldPosition : POSITION0; //ピクセルの空間での座標
    float4 Normal : NORMAL0; //ピクセルの法線
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
    float4 LightPosition : POSITION1; //ライト空間座標//11/18	
};
