#include "OBB.h"

// 内積を取る関数
inline float Dot(const XMFLOAT3& a, const XMFLOAT3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// ベクトルの差
inline XMFLOAT3 Subtract(const XMFLOAT3& a, const XMFLOAT3& b)
{
    return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
}

std::vector<XMFLOAT3> Obb::GetVertices() const
{
    std::vector<XMFLOAT3> vertices;

    // 各軸ベクトルをXMVECTORへ変換
    XMVECTOR cx = XMLoadFloat3(&axis[0]);
    XMVECTOR cy = XMLoadFloat3(&axis[1]);
    XMVECTOR cz = XMLoadFloat3(&axis[2]);

    cx = XMVectorScale(cx, halfSize[0]);
    cy = XMVectorScale(cy, halfSize[1]);
    cz = XMVectorScale(cz, halfSize[2]);

    // 中心座標
    XMVECTOR c = XMLoadFloat3(&center);

    // 頂点の組み合わせ（8頂点）
    const int signs[8][3] = {
        { -1, -1, -1 },
        {  1, -1, -1 },
        {  1,  1, -1 },
        { -1,  1, -1 },
        { -1, -1,  1 },
        {  1, -1,  1 },
        {  1,  1,  1 },
        { -1,  1,  1 }
    };

    for (int i = 0; i < 8; ++i)
    {
        XMVECTOR vertex =
            XMVectorMultiply(cx, XMVectorReplicate((float)signs[i][0])) +
            XMVectorMultiply(cy, XMVectorReplicate((float)signs[i][1])) +
            XMVectorMultiply(cz, XMVectorReplicate((float)signs[i][2])) + c;

        XMFLOAT3 out;
        XMStoreFloat3(&out, vertex);
        vertices.push_back(out);
    }

    return vertices;
}

bool Obb::CheckCollision(const Obb& other) const
{
    const float epsilon = 1e-5f;
    XMFLOAT3 T = Subtract(other.center, center);

    float R[3][3], AbsR[3][3];

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            R[i][j] = Dot(axis[i], other.axis[j]);
            AbsR[i][j] = fabs(R[i][j]) + epsilon;
        }
    }

    float ra, rb, t;

    for (int i = 0; i < 3; ++i)
    {
        ra = halfSize[i];
        rb = other.halfSize[0] * AbsR[i][0] +
            other.halfSize[1] * AbsR[i][1] +
            other.halfSize[2] * AbsR[i][2];

        t = fabs(Dot(T, axis[i]));
        if (t > ra + rb) return false;
    }

    for (int i = 0; i < 3; ++i)
    {
        ra = halfSize[0] * AbsR[0][i] +
            halfSize[1] * AbsR[1][i] +
            halfSize[2] * AbsR[2][i];

        rb = other.halfSize[i];
        t = fabs(Dot(T, other.axis[i]));
        if (t > ra + rb) return false;
    }

    return true;
}

