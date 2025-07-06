#include"common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
//���_���W�ϊ�
matrix wvp;
wvp = mul(World, View); //wvp = world * view
wvp = mul(wvp, Projection); //wvp = wvp * Projection
Out.Position = mul(In.Position, wvp); // �ϊ����ʂ��o��
//�����܂Ő��VS�V�F�[�_�[�ɕK�v

//���_�@�������[���h�s��ŉ�]������i���f���Ɠ�����]���s���j
float4 worldNormal, normal;
normal = float4(In.Normal.xyz, 0.0f); //�@���x�N�g����w��0�Ƃ��Ă���
worldNormal = mul(normal,World);	//�R�s�[�����@������]������
worldNormal = normalize(worldNormal);	//��]�������@���𐳋K��
Out.Normal = worldNormal;	//�o��

//���_�̃f�t���[�Y���o��
Out.Diffuse = In.Diffuse;
//�e�N�X�`�����W���o��
Out.TexCoord = In.TexCoord;
//���[���h�ϊ��������_���W���o��
Out.WorldPosition = mul(In.Position, World);

}