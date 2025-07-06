#include "main.h"
#include "renderer.h"
#include "box.h"
#include "modelRenderer.h"

void Box::Init()
{
	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\castle.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\DisneyPBRVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\DisneyPBRPS.cso");

	//テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\Texture\\field000.jpg", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);

}

void Box::Uninit()
{
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexLayout->Release();
}

void Box::Update()
{
}

void Box::Draw()
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

	//トゥーン用テクスチャの設定（テクスチャ１番へセット）
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_Texture);

	m_Component->Draw();
}

