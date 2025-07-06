#include "main.h"
#include "renderer.h"
#include "titleparticle.h"
#include "titlecamera.h"
#include "scene.h"
#include "manager.h"

void TitleParticle::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 25.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0, 0);

	vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 25.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1, 0);

	vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 25.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0, 1);

	vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 25.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1, 1);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffur);

	//テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\Texture\\particle.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

}

void TitleParticle::Uninit()
{
	m_VertexBuffur->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void TitleParticle::Update()
{

	//パーティクル発射
	for (int i = 0; i < PARTICLE_MAX; i++) {
		if (m_Particle[i].Enable == false){
			m_Particle[i].Enable = true;
			m_Particle[i].Life = 25;
			m_Particle[i].Position.x = m_position.x + (rand() % 50-25) / 6;
			m_Particle[i].Position.y = m_position.y;

			m_Particle[i].Velocity.x = 0.09f;
			m_Particle[i].Velocity.y = (rand() % 5-3) / 500.0f;
			m_Particle[i].Velocity.z = 0;

			break;
		}
	}
	//パーティクル移動
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_Particle[i].Enable == true)
		{
			m_Particle[i].Velocity.y += 0.03f;

			//移動
			if (m_position.x < m_Particle[i].Position.x)
			{
				m_Particle[i].Position.x -= m_Particle[i].Velocity.x;

			}
			else
			{
				m_Particle[i].Position.x += m_Particle[i].Velocity.x;
			}
			m_Particle[i].Position.y += m_Particle[i].Velocity.y;
			m_Particle[i].Position.z += m_Particle[i].Velocity.z;//dtを使ってやった方がフレームレート更新が安定する

			//ライフ
			m_Particle[i].Life--;
			if (m_Particle[i].Life == 0)
			{
				m_Particle[i].Enable = false;
			}
		}
	}
}

void TitleParticle::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//カメラのビューマトリクス取得
	Scene* scene = Manager::GetScene();
	TitleCamera* camera = scene->GetGameObject<TitleCamera>();
	XMMATRIX view = camera->GetViewMatrix();//カメラにどのように見えるか

	//ビューの逆行列(カメラの向きがわかる)
	XMMATRIX inView;
	inView = XMMatrixInverse(nullptr, view);
	inView.r[3].m128_f32[0] = 0.0f;
	inView.r[3].m128_f32[1] = 0.0f;
	inView.r[3].m128_f32[2] = 0.0f;

	

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffur, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 0.1f, 0.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//Zバッファ無効
	Renderer::SetDepthEnable(false);

	//加算合成有効
	Renderer::SetBlendAddEnable(true);

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_Particle[i].Enable == true)
		{
			//ワールドマトリクス設定
			XMMATRIX world, scale, rot, trans;
			scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
			trans = XMMatrixTranslation(m_Particle[i].Position.x, m_Particle[i].Position.y, m_Particle[i].Position.z);
			world = scale * inView * trans;//rotをinViewに変えてカメラに合わせて板ポリが回転する(ビルボード)
			Renderer::SetWorldMatrix(world);

			//ポロゴン描画
			Renderer::GetDeviceContext()->Draw(4, 0);
		}
	}
	//Zバッファ無効
	Renderer::SetDepthEnable(true);
	//加算合成有効
	Renderer::SetBlendAddEnable(false);

}
