#pragma once
#include <cstddef>
#include "gameobject.h"

class Hp : public GameObject
{
private:

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_BackTexture = NULL;
	ID3D11ShaderResourceView* m_BarTexture = NULL;
	ID3D11ShaderResourceView* m_FrontTexture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	float m_Count{};
	float m_minute{};
	float m_time{};
	float m_minite{};

	float fade = 1.0f;
	float m_oldCurrentHP{};
	float m_CurrentHalfHP{};
	static const int SCORE_MAX = 4;

public:
	bool m_downHP{};
	float m_CurrentHP{};

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void AddCount(int Count) { m_Count += Count; }
};