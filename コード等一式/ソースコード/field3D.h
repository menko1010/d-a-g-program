#pragma once
#include "gameobject.h"

class Field : public GameObject {
private:

	ID3D11Buffer* m_VertexBuffur{};

	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};



public:
	void Init()override;
	void Uninit()override;
	void Update() override;
	void Draw() override;

};