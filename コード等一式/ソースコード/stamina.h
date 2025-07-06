#pragma once
#include <cstddef>
#include "gameobject.h"
#include "player.h"

class Stamina : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_BackTexture = NULL;
	ID3D11ShaderResourceView* m_FrontTexture = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	int m_Count;
	int m_minute;
	int m_time;
	float fade = 1.0f;

public:
	float m_CurrentStamina;

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void AddCount(int Count) { m_Count += Count; }
};