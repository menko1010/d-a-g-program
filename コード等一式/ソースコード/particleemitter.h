#pragma once
//パーティクルの発射装置

#include "gameobject.h"

class ParticleEmitter : public GameObject {
private:

	ID3D11Buffer* m_VertexBuffur{};

	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	int m_Count{};

	struct PARTICLE
	{
		bool Enable = false;
		int Life;
		XMFLOAT3 Position;
		XMFLOAT3 Velocity;

	};
	static const int PARTICLE_MAX = 1000;
	PARTICLE m_Particle[PARTICLE_MAX]{};

public:
	void Init()override;
	void Uninit()override;
	void Update() override;
	void Draw() override;

};