#pragma once
#include "gameobject.h"
#include "component.h"
#include <string>


class PlayerShadow : public GameObject {
private:
	static Component* m_Component;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	std::string	m_AnimationName1{};
	std::string	m_AnimationName2{};
	float		m_AnimationBlendRatio{};
	int			m_AnimationFrame{};

public:
	static void Load();
	static void Unload();
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};