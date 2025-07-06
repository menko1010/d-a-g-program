#pragma once
#include "gameobject.h"

class Camera : public GameObject {
private:
	XMFLOAT3 m_target{};
	XMFLOAT3 m_target2{};
	XMFLOAT4X4 m_ViewMatrix{};
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	XMMATRIX GetViewMatrix()
	{
		//ベクトル計算などでシムドを使った方が一気に四つの変数計算ができる(使い方注意　newに対応していない)
		return XMLoadFloat4x4(&m_ViewMatrix);//型が違うので関数を嚙ませて変換し読み込みを楽にする
	}

};