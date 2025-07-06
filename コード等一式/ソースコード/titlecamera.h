#pragma once
#include "gameobject.h"

class TitleCamera : public GameObject 
{
private:
	XMFLOAT3 m_target{};
	XMFLOAT3 m_target2{};
	XMFLOAT4X4 m_ViewMatrix{};
	bool m_cameracontrol = false;

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	XMMATRIX GetViewMatrix()
	{
		return XMLoadFloat4x4(&m_ViewMatrix);
	}

};