#include "main.h"
#include "renderer.h"
#include "titleryuu.h"
#include "modelRenderer.h"

void TitleRyuu::Init()
{
	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\ryuu_Idle.obj");

	ModelRenderer::LoadObj("asset\\model\\ryuu_Idle.obj", &m_ModelObj[0]);//頂点データ変化用
	ModelRenderer::LoadObj("asset\\model\\ryuu_Idle2.obj", &m_ModelObj[1]);//モデル読み込み

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");
}

void TitleRyuu::Uninit()
{
	delete m_ModelObj[0].IndexArray;
	delete m_ModelObj[0].VertexArray;
	delete m_ModelObj[0].SubsetArray;

	delete m_ModelObj[1].IndexArray;
	delete m_ModelObj[1].VertexArray;
	delete m_ModelObj[1].SubsetArray;

	delete m_Component;

	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexLayout->Release();
}

void TitleRyuu::Update()
{
	ID3D11Buffer* vertexBuffer = ((ModelRenderer*)m_Component)->GetVerTexBuffer();

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	m_time += 1.0f/ 60.0f;
	float blend = sinf(m_time * 2.0f) * 0.5f + 0.5f;

	for (int i = 0; i < m_ModelObj[0].VertexNum; i++)
	{
		vertex[i] = m_ModelObj[0].VertexArray[i];

		//線形補間
		vertex[i].Position.x = m_ModelObj[0].VertexArray[i].Position.x * (1.0f - blend)
			+ m_ModelObj[1].VertexArray[i].Position.x * blend;

		vertex[i].Position.y = m_ModelObj[0].VertexArray[i].Position.y * (1.0f - blend)
			+ m_ModelObj[1].VertexArray[i].Position.y * blend;

		vertex[i].Position.z = m_ModelObj[0].VertexArray[i].Position.z * (1.0f - blend)
			+ m_ModelObj[1].VertexArray[i].Position.z * blend;
	}

	if (m_time <= 1.5f)
	{
		for (int timecount = 0; timecount < 2; timecount++)
		{
			m_position.y += 0.005f;
		}
	}
	if (m_time >= 1.5f)
	{
		for (int timecount = 0; timecount < 2; timecount++)
		{
			m_position.y -= 0.005f;
		}
	}
	if (m_time >= 3.1f)
	{
		m_time = 0.0f;
	}
	Renderer::GetDeviceContext()->Unmap(vertexBuffer, 0);
}

void TitleRyuu::Draw()
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

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffur, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//プリミティブポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_Component->Draw();
}
