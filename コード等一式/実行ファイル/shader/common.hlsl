
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
    float4 SkyColor; //�V���F
    float4 GroundColor; //�n�ʐF
    float4 GroundNormal; //�n�ʂ̖@��

    float4 Position; //���̈ʒu
    float4 PointLightParam; //x ���̓͂�����  y ���C�g�̌� z ������  w ���炩��

    matrix ViewMatrix; //���C�g�J�����p//	11/18
    matrix ProjectonMatrix; //���C�g�v���W�F�N�V�����p	11/18

};

cbuffer LightBuffer : register(b4)
{
	LIGHT Light;
}
cbuffer CameraBuffer : register(b5) // �R���X�^���g�o�b�t�@5�ԂŎ󂯎��
{
    float4 CameraPosition; // �J�����^�\���̂Ƃ��ė��p����(�J�����̍��W)
}

//�ėp�p�����[�^
cbuffer ParameterBuffer : register(b6)
{
    float4 Parameter; //C���ꂩ�牽���󂯎��
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
    float4 WorldPosition : POSITION0; //�s�N�Z���̋�Ԃł̍��W
    float4 Normal : NORMAL0; //�s�N�Z���̖@��
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
    float4 LightPosition : POSITION1; //���C�g��ԍ��W//11/18	
};
