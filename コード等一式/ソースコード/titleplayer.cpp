#include "main.h"
#include "renderer.h"
#include "audio.h"
#include "manager.h"
#include "titleplayer.h"
#include "modelRenderer.h"
#include"animationModel.h"
#include "input.h"
#include "scene.h"
#include "box.h"
#include "result.h"
#include "meshField.h"
#include "stamina.h"
#include <windows.h>
#include "titlecamera.h"
void TitlePlayer::Init()
{
	m_Component = new AnimationModel(this);
	((AnimationModel*)m_Component)->Load("asset\\model\\lance.fbx");

	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\lancetitle.fbx", "Idle");
	m_AnimationName1 = "Idle";
	m_AnimationName2 = "Idle";

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\UnlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, 
		"shader\\UnlitTexturePS.cso");
}

void TitlePlayer::Uninit()
{
	m_Component->Uninit();
	delete m_Component;

	 m_VertexShader->Release();
	m_PixelShader->Release();
	 m_VertexLayout->Release();
}

void TitlePlayer::Update()
{
}
void TitlePlayer::Draw()
{
	((AnimationModel*)m_Component)->Update(m_AnimationName1.c_str(), m_AnimationFrame, m_AnimationName2.c_str(), m_AnimationFrame, m_AnimationBlendRatio);
	m_AnimationFrame++;

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	XMMATRIX world, scale, rot, trans;
	float vector;

	scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y + XM_PI, m_rotation.z);
	trans = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_Component->Draw();
}
