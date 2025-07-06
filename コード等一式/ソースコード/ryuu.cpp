#include "main.h"
#include "renderer.h"
#include "ryuu.h"
#include "modelRenderer.h"
#include "scene.h"
#include "player.h"
#include "manager.h"
#include "meshField.h"

void Ryuu::Attak0()
{
	if (m_Ryuu_pattern == 0)
	{
		if (m_attackminite >= 1.5f)
		{
			m_RyuuUse = true;
			m_attacktime = 0;
			m_Ryuu_pattern = 0;
		}
	}

}
void Ryuu::Attak1()
{
	Scene* object = Manager::GetScene();
	Player* player = object->GetGameObject<Player>();
	Obb* playerOBB = player->playerobb;

	bool playerInvincible = player->m_invincible;
	bool playerUse = player->m_playerUse;

	if (m_Ryuu_pattern == 1 && m_attackminite >= 1.0f)
	{
		if (playerInvincible)
		{
			if (m_attackminite >= 1.5f)
			{
				m_position.y += 0.15f;
			}
			if (ryuuobb->CheckCollision(*playerOBB))
			{
				if (m_attackminite == 3.0f)
				{
					if (playerUse)
					{
						m_attack = 20.0f;
					}
					else
						m_attack = 0.0f;
				}
				else
					m_attack = 0.0;
			}
		}
		if (m_attackminite >= 3.3f)
		{
			m_RyuuUse = true;
			m_attacktime = 0;
			m_Ryuu_pattern = 0;
		}
	}

}
void Ryuu::Attak2()
{
	Scene* object = Manager::GetScene();
	Player* player = object->GetGameObject<Player>();
	Obb* playerOBB = player->playerobb;

	bool playerInvincible = player->m_invincible;
	bool playerUse = player->m_playerUse;

	if (m_Ryuu_pattern == 2 && m_attackminite >= 1.0f)
	{
		m_rotation.y += 0.2f;
		if (playerInvincible)
		{
			if (ryuuobb->CheckCollision(*playerOBB))
			{
				if (m_attackminite == 1.0f)
				{
					if (playerUse)
					{
						m_attack = 20.0f;
					}
					else
						m_attack = 0.0f;
				}
				else
					m_attack = 0.0;
			}
		}
		if (m_attackminite >= 1.5f)
		{
			m_RyuuUse = true;
			m_attacktime = 0;
			m_Ryuu_pattern = 0;
		}
	}

}
void Ryuu::Base()
{
	float dt = 1.0f / 60.0f;

	//�d��
	m_Velocity.y += -10.0f * dt;
	m_position.y += m_Velocity.y * dt;

	//���b�V���t�B�[���h�����擾
	MeshField* meshField =
		Manager::GetScene()->GetGameObject<MeshField>();

	//�n�ʂ̍���
	float groundHeight = meshField->GetHeight(m_position);

	XMFLOAT3 axes[3] = { GetRight(), GetUp(), GetForward() };
	ryuuobb->RyuuSet(m_position, axes, m_scale);

	//�n�ʂƂ̏Փ�
	if (m_position.y < groundHeight + 3.0f)
	{
		m_position.y = groundHeight + 3.0f;
		m_Velocity.y = 0.0f;
	}
}
void Ryuu::Movement()
{
	Scene* object = Manager::GetScene();
	Player* player = object->GetGameObject<Player>();
	Obb* playerOBB = player->playerobb;

	XMFLOAT3 playerPosition = player->GetPosition();
	XMFLOAT3 playerScale = player->GetScale();

	//�ȈՈړ�
	if (m_position.x < playerPosition.x)
	{
		m_position.x = m_position.x + 0.1f;
	}
	else if (playerPosition.x < m_position.x)
	{
		m_position.x = m_position.x - 0.1f;
	}
	if (m_position.z < playerPosition.z)
	{
		m_position.z = m_position.z + 0.1f;
	}
	else if (playerPosition.z < m_position.z)
	{
		m_position.z = m_position.z - 0.1f;
	}

	XMFLOAT3 direction;
	direction.x = playerPosition.x - m_position.x;
	direction.y = playerPosition.y - m_position.y;
	direction.z = playerPosition.z - m_position.z;//����

	XMFLOAT3 axisX = player->GetRight();
	XMFLOAT3 dotX;//���όv�Z
	dotX.x = direction.x * axisX.x + direction.y * axisX.y + direction.z * axisX.z;

	//Y������
	XMFLOAT3 axisY = player->GetUp();
	XMFLOAT3 dotY;
	dotY.y = direction.x * axisX.x + direction.y * axisX.y + direction.z * axisX.z;//���όv�Z

	//Z������
	XMFLOAT3 axisZ = player->GetForward();
	XMFLOAT3 dotZ;//���όv�Z
	dotZ.z = direction.x * axisX.x + direction.y * axisX.y + direction.z * axisX.z;

	m_NormaDirect[0] = dotX;
	m_NormaDirect[1] = dotY;
	m_NormaDirect[2] = dotZ;

	length[0] = sqrtf(direction.x * direction.x);//�O������direction�̒��������߂�
	length[1] = sqrtf(direction.y * direction.y);//�O������direction�̒��������߂�
	length[2] = sqrtf(direction.z * direction.z);//�O������direction�̒��������߂�

	//��]
	m_vector.x = direction.x;
	m_vector.z = direction.z;

	m_rotation.y = atan2(m_vector.x, m_vector.z);

	if (ryuuobb->CheckCollision(*playerOBB))
	{
		m_Ryuu_pattern = (rand() % 3 - 0);
		m_RyuuUse = false;
	}

}

void Ryuu::Init()
{
	m_Component = new ModelRenderer();
	((ModelRenderer*)m_Component)->Load("asset\\model\\ryuu_Idle.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\limLightingVS2.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\limLightingPS2.cso");

	ryuuobb = new Obb();
}

void Ryuu::Uninit()
{
	delete m_Component;

	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexLayout->Release();
}

void Ryuu::Update()
{
	Base();
	//�G�̍s���p�^�[��
	if (m_RyuuUse)
	{
		Movement();
	}
	else
	{
		m_attacktime++;
		m_attackminite = m_attacktime / 60;
		Attak0();
		Attak1();
		Attak2();

	}
	if (m_RyuuLife == 0)
	{
		Setdestroy();
	}
}

void Ryuu::Draw()
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

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//�v���~�e�B�u�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	m_Component->Draw();
	if (ryuuobb)
	{
		std::vector<XMFLOAT3> vertices = ryuuobb->GetVertices();
		Renderer::DrawLineBox(vertices, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)); // �ԐF
	}

}

void Ryuu::LifeDown()
{
	m_RyuuLife--;
}
