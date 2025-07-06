#include "main.h"
#include "renderer.h"
#include "input.h"
#include "stamina.h"
#include "scene.h"
#include "manager.h"
#include "audio.h"

void Stamina::Init()
{
	VERTEX_3D vertex[4 * 2];

	vertex[0].Position = XMFLOAT3(0.0f, 150.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(100.0f, 150.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f, 250.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(100.0f, 250.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//二枚目
	vertex[4].Position = XMFLOAT3(0.0f, 150.0f, 0.0f);
	vertex[4].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[4].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[4].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[5].Position = XMFLOAT3(100.0f, 150.0f, 0.0f);
	vertex[5].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[5].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[5].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[6].Position = XMFLOAT3(0.0f, 250.0f, 0.0f);
	vertex[6].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[6].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[6].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[7].Position = XMFLOAT3(100.0f, 250.0f, 0.0f);
	vertex[7].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[7].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[7].TexCoord = XMFLOAT2(1.0f, 1.0f);


	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;//デフォルトをダイナミックに変える
	bd.ByteWidth = sizeof(VERTEX_3D) * 4 * 2;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;//0からwhiteに変える
	//UsageとCPUを変える事で頂点座標変換をcontrolできる

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\Texture\\backHP.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_BackTexture);
	assert(m_BackTexture);

	LoadFromWICFile(L"asset\\Texture\\frontStamina.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_FrontTexture);
	assert(m_FrontTexture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	m_Count = 100;
	m_CurrentStamina = 100;
	m_minute = 0;
	m_time = 1;
	fade = 1.0f;
}

void Stamina::Uninit()
{

	m_VertexBuffer->Release();
	m_BackTexture->Release();
	m_FrontTexture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	
}

void Stamina::Update()
{

	if (m_CurrentStamina <= 100.0f)
	{
		m_CurrentStamina += 0.2f;
	}
	else
	{
		m_CurrentStamina = 100.0f;
	}
	if (m_CurrentStamina >= 0.0f)
	{
		if (m_CurrentStamina >= 1.0f)
		{

			if (Input::GetKeyPress('S') || Input::GetKeyPress('W') || Input::GetKeyPress('A') || Input::GetKeyPress('D'))
			{
				if (Input::GetKeyPress(VK_SHIFT))
				{
					m_CurrentStamina -= 0.5f;

				}

			}
			if (Input::GetKeyTrigger('C'))
			{
				m_CurrentStamina -= 10.0f;
			}
		}
	}
	else
	{
		m_CurrentStamina = 0.0f;
	}

}

void Stamina::Draw()
{
	float hpRatio = m_CurrentStamina / m_Count;

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = XMFLOAT3(95.0f /*+100.0f * (4 - 1 - i)*/, 60.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, fade);
	vertex[0].TexCoord = XMFLOAT2(0, 0);

	vertex[1].Position = XMFLOAT3(450.0f /*+ 100.0f * (4 - 1 - i)*/, 60.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, fade);
	vertex[1].TexCoord = XMFLOAT2(1, 0);

	vertex[2].Position = XMFLOAT3(95.0f /*+ 100.0f * (4 - 1 - i)*/, 80.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, fade);
	vertex[2].TexCoord = XMFLOAT2(0, 1);

	vertex[3].Position = XMFLOAT3(450.0f/* + 100.0f * (4 - 1 - i)*/, 80.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, fade);
	vertex[3].TexCoord = XMFLOAT2(1, 1);


	vertex[4].Position = XMFLOAT3(95.0f /*+100.0f * (4 - 1 - i)*/, 60.0f, 0.0f);
	vertex[4].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[4].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, fade);
	vertex[4].TexCoord = XMFLOAT2(0, 0);

	vertex[5].Position = XMFLOAT3(450.0f * hpRatio, 60.0f, 0.0f);
	vertex[5].Normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[5].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, fade);
	vertex[5].TexCoord = XMFLOAT2(1, 0);

	vertex[6].Position = XMFLOAT3(95.0f /*+ 100.0f * (4 - 1 - i)*/, 80.0f, 0.0f);
	vertex[6].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[6].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, fade);
	vertex[6].TexCoord = XMFLOAT2(0, 1);

	vertex[7].Position = XMFLOAT3(450.0f * hpRatio, 80.0f, 0.0f);
	vertex[7].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[7].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, fade);
	vertex[7].TexCoord = XMFLOAT2(1, 1);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, fade);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);


	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_BackTexture);


	//プリミティブポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポロゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_FrontTexture);

	//ポロゴン描画
	Renderer::GetDeviceContext()->Draw(4, 4);

}

