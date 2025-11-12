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
    SetAABB(); // AABB設定
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
            Transform transform = other.GetTrans();  // ← Transformを取得
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
        other.GetTrans() // Transformのコピー
            )
{
    SetAABB(); // コピー後にAABBを再設定

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

}

// Transform基準のコライダーサイズ設定
void CapsuleCollider::SetTrans()
{

}

void CapsuleCollider::SetAABB()
{
    const CapsuleType& cap = std::get<CapsuleType>(m_data);

    // 中心線ベクトル
    VECTOR line = VSub(cap.posTop, cap.posBottom);
    float halfLen = 0.5f * VSize(line);
    VECTOR center = VScale(VAdd(cap.posTop, cap.posBottom), 0.5f);

    // カプセルの回転行列を計算（中心線の向きに沿うZ軸回転などを作る）
    // 今回は簡易化して、中心線を単純な回転とみなす
    VECTOR dir = VNorm(line);

    // 3軸方向ベクトル（dir軸を中心に考える）
    VECTOR axes[3] = {
        VGet(1,0,0),  // X
        VGet(0,1,0),  // Y
        VGet(0,0,1)   // Z
    };

    VECTOR worldMin = VGet(FLT_MAX, FLT_MAX, FLT_MAX);
    VECTOR worldMax = VGet(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    // カプセルを長方体で包むイメージでAABB計算
    for (int i = 0; i < 3; i++) {
        VECTOR axis = axes[i];
        // 回転ベクトルも考慮（capsule自体がTransform回転している場合）
        // ここでは posTop/posBottom は既に回転済みなので、半径分を各方向に加える
        float r = cap.radius;
        worldMin.x = fmin(worldMin.x, center.x - r);
        worldMin.y = fmin(worldMin.y, center.y - r);
        worldMin.z = fmin(worldMin.z, center.z - r);

        worldMax.x = fmax(worldMax.x, center.x + r);
        worldMax.y = fmax(worldMax.y, center.y + r);
        worldMax.z = fmax(worldMax.z, center.z + r);
    }

    // カプセルの長さ方向も加味
    worldMin.x = fmin(worldMin.x, cap.posTop.x);
    worldMin.y = fmin(worldMin.y, cap.posTop.y);
    worldMin.z = fmin(worldMin.z, cap.posTop.z);

    worldMin.x = fmin(worldMin.x, cap.posBottom.x);
    worldMin.y = fmin(worldMin.y, cap.posBottom.y);
    worldMin.z = fmin(worldMin.z, cap.posBottom.z);

    worldMax.x = fmax(worldMax.x, cap.posTop.x);
    worldMax.y = fmax(worldMax.y, cap.posTop.y);
    worldMax.z = fmax(worldMax.z, cap.posTop.z);

    worldMax.x = fmax(worldMax.x, cap.posBottom.x);
    worldMax.y = fmax(worldMax.y, cap.posBottom.y);
    worldMax.z = fmax(worldMax.z, cap.posBottom.z);

    aabb.min = worldMin;
    aabb.max = worldMax;
}
