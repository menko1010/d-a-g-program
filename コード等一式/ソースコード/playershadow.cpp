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
	//メッシュフィールド高さ取得
	MeshField* meshField =
		Manager::GetScene()->GetGameObject<MeshField>();

	//地面の高さ
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
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	trans = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	//colorバッファマスク有効
	Renderer::SetBlendMaskEnable(true);

	//ステンシル書き込み有効
	Renderer::SetStencilEnable(true);

	//カリング無効
	Renderer::SetCullEnable(false);

	m_Component->Draw();
	
	//colorバッファマスク無効
	Renderer::SetBlendMaskEnable(false);

	//ステンシル書き込み無効
	Renderer::SetDepthEnable(false);

	//カリング有効
	Renderer::SetCullEnable(true);

}
