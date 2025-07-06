#include"common.hlsl"

Texture2D	g_Texture : register(t0);	//�e�N�X�`��0��
SamplerState g_SamplerState : register(s0);	//�T���v���[0��

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{

    //�e�N�X�`���̐F���擾
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);

    //���l�̏���
        outDiffuse = In.Diffuse;
    
//�s�N�Z���̖@���𐳋K��
        float4 normal = normalize(In.Normal);

//�����v�Z(�n�[�u�����o�[�g)
        float light = 5.5f + -dot(normal.xyz, Light.GroundColor.xyz) * 0.5f;
    
    
//�����v�Z�̌��ʂ���Z����
        outDiffuse.rgb *= In.Diffuse.rgb * light;

//���̔��˃x�N�g��
        float3 refv = reflect(Light.Direction.xyz, normal.xyz);
        refv = normalize(refv);
//�X�y�L�����[�v�Z
        float specular = refv;
        specular = saturate(specular);
        specular = pow(specular, 30); //�X�y�L�����[�̒���

//�X�y�L�����[���f�B�t���[�Y�ɉ��Z����
        outDiffuse.rgb += specular;
    
    outDiffuse.a = Material.Diffuse.a;
}