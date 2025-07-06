#pragma once
#include "gameobject.h"
#include "component.h"
#include "modelRenderer.h"
#include "OBB.h"

class Ryuu : public GameObject 
{
private:
	ID3D11Buffer* m_VertexBuffur{};
	Component* m_Component;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	MODEL_OBJ m_ModelObj[2];
	float m_time = 0;
	float m_minite = 0;
	float m_usetime = 0;
	float m_useminite = 0;
	float m_attacktime = 0;
	float m_attackminite = 0;
	float m_alpha = 1.0f;
	float m_RyuuLife = 5;
	float length[3];

	int   m_Ryuu_pattern = 0;
	bool  m_RyuuUse = true;
	XMFLOAT3 m_NormaDirect[3]; // 方向ベクトル（正規化）

public:
	float m_attack;
	class Obb* ryuuobb;

	void Base();
	void Movement();
	void Attak0();
	void Attak1();
	void Attak2();
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void LifeDown();
	
	Obb* GetRyuuObb() { return ryuuobb; }
};