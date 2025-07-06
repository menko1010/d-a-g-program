#pragma once
#include "gameobject.h"
#include "component.h"
#include "modelRenderer.h"

class TitleRyuu : public GameObject 
{
private:
	ID3D11Buffer* m_VertexBuffur{};
	Component* m_Component{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	MODEL_OBJ m_ModelObj[2];

	float m_time = 0.0f;
	float m_movetime = 0.0f;

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};