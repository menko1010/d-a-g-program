#pragma once
#include <cstddef>
#include "gameobject.h"

class Loadrogo : public GameObject
{
private:

	ID3D11Buffer* m_VertexBuffur = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
	float m_fade = 1.0f;
	int m_minute = 0;
	int m_time = 0;

	VERTEX_3D vertex[4];
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};