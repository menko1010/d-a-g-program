#pragma once
#include "gameobject.h"
#include "component.h"

class Box : public GameObject {
private:

	Component* m_Component{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	ID3D11ShaderResourceView* m_Texture{};
	ID3D11ShaderResourceView* m_Texture2{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};