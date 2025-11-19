#include "CapsuleCollider.h"
#include "ColliderType.h"
#include <variant>
#include "DxLib.h"

// コンストラクタ
CapsuleCollider::CapsuleCollider(Transform transform, float height, float radius, ColliderManager* manager)
    : Collider([transform, height, radius]() {
    CapsuleType c;

    // --- Transformの回転を考慮して上下方向を計算 ---
    VECTOR rot = transform.GetRot();  // ← 回転（ラジアン）
    // 各軸の回転行列を生成
    MATRIX rotX = MGetRotX(rot.x);
    MATRIX rotY = MGetRotY(rot.y);
    MATRIX rotZ = MGetRotZ(rot.z);

    // 回転行列を合成（X→Y→Z の順）
    MATRIX rotMat = MMult(MMult(rotX, rotY), rotZ);

    // Y軸方向を回転
    VECTOR upLocal = VGet(0, 1, 0);
    VECTOR upDir = VTransform(upLocal, rotMat);  // 法線方向の回転と同等

    VECTOR center = transform.GetPos();
    float halfHeight = height * 0.5f;

    // 上下端を決定
    c.posTop = VAdd(center, VScale(upDir, halfHeight));
    c.posBottom = VAdd(center, VScale(upDir, -halfHeight));
    c.height = height;
    c.radius = radius;

    return c;
        }(),
            manager,
            transform)
{
    SetOBB(); // AABB設定
}

// デストラクタ
CapsuleCollider::~CapsuleCollider()
{}

// コピコン
CapsuleCollider::CapsuleCollider(const CapsuleCollider& other)
    : Collider(
        [other]() {
            CapsuleType c;

            // --- Transformの回転を考慮して上下方向を再計算 ---
            Transform transform = other.m_transform;  // ← Transformを取得
            float height = other.GetCapsule()->height;
            float radius = other.GetCapsule()->radius;

            VECTOR rot = transform.GetRot();  // 回転（ラジアン）
            MATRIX rotX = MGetRotX(rot.x);
            MATRIX rotY = MGetRotY(rot.y);
            MATRIX rotZ = MGetRotZ(rot.z);
            MATRIX rotMat = MMult(MMult(rotX, rotY), rotZ);

            VECTOR upLocal = VGet(0, 1, 0);
            VECTOR upDir = VTransform(upLocal, rotMat);

            VECTOR center = transform.GetPos();
            float halfHeight = height * 0.5f;

            c.posTop    = VAdd(center, VScale(upDir,  halfHeight));
            c.posBottom = VAdd(center, VScale(upDir, -halfHeight));
            c.height = height;
            c.radius = radius;

            return c;
        }(),
        other.m_manager,
        other.m_transform // Transformのコピー
            )
{
    SetOBB(); // コピー後にAABBを再設定

#ifdef _DEBUG
    MessageBoxW(
        nullptr,
        L"CapsuleCollider コピーコンストラクタが呼ばれました。",
        L"通知",
        MB_OK | MB_ICONINFORMATION
    );
#endif
}

// Update
void CapsuleCollider::Update()
{
    SetTrans();
    SetOBB();
}

// Transform基準のコライダーサイズ設定
void CapsuleCollider::SetTrans()
{
    // Transform をワールド行列まで更新
    m_transform.LocalToWorld();

    // CapsuleType を Transform に基づいて更新
    CapsuleType& cap = std::get<CapsuleType>(m_data);

    VECTOR center = m_transform.GetPos();
    VECTOR rot = m_transform.GetRot(); // ラジアン
    VECTOR scale = m_transform.GetScale();

    // 回転行列
    MATRIX rotX = MGetRotX(rot.x);
    MATRIX rotY = MGetRotY(rot.y);
    MATRIX rotZ = MGetRotZ(rot.z);
    MATRIX rotMat = MMult(MMult(rotX, rotY), rotZ);

    // Y軸方向を Transform に沿わせる
    VECTOR upDir = VTransform(VGet(0, 1, 0), rotMat);

    // スケールを反映した半高さ
    float halfHeight = (cap.height * scale.y) * 0.5f;

    cap.posTop = VAdd(center, VScale(upDir, halfHeight));
    cap.posBottom = VAdd(center, VScale(upDir, -halfHeight));
}

void CapsuleCollider::SetOBB()
{
    const CapsuleType& cap = std::get<CapsuleType>(m_data);

    VECTOR line = VSub(cap.posTop, cap.posBottom);
    float halfLen = 0.5f * VSize(line);

    // 半径分を足して全体の長さに
    halfLen += cap.radius;

    VECTOR center = VScale(VAdd(cap.posTop, cap.posBottom), 0.5f);

    // 長さ方向
    VECTOR dir = VNorm(line);

    // 任意の垂直ベクトルを作る
    VECTOR up = VGet(0, 1, 0);
    if (fabs(VDot(dir, up)) > 0.999f) up = VGet(1, 0, 0); // 並行なら切り替え

    VECTOR right = VNorm(VCross(up, dir));
    VECTOR forward = VCross(dir, right);

    // OBB に保存
    obb.center = center;
    obb.axes[0] = dir;       obb.halfLen[0] = halfLen;
    obb.axes[1] = right;     obb.halfLen[1] = cap.radius;
    obb.axes[2] = forward;   obb.halfLen[2] = cap.radius;
}

// コライダーの可視化
void CapsuleCollider::DrawCollider() const
{
    const CapsuleType& cap = std::get<CapsuleType>(m_data);

    DrawCapsule3D(cap.posTop, cap.posBottom, cap.radius, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), TRUE);
}