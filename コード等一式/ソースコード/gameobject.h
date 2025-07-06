#pragma once

class GameObject {
protected:

	XMFLOAT3 m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_second_position = XMFLOAT3(100.0f, 0.0f, 0.0f);
	XMFLOAT3 m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	XMFLOAT3 m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_vector = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);

	bool m_destroy = false;

public:

	virtual ~GameObject(){}

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0; 

	XMFLOAT3 GetPosition() { return m_position; }
	XMFLOAT3 GetSecondPosition() { return m_second_position; }
	XMFLOAT3 GetScale() { return m_scale;}
	XMFLOAT3 GetRotation() { return m_rotation; }
	XMFLOAT3 GetVector() { return m_vector; }
	XMFLOAT3 GetVelocity() { return m_Velocity; }

	void SetPosition(XMFLOAT3 Position) { m_position = Position; }
	void SetScale(XMFLOAT3 Scale) { m_scale = Scale; }
	void SetRotation(XMFLOAT3 Rotation) { m_rotation = Rotation; }
	void SetVector(XMFLOAT3 Vector) { m_vector = Vector; }
	void SetVelocity(XMFLOAT3 Velocity) { m_Velocity = Velocity; }
	void Setdestroy() { m_destroy = true; }

	bool Destroy()
	{
		if (m_destroy) {
			Uninit();
			delete this;
			return true;
		}
		else {
			return false;

		}
	}

	XMFLOAT3 GetForward()
	{
		//オイラー角から回転行列を生成
		XMMATRIX rotationMatrix;
		rotationMatrix = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);

		XMFLOAT3 foward;
		XMStoreFloat3(&foward, rotationMatrix.r[2]);//rotationMatrixの３番めにz軸のベクトル情報がある
		return foward;
	}

	XMFLOAT3 GetRight() 
	{
		//オイラー角から回転行列を生成
		XMMATRIX rotationMatrix;
		rotationMatrix = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);

		XMFLOAT3 right;
		XMStoreFloat3(&right, rotationMatrix.r[0]);//rotationMatrixの３番めにz軸のベクトル情報がある
		return right;

	
	}

	XMFLOAT3 GetUp() 
	{
		//オイラー角から回転行列を生成
		XMMATRIX rotationMatrix;
		rotationMatrix = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);

		XMFLOAT3 up;
		XMStoreFloat3(&up, rotationMatrix.r[1]);//rotationMatrixの３番めにz軸のベクトル情報がある
		return up;

	
	}


};