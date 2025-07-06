#pragma once

#include <DirectXMath.h>
#include <vector>

using namespace DirectX;

class Obb
{
public:
    XMFLOAT3 center;       // ���S���W
    XMFLOAT3 axis[3];      // �e���iX, Y, Z�j
    float halfSize[3];     // �e�������̔��T�C�Y
    std::vector<XMFLOAT3> GetVertices() const;

    void PlayerSet(const XMFLOAT3& pos, const XMFLOAT3 axes[3], const XMFLOAT3& scale)
    {
        center = pos;
        axis[0] = axes[0];
        axis[1] = axes[1];
        axis[2] = axes[2];
        halfSize[0] = scale.x* 20.0f;
        halfSize[1] = scale.y* 170.0f;
        halfSize[2] = scale.z* 20.0f;
    }

    void RyuuSet(const XMFLOAT3& pos, const XMFLOAT3 axes[3], const XMFLOAT3& scale)
    {
        center = pos;
        axis[0] = axes[0];
        axis[1] = axes[1];
        axis[2] = axes[2];
        halfSize[0] = scale.x * 10.0f;
        halfSize[1] = scale.y * 20.0f;
        halfSize[2] = scale.z * 20.0f;
    }

    bool CheckCollision(const Obb& other) const;
};
