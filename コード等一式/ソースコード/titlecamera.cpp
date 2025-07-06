#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "titlecamera.h"
#include "titleplayer.h"
#include "scene.h"

void TitleCamera::Init()
{
	m_position = XMFLOAT3(0.0f, 0.0f, 10.0f);
	m_target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_target2 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void TitleCamera::Uninit()
{
}

void TitleCamera::Update()
{
	Scene* scene = Manager::GetScene();//ポインターで宣言しているだけで中身が無いのでSceneの中を取得させる
	TitlePlayer* player = scene->GetGameObject<TitlePlayer>();
	XMFLOAT3 playerPosition = player->GetPosition();

	m_target.x = playerPosition.x + -1.0f;
	m_target.y = playerPosition.y + 10.0f;
	m_target.z = playerPosition.z;
}
void TitleCamera::Draw()
{
	XMFLOAT3 up{ 0.0f, 5.0f, 10.0f };
	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_position), XMLoadFloat3(&m_target), XMLoadFloat3(&up));//どこにおいてどこに向かせるか

	Renderer::SetViewMatrix(viewMatrix);

	XMStoreFloat4x4(&m_ViewMatrix,viewMatrix);

	//プロジェクションマトリクス設定
	XMMATRIX projectionmatrix;
	projectionmatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(projectionmatrix);
}
