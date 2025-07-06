#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "scene.h"

void Camera::Init()
{
	m_position = XMFLOAT3(0.0f, 5.0f, -10.0f);
	m_target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_target2 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void Camera::Uninit()
{
}

void Camera::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	Box* box = scene->GetGameObject<Box>();

	m_target = player->GetPosition();
	m_target.y += 7.0f; // ターゲットの高さ調整

	// 入力によるカメラの回転更新
	if (Input::GetKeyPress('J')) m_rotation.y -= 0.05f;
	if (Input::GetKeyPress('L')) m_rotation.y += 0.05f;

	// 角度のラップ処理 (0 ~ 2π)
	if (m_rotation.y < 0.0f) m_rotation.y += XM_2PI;
	if (m_rotation.y > XM_2PI) m_rotation.y -= XM_2PI;

	// 基本のカメラ距離
	XMFLOAT3 baseDistance;
	baseDistance.x = 15.0f;
	baseDistance.y = 15.0f;
	baseDistance.z = 15.0f;


	// プレイヤーとBoxの距離を計算
	XMFLOAT3 boxPos = box->GetPosition();
	XMFLOAT3 boxScale = box->GetScale();
	XMFLOAT3 playerPos = player->GetPosition();
	XMFLOAT3 adjustedDistance;

	float dx = playerPos.x - boxPos.x;
	float dy = playerPos.y - boxPos.y;
	float dz = playerPos.z - boxPos.z;

	float playerBoxDistance;
	playerBoxDistance = sqrtf(dx * dx + dy * dy + dz * dz);

	// Boxの半径（または許容距離）を設定（Boxの大きさに合わせて調整）
	const float boxRadius = 30.0f;

	// プレイヤーがBoxに近づいた場合、距離に応じてカメラ距離を縮める
	adjustedDistance = baseDistance;

	if (playerBoxDistance < boxScale.x * 550 + 5.0f && 
		playerBoxDistance < boxScale.z * 600 + 5.0f) // 5.0fは余裕の距離
	{
		// Boxに近づくほどカメラ距離を縮める（最大5m縮める）
		float shrinkAmountX = (boxRadius - playerBoxDistance);
		float shrinkAmountY = (boxRadius - playerBoxDistance);
		float shrinkAmountZ = (boxRadius - playerBoxDistance);
		if (shrinkAmountX > 5.0f && 
			shrinkAmountZ > 5.0f && 
			shrinkAmountY > 5.0f)
		{
			shrinkAmountX = 5.0f;
			shrinkAmountY = 5.0f;
			shrinkAmountZ = 5.0f;
		}

		adjustedDistance.x = baseDistance.x - shrinkAmountX;
		adjustedDistance.y = baseDistance.y - shrinkAmountY;
		adjustedDistance.z = baseDistance.z - shrinkAmountZ;
		if (adjustedDistance.x < 5.0f && 
			adjustedDistance.y < 5.0f && 
			adjustedDistance.z < 5.0f)
		{
			adjustedDistance.x = 5.0f; 
			adjustedDistance.y = 5.0f; 
			adjustedDistance.z = 5.0f; 
		}
	}

	// カメラの理想位置を計算（プレイヤーからの距離を調整済み）
	m_position.x = m_target.x + adjustedDistance.x * sinf(m_rotation.y);
	m_position.y = m_target.y + 2.0; // 高さは固定
	m_position.z = m_target.z + adjustedDistance.z * cosf(m_rotation.y);

	// Boxとカメラの衝突判定（単純な距離判定でOK）
	float dx_cam = m_position.x - boxPos.x;
	float dy_cam = m_position.y - boxPos.y;
	float dz_cam = m_position.z - boxPos.z;

	XMFLOAT3 camBoxDistance ;
	camBoxDistance.x = sqrtf(dx_cam * dx_cam);
	camBoxDistance.y = sqrtf(dy_cam * dy_cam);
	camBoxDistance.z = sqrtf(dz_cam * dz_cam);

	if (camBoxDistance.z < boxScale.z * 580)
	//if(camBoxDistance < boxRadius)
	{
		// カメラがBoxに入ってしまったら、カメラ位置をBoxの外に押し出す
		// カメラ位置をBox中心から外側に移動
		float overlap;
		overlap = boxRadius - camBoxDistance.z;

		// 正規化ベクトル
		float nx = dx_cam / camBoxDistance.x;
		float ny = dy_cam / camBoxDistance.y;
		float nz = dz_cam / camBoxDistance.z;

		m_position.x += nx * overlap;
		m_position.y += ny * overlap;
		m_position.z += nz * overlap;

	}
}


void Camera::Draw()
{
	XMFLOAT3 up{ 0.0f, 5.0f, 0.0f };
	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_position), XMLoadFloat3(&m_target), XMLoadFloat3(&up));//どこにおいてどこに向かせるか

	Renderer::SetViewMatrix(viewMatrix);

	
	XMStoreFloat4x4(&m_ViewMatrix,viewMatrix);

	//プロジェクションマトリクス設定
	XMMATRIX projectionmatrix;
	projectionmatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(projectionmatrix);

	////カメラウィンドウ
	//ImGui::Begin("Camera");

	//ImGui::InputFloat("Position", (float*)&m_position);
	//static float col1[3] = { 1.0f, 0.0f, 0.2f };
	//static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
	//ImGui::ColorEdit3("color 1", col1);

	//ImGui::End();
}


