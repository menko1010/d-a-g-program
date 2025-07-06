#pragma once

#include <DirectXMath.h>
#include <vector>

using namespace DirectX;

class Obb
{
public:
    XMFLOAT3 center;       // 中心座標
    XMFLOAT3 axis[3];      // 各軸（X, Y, Z）
    float halfSize[3];     // 各軸方向の半サイズ
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
