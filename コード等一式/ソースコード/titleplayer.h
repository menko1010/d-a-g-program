#pragma once
#include "gameobject.h"
#include "component.h"
#include <string>

class TitlePlayer : public GameObject 
{
private:
	Component* m_Component{};
	Component* m_ChildModel{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	XMFLOAT3 m_secondPosition{};
	XMFLOAT3 m_thirdPosition{};

	XMFLOAT3 m_Velocity{};
	XMFLOAT3 m_acsel{};

	XMFLOAT4 m_Quaternion{};

	std::string	m_AnimationName1{};
	std::string	m_AnimationName2{};
	float		m_AnimationBlendRatio{};
	int			m_AnimationFrame{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};