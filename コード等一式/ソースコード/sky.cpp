#include "main.h"
#include "renderer.h"
#include "sky.h"
#include "modelRenderer.h"

void Sky::Init()
{
	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\sky.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\skyVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\skyPS.cso");

	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void Sky::Uninit()
{
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexLayout->Release();

}

void Sky::Update()
{
}

void Sky::Draw()
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

	m_Component->Draw();

}
