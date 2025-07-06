#pragma once
#include <cstddef>
#include "gameobject.h"

class Score : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffur = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	int m_Count;
	int m_minute;
	int m_time;
	float fade;

	class Audio* m_SE{};

	static const int SCORE_MAX = 4;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void AddCount(int Count) { m_Count += Count; }
};