#pragma once
#include "gameobject.h"

class Tree : public GameObject 
{
private:
	ID3D11Buffer* m_VertexBuffur{};

	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	int m_Count{};

public:
	void Init()override;
	void Uninit()override;
	void Update() override;
	void Draw() override;
	XMFLOAT3 treePosition = m_position;
};