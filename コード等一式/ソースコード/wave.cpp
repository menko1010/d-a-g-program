#include "main.h"
#include "renderer.h"
#include "wave.h"


void Wave::Init()
{
	for (int x = 0; x < 21; x++) {
		for (int z = 0; z < 21; z++) {
			m_vertex[x][z].Position = XMFLOAT3((x - 10) * 5.0f, 0.3f,
										(z - 10) * -5.0f);
			m_vertex[x][z].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			m_vertex[x][z].Diffuse = XMFLOAT4(1.0f, 1.0f, 0.5f, 1.0f);
			m_vertex[x][z].IntTexcoord = XMINT2(x, z);
		}
	}

	//�@���x�N�g���Z�o
	for (int x = 1; x < 20; x++)
	{
		for (int z = 1; z < 20; z++)
		{
			XMFLOAT3 vx, vz, vn;
			vx.x = m_vertex[x + 1][z].Position.x - m_vertex[x - 1][z].Position.x;
			vx.y = m_vertex[x + 1][z].Position.y - m_vertex[x - 1][z].Position.y;
			vx.z = m_vertex[x + 1][z].Position.z - m_vertex[x - 1][z].Position.z;

			vz.x = m_vertex[x][z - 1].Position.x - m_vertex[x][z + 1].Position.x;
			vz.y = m_vertex[x][z - 1].Position.y - m_vertex[x][z + 1].Position.y;
			vz.z = m_vertex[x][z - 1].Position.z - m_vertex[x][z + 1].Position.z;

			//�O��
			vn.x = vz.y * vx.z - vz.z * vx.y;
			vn.y = vz.z * vx.x - vz.x * vx.z;
			vn.z = vz.x * vx.y - vz.y * vx.x;

			//���K��(�������P�ɂ���)
			float len = sqrtf(vn.x * vn.x + vn.y * vn.y + vn.z * vn.z);
			vn.x /= len;
			vn.y /= len;
			vn.z /= len;

			m_vertex[x][z].Normal = vn;
		}
	}
	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 21 * 21;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = m_vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffur);

	//�C���f�b�N�X�o�b�t�@����
	{
		unsigned int index[((21 + 1) * 2) * 20 - 2];

		int i = 0;
		for (int x = 0; x < 20; x++)
		{
			for (int z = 0; z < 21; z++)
			{
				index[i] = x * 21 + z;
				i++;

				index[i] = (x + 1) * 21 + z;
				i++;
			}

			if (x == 19)
				break;

			index[i] = (x + 1) * 21 + 20;
			i++;
			index[i] = (x + 1) * 21;
			i++;
		}

		//���_�o�b�t�@����
		D3D11_BUFFER_DESC bd{};
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * ((22 * 2) * 20 - -2);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\waveVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\wavePS.cso");

	//�e�N�X�`���ǂݍ���
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\Texture\\water.jpg", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_EnvTexture);
	assert(m_EnvTexture);
}

void Wave::Uninit()
{
	m_VertexBuffur->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_EnvTexture->Release();

}

void Wave::Update()
{
	float dx, dz, length;
	float wavecycle = 10.0f;//����
	for (int x = 0; x < 21; x++) 
	{
		for (int z = 0; z < 21; z++) 
		{
			dx = m_vertex[x][z].Position.x - m_vertex[0][0].Position.x;
			dz = m_vertex[x][z].Position.z - m_vertex[0][0].Position.z;
			length = sqrtf(dx + dx + dz * dz + dx * dx + dz * dz);

			m_vertex[x][z].Position.y = m_amplitude *
				sinf(2.0f * XM_PI * (length / m_wavelength - m_wavetime / wavecycle));
		}
	}
	m_wavetime += 1.0f / 60.0f;

	//���_�f�[�^��������
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffur, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//�����Œ��_�f�[�^�̏�������
	memcpy(vertex, m_vertex, sizeof(VERTEX_3D) * 21 * 21);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffur, 0);
}

void Wave::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//���[���h�}�g���N�X�ݒ�
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	trans = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffur, &stride, &offset);

	//�C���f�b�N�X�o�b�t�@�ݒ�
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//�e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_EnvTexture);

	//�v���~�e�B�u�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	//Renderer::GetDeviceContext()->Draw(21 * 21, 0);
	Renderer::GetDeviceContext()->DrawIndexed((22 * 2) * 20 - 2, 0, 0);
}
