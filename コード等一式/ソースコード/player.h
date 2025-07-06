#pragma once
#include "gameobject.h"
#include "component.h"
#include <string>
#include "OBB.h"

class Player : public GameObject {
private:
	static Component* m_Component;
	Component* m_ChildModel{};


	XMFLOAT3 m_secondPosition{};
	XMFLOAT3 m_thirdPosition{};

	ID3D11ShaderResourceView* m_Texture{};
	ID3D11ShaderResourceView* m_Texture2{};

	XMFLOAT3 m_Velocity{};
	XMFLOAT3 m_acsel{};

	XMFLOAT4 m_Quaternion{};

	std::string	m_AnimationName1{};
	std::string	m_AnimationName2{};
	float		m_AnimationBlendRatio{};
	int			m_AnimationFrame{};

	float m_time{};
	float m_minite{};

	bool m_Attack;

	float m_stamina = 100.0f;

	class Audio* m_SE{};
public:
	float m_tire{};
	XMFLOAT3 m_boxlength{};
	bool m_playerUse;
	bool m_rowling;
	bool m_invincible;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float length[3];
	class Obb* playerobb;

	static void Load();
	void Velocity();
	void Ryuucollision();
	void Base();
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};