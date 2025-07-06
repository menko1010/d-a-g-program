#include"common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
//���_���W�ϊ�
matrix wvp;
wvp = mul(World, View); //wvp = world * view
wvp = mul(wvp, Projection); //wvp = wvp * Projection
//�����܂Ő��VS�V�F�[�_�[�ɕK�v

//���_�@�������[���h�s��ŉ�]������i���f���Ɠ�����]���s���j
float4 worldNormal, normal;
normal = float4(In.Normal.xyz, 0.0f); //�@���x�N�g����w��0�Ƃ��Ă���
worldNormal = mul(normal,World);	//�R�s�[�����@������]������
worldNormal = normalize(worldNormal);	//��]�������@���𐳋K��
Out.Normal = worldNormal;	//�o��

//���_�̃f�t���[�Y���o��
Out.Diffuse = In.Diffuse * Material.Diffuse;
    Out.Diffuse += In.Diffuse * Material.Ambient;
    Out.Diffuse += Material.Emission;
    Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;
//���[���h�ϊ��������_���W���o��
Out.Position = mul(In.Position, wvp);
    //�e�N�X�`�����W���o��
    Out.TexCoord = In.TexCoord;

}