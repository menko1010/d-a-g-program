#pragma once
#include <cstddef>
#include "gameobject.h"

class FadeTexture : public GameObject
{
private:

	ID3D11Buffer* m_VertexBuffur = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	VERTEX_3D vertex[4]{};
	float m_fade = 1.0f;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};