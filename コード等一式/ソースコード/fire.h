#pragma once
#include <cstddef>
#include "gameobject.h"

class Fire : public GameObject
{
private:

	ID3D11Buffer* m_VertexBuffur = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	float m_Count;
	float m_minute;
	float m_time;
	float fade;
	//struct digit {
	//	XMFLOAT2 Position;

	class Audio* m_SE{};
	VERTEX_3D vertex[4];

	//};
	static const int SCORE_MAX = 4;
	//digit m_score[SCORE_MAX]{};//åÖêî
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void AddCount(int Count) { m_Count += Count; }
};