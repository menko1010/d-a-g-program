#include "main.h"
#include "renderer.h"
#include "audio.h"
#include "manager.h"
#include "player.h"
#include "ryuu.h"
#include "modelRenderer.h"
#include "animationModel.h"
#include "hp.h"
#include "input.h"
#include "scene.h"
#include "box.h"
#include "result.h"
#include "meshField.h"
#include "stamina.h"
#include "OBB.h"
#include <windows.h>

Component* Player::m_Component{};

void Player::Load()
{
	m_Component = new AnimationModel();
	((AnimationModel*)m_Component)->Load("asset\\model\\lance.fbx");

	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\lanceRunning.fbx", "Run");
	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\lanceIdle.fbx", "Idle");
	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\lanceSlash.fbx", "Attack");
	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\rowling.fbx", "rowling");
	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\down2.fbx", "down");

}

void Player::Velocity()
{
	Scene* object = Manager::GetScene();
	Camera* camera = object->GetGameObject<Camera>();
	Stamina* stamina = object->GetGameObject<Stamina>();
	Hp* hp = object->GetGameObject<Hp>();
	XMFLOAT3 Crotation = camera->GetRotation();
	XMFLOAT3 foward = camera->GetForward();
	XMFLOAT3 right = camera->GetRight();
	bool checkHp = hp->m_downHP;
	float staminanow = stamina->m_CurrentStamina;
	float dt = 1.0f / 60.0f;
	float hpnow = hp->m_CurrentHP;

	//加速
	if (Input::GetKeyPress('S'))
	{
		m_Velocity.x += foward.x * 10.0f * dt;
		m_Velocity.y += foward.y * 10.0f * dt;
		m_Velocity.z += foward.z * 10.0f * dt;

		m_vector.z = -1.5f;
		m_vector.x = 0.0f;

		m_AnimationName1 = m_AnimationName2;
		m_AnimationName2 = "Run";
		m_AnimationBlendRatio = 0.0f;

		if (staminanow >= 1.0f)
		{
			if (Input::GetKeyPress(VK_SHIFT))
			{
				m_Velocity.x += foward.x * 20.0f * dt;
				m_Velocity.z += foward.z * 20.0f * dt;
			}
		}
	}
	if (Input::GetKeyPress('W'))
	{
		m_Velocity.x -= foward.x * 10.0f * dt;
		m_Velocity.y -= foward.y * 10.0f * dt;
		m_Velocity.z -= foward.z * 10.0f * dt;

		m_vector.z = 1.5f;
		m_vector.x = 0.0f;

		m_AnimationName1 = m_AnimationName2;
		m_AnimationName2 = "Run";
		m_AnimationBlendRatio = 0.0f;

		if (staminanow >= 1.0f)
		{
			if (Input::GetKeyPress(VK_SHIFT))
			{
				m_Velocity.x -= foward.x * 20.0f * dt;
				m_Velocity.z -= foward.z * 20.0f * dt;
			}
		}
	}
	if (Input::GetKeyPress('A'))
	{
		m_Velocity.x += right.x * 10.0f * dt;
		m_Velocity.y += right.y * 10.0f * dt;
		m_Velocity.z += right.z * 10.0f * dt;
		m_vector.x = -1.5f;
		m_vector.z = 0.0f;

		m_AnimationName1 = m_AnimationName2;
		m_AnimationName2 = "Run";
		m_AnimationBlendRatio = 0.0f;

		if (staminanow >= 1.0f)
		{
			if (Input::GetKeyPress(VK_SHIFT))
			{
				m_Velocity.x += right.x * 20.0f * dt;
				m_Velocity.z += right.z * 20.0f * dt;
			}
		}
	}
	if (Input::GetKeyPress('D'))
	{
		m_Velocity.x -= right.x * 10.0f * dt;
		m_Velocity.y -= right.y * 10.0f * dt;
		m_Velocity.z -= right.z * 10.0f * dt;
		m_vector.x = 1.5f;
		m_vector.z = 0.0f;
		m_AnimationName1 = m_AnimationName2;
		m_AnimationName2 = "Run";
		m_AnimationBlendRatio = 0.0f;

		if (staminanow >= 1.0f)
		{
			if (Input::GetKeyPress(VK_SHIFT))
			{
				m_Velocity.x -= right.x * 20.0f * dt;
				m_Velocity.z -= right.z * 20.0f * dt;
			}
		}
	}
	if (Input::GetKeyPress('W') && Input::GetKeyPress('D'))
	{
		m_vector.z = 1.0f;
		m_vector.x = 1.0f;
	}
	if (Input::GetKeyPress('W') && Input::GetKeyPress('A'))
	{
		m_vector.z = 1.0f;
		m_vector.x = -1.0f;
	}
	if (Input::GetKeyPress('S') && Input::GetKeyPress('D'))
	{
		m_vector.z = -1.0f;
		m_vector.x = 1.0f;
	}
	if (Input::GetKeyPress('S') && Input::GetKeyPress('A'))
	{
		m_vector.z = -1.0f;
		m_vector.x = -1.0f;
	}
	if (Input::GetKeyPress('C'))
	{
		m_rowling = false;
		m_invincible = false;
		m_AnimationFrame = 0;//アニメーションフレームを初期化することでアニメーションをきれいに再生する
		m_AnimationName1 = m_AnimationName2;
		m_AnimationName2 = "rowling";
		m_AnimationBlendRatio = 0.5f;
	}
	if (checkHp)//HP減少したか
	{
		m_playerUse = false;
		m_AnimationFrame = 0;//アニメーションフレームを初期化することでアニメーションをきれいに再生する
		m_AnimationName1 = m_AnimationName2;
		m_AnimationName2 = "down";
		m_AnimationBlendRatio = 0.5f;
	}
	else
	{
		if (m_AnimationName2 != "Idle")
		{
			m_AnimationName1 = m_AnimationName2;
			m_AnimationName2 = "Idle";
			m_AnimationBlendRatio = 0.0f;
		}
	}

	if (hpnow <= 0)
	{
		Setdestroy();
	}

	//重力加速度
	m_Velocity.y += -10.0f * dt;

	//移動
	m_position.x += m_Velocity.x * dt;
	m_position.y += m_Velocity.y * dt;
	m_position.z += m_Velocity.z * dt;

	//摩擦
	m_Velocity.x -= m_Velocity.x * 2.0f * dt;
	m_Velocity.z -= m_Velocity.z * 2.0f * dt;

	//方向
	m_rotation.y = (Crotation.y + atan2f(m_vector.x, m_vector.z));

}

void Player::Ryuucollision()
{
	Scene* object = Manager::GetScene();

	//敵との当たり判定
	std::vector<Ryuu*>ryuuList = object->GetGameObjects<Ryuu>();

	for (Ryuu* ryuu : ryuuList)
	{
		XMFLOAT3 ryuuPosition = ryuu->GetPosition();
		XMFLOAT3 ryuuScale = ryuu->GetScale();

		XMFLOAT3 direction;
		direction.x = ryuuPosition.x - m_position.x;
		direction.y = ryuuPosition.y - m_position.y;
		direction.z = ryuuPosition.z - m_position.z;//距離

		length[0] = sqrtf(direction.x * direction.x);//三平方でdirectionの長さを求める
		length[1] = sqrtf(direction.y * direction.y);//三平方でdirectionの長さを求める
		length[2] = sqrtf(direction.z * direction.z);//三平方でdirectionの長さを求める

		if (Input::GetKeyTrigger('K'))//trigerにする
		{
			m_Attack = false;
			m_AnimationFrame = 0;//アニメーションフレームを初期化することでアニメーションをきれいに再生する
			m_AnimationName1 = m_AnimationName2;
			m_AnimationName2 = "Attack";
			m_AnimationBlendRatio = 0.5f;

			if (length[0] < ryuuScale.x + 15.0f ||
				length[1] < ryuuScale.z + 15.0)
			{
				m_SE->Play();
				ryuu->LifeDown();
			}
		}
		else
		{
			if (m_AnimationName2 != "Idle")
			{
				m_AnimationName1 = m_AnimationName2;
				m_AnimationName2 = "Idle";
				m_AnimationBlendRatio = 0.0f;
			}
		}
	}
}

void Player::Base()
{
	Scene* object = Manager::GetScene();
	Box* box = object->GetGameObject<Box>();
	XMFLOAT3 oldPosition = m_position;

	m_AnimationBlendRatio += 0.1f;
	if (m_AnimationBlendRatio > 1.0f)
	{
		m_AnimationBlendRatio = 1.0f;
	}

	//メッシュフィールド高さ取得
	MeshField* meshField =
		Manager::GetScene()->GetGameObject<MeshField>();

	//地面の高さ
	float groundHeight = meshField->GetHeight(m_position);


	//地面との衝突
	if (m_position.y < groundHeight)
	{
		m_position.y = groundHeight;
		m_Velocity.y = 0.0f;
	}

	//result
	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Manager::SetScene<Result>();
	}

	//城当たり判定
	XMFLOAT3 boxposition = box->GetPosition();
	XMFLOAT3 boxScale = box->GetScale();

	XMFLOAT3 boxdirection;
	boxdirection.x = boxposition.x - m_position.x;
	boxdirection.y = boxposition.y - m_position.y;
	boxdirection.z = boxposition.z - m_position.z;//距離

	length[0] = sqrtf(boxdirection.x * boxdirection.x);//三平方でdirectionの長さを求める
	length[1] = sqrtf(boxdirection.z * boxdirection.z);

}
void Player::Init()
{
	m_AnimationName1 = "Idle";
	m_AnimationName2 = "Idle";

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\DisneyPBRVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, 
		"shader\\DisneyPBRPS.cso");

	m_SE = new Audio(this);
	m_SE->Load("asset\\BGM\\attack.wav");

	playerobb = new Obb();
}

void Player::Uninit()
{
	m_SE->Uninit();
	delete m_SE;

	m_Component->Uninit();
	delete m_Component;

	 m_VertexShader->Release();
	m_PixelShader->Release();
	 m_VertexLayout->Release();
}

void Player::Update()
{
	Scene* object = Manager::GetScene();

	Camera* camera = object->GetGameObject<Camera>();
	Obb* obbpoint = object->GetGameObject<Obb>();
	Box* box = object->GetGameObject<Box>();
	XMFLOAT3 oldPosition = m_position;
	XMFLOAT3 boxScale = box->GetScale();
	XMFLOAT3 axes[3] = { GetRight(), GetUp(), GetForward() };
	playerobb->PlayerSet(m_position, axes, m_scale);

	m_tire = 0.0f;
	if (m_playerUse)
	{
		if (m_Attack)
		{
			if (m_rowling)
			{
				Velocity();
				Ryuucollision();
				Base();
			}
			else{
				m_time++;
				m_minite = m_time / 60;
				if (m_minite >= 0.3f){
					m_invincible = true;
				}
				if (m_minite >= 0.5f){
					m_rowling = true;
					m_time = 0.0f;
				}
			}
		}
		else{
			m_time++;
			m_minite = m_time / 60;
			if (m_minite >= 1.3f){
				m_Attack = true;
				m_time = 0.0f;
			}
		}
	}
	else{
		m_time++;
		m_minite = m_time / 60;
		if (m_minite >= 1.0f){
			m_playerUse = true;
			m_time = 0.0f;
		}
	}
	if (length[0] < boxScale.x * 550 &&
		length[1] < boxScale.z * 650)
	{
		m_position = oldPosition;
	}

}

void Player::Draw()
{
	// player.cpp 内の ImGui 描画処理
	static int currentShaderIndex = 0;
	const char* shaderOptions[] = { "limLight", "toonLight", "DisneyPBR", "stealth"};

	ImGui::Text("PlayerUse : %s", m_playerUse ? "true" : "false");

	ImGui::Text("Shader Select:");
	if (ImGui::Combo("Shader", &currentShaderIndex, shaderOptions, IM_ARRAYSIZE(shaderOptions))) {
		switch (currentShaderIndex) {
		case 0: // limLight シェーダー
			Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
				"shader\\limLightingVS.cso");
			Renderer::CreatePixelShader(&m_PixelShader,
				"shader\\limLightingPS.cso");
			break;

		case 1: // toonLight シェーダー
			Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
				"shader\\toonLightingVS2.cso");
			Renderer::CreatePixelShader(&m_PixelShader,
				"shader\\toonLightingPS2.cso");
			break;

		case 2: // DisneyPBR シェーダー
			Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
				"shader\\DisneyPBRVS.cso");
			Renderer::CreatePixelShader(&m_PixelShader,
				"shader\\DisneyPBRPS.cso");
			break;

		case 3: // DisneyPBR シェーダー
			Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
				"shader\\stealthVS.cso");
			Renderer::CreatePixelShader(&m_PixelShader,
				"shader\\stealthPS.cso");
			break;
		}
	}
	ImGui::Text("Position");
	ImGui::InputFloat3("PlayerPosition.x", &m_position.x);
	ImGui::InputFloat3("PlayerScale", &m_scale.x);

	const char* animNames[] = { "Idle", "Run", "Attack", "rowling", "down" };
	int animCount = sizeof(animNames) / sizeof(animNames[0]);
	int currentIndex = -1;
	for (int i = 0; i < animCount; ++i) {
		if (m_AnimationName1 == animNames[i]) {
			currentIndex = i;
			break;
		}
	}
	if (currentIndex != -1) {
		ImGui::Text("Current Animation: %s", animNames[currentIndex]);
	}
	else {
		ImGui::Text("Current Animation: Unknown (%s)", m_AnimationName1.c_str());
	}

	((AnimationModel*)m_Component)->Update(m_AnimationName1.c_str(), m_AnimationFrame, m_AnimationName2.c_str(), m_AnimationFrame, m_AnimationBlendRatio);
	m_AnimationFrame++;

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//ワールドマトリクス設定	rot = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y + XM_PI, m_rotation.z);
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y + XM_PI, m_rotation.z);
	//rot = XMMatrixRotationQuaternion(XMLoadFloat4(&m_Quaternion));//四次元用のマトリクス
	trans = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//Renderer::SetCullEnable(D3D11_CULL_BACK);
		//ステンシル無効
	Renderer::SetDepthEnable(true);

	m_Component->Draw();
	if (playerobb)
	{
		std::vector<XMFLOAT3> vertices = playerobb->GetVertices();
		Renderer::DrawLineBox(vertices, XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)); // 緑色
	}
}



