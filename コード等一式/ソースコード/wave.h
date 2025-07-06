#pragma once
#include "gameobject.h"

class Wave : public GameObject 
{
private:
	ID3D11Buffer* m_VertexBuffur{};
	ID3D11Buffer* m_IndexBuffer{};

	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	ID3D11ShaderResourceView* m_EnvTexture;

	VERTEX_3D m_vertex[21][21];

	float m_amplitude = 1.0f;//�ӂ蕝
	float m_wavelength = 5.0f;
	float m_wavetime{};

public:
	void Init()override;
	void Uninit()override;
	void Update() override;
	void Draw() override;
	float GetHeight(XMFLOAT3 Position);
};

