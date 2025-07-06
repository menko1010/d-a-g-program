#include "main.h"
#include "renderer.h"
#include "playershadow.h"
#include "modelRenderer.h"
#include "animationModel.h"
#include "scene.h"
#include "manager.h"
#include "meshField.h"

Component* PlayerShadow::m_Component{};

void PlayerShadow::Load()
{
}
void PlayerShadow::Unload()
{
}

void PlayerShadow::Init()
{
	m_Component = new ModelRenderer();
	((ModelRenderer*)m_Component)->Load("asset\\model\\bullet.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

	m_scale = XMFLOAT3(50.0f, 50.0f, 50.0f);
}

void PlayerShadow::Uninit()
{
	m_Component->Uninit();
	delete m_Component;

	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexLayout->Release();

}

void PlayerShadow::Update()
{
	//���b�V���t�B�[���h�����擾
	MeshField* meshField =
		Manager::GetScene()->GetGameObject<MeshField>();

	//�n�ʂ̍���
	float groundHeight = meshField->GetHeight(m_position);

	Scene* object = Manager::GetScene();
	Player* player = object->GetGameObject<Player>();
	m_position = player->GetPosition();
	m_position.y = player->GetPosition().y - 0.1f;
	if (m_position.y < groundHeight)
	{
		m_position.y = groundHeight - 0.1f;
		m_Velocity.y = 0.0f;
	}
}

void PlayerShadow::Draw()
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

	//color�o�b�t�@�}�X�N�L��
	Renderer::SetBlendMaskEnable(true);

	//�X�e���V���������ݗL��
	Renderer::SetStencilEnable(true);

	//�J�����O����
	Renderer::SetCullEnable(false);

	m_Component->Draw();
	
	//color�o�b�t�@�}�X�N����
	Renderer::SetBlendMaskEnable(false);

	//�X�e���V���������ݖ���
	Renderer::SetDepthEnable(false);

	//�J�����O�L��
	Renderer::SetCullEnable(true);

}
