#include "ColliderManager.h"
#include "DxLib.h"
#include "cmath"
#include <algorithm>

ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
}

void ColliderManager::Update()
{
}

// コライダーの追加
void ColliderManager::AddCollider(Collider* collider)
{
    m_allColliders.emplace_back(collider);
}

// コライダーの削除
void ColliderManager::DeleteCollider(Collider* collider)
{
    std::erase_if(m_allColliders, [&](const auto& elem) { return elem == collider; });
}

void ColliderManager::HitJudgment()
{

}

// レイヤー/マスク判定
void ColliderManager::LayerAndMaskPhase()
{
    m_layerMaskPairs.clear(); // 前フレームの判定結果をクリア

    // すべてのコライダーをビット演算で判定
    for (size_t i = 0; i < m_allColliders.size(); ++i) {
        for (size_t j = i + 1; j < m_allColliders.size(); ++j) {
            Collider* a = m_allColliders[i];
            Collider* b = m_allColliders[j];

            // Layer と Mask のビット演算で通過判定
            if (Any(a->GetLayer() & b->GetCollisionMask()) &&
                Any(b->GetLayer() & a->GetCollisionMask()))
            {
                m_layerMaskPairs.emplace_back(a, b);
            }
        }
    }
}

// 簡易的な当たり判定
void ColliderManager::BroadPhase()
{
    m_broadPhasePairs.clear();

    LayerAndMaskPhase();

#ifdef _DEBUG
    DrawFormatString(0, 150, GetColor(255, 255, 255), "colliderSize = %d", (int)m_layerMaskPairs.size());
#endif // _DEBUG

    for (auto& pair : m_layerMaskPairs)
    {
        Collider* a = pair.first;
        Collider* b = pair.second;

        // OBB を取得
        OBB aOBB = *a->GetOBB();
        OBB bOBB = *b->GetOBB();

        if (HitCheckOBBToOBB(aOBB, bOBB))
        {
            // AABB が重なっていれば NarrowPhase へ
            m_broadPhasePairs.emplace_back(a, b);
        }
    }
}

// 当たり判定の実装
void ColliderManager::NarrowPhase()
{
    m_collisionPairs.clear();

    for (auto& pair : m_broadPhasePairs)
    {
        Collider* colA = pair.first;
        Collider* colB = pair.second;

        ColliderType typeA = colA->GetType();
        ColliderType typeB = colB->GetType();

        // 判定順を固定（小さい方が先）
        if (typeA > typeB)
        {
            std::swap(typeA, typeB);
            std::swap(colA, colB);
        }

        bool isHit = false;

        // 形状ごとの判定
        if (typeA == ColliderType::Box && typeB == ColliderType::Box)
        {
            const OBB* a = colA->GetOBB();   // ← OBB 取得
            const OBB* b = colB->GetOBB();   // ← OBB 取得
            if (a && b) isHit = HitCheckOBBToOBB(*a, *b);
        }
        else if (typeA == ColliderType::Box && typeB == ColliderType::Capsule)
        {
            const OBB* a = colA->GetOBB();
            const CapsuleType* b = colB->GetCapsule();
            if (a && b) isHit = HitCheckBoxToCapsule(*a, *b);
        }
        else if (typeA == ColliderType::Box && typeB == ColliderType::Sphere)
        {
            const OBB* a = colA->GetOBB();
            const SphereType* b = colB->GetSphere();
            if (a && b) isHit = HitCheckBoxToSphere(*a, *b);
        }
        else if (typeA == ColliderType::Capsule && typeB == ColliderType::Capsule)
        {
            const CapsuleType* a = colA->GetCapsule();
            const CapsuleType* b = colB->GetCapsule();
            if (a && b) isHit = HitCheckCapsuleToCapsule(*a, *b);
        }
        else if (typeA == ColliderType::Sphere && typeB == ColliderType::Capsule)
        {
            const SphereType* a = colA->GetSphere();
            const CapsuleType* b = colB->GetCapsule();
            if (a && b) isHit = HitCheckSphereToCapsule(*a, *b);
        }
        else if (typeA == ColliderType::Sphere && typeB == ColliderType::Sphere)
        {
            const SphereType* a = colA->GetSphere();
            const SphereType* b = colB->GetSphere();
            if (a && b) isHit = HitCheckSphereToSphere(*a, *b);
        }

        // 衝突していればフラグと衝突リストに追加
        if (isHit)
        {

            // colA->AddCurrentHitCollider(colB);
            // colB->AddCurrentHitCollider(colA);

            m_collisionPairs.emplace_back(colA, colB);
        }
    }

    m_broadPhasePairs.clear(); // 次フレーム用にクリア
}

// OBBの判定 兼 BoxとBoxの判定
bool ColliderManager::HitCheckOBBToOBB(const OBB& a, const OBB& b)
{
    const VECTOR& Ap = a.center;
    const VECTOR& Bp = b.center;
    VECTOR T = VSub(Bp, Ap);

    const VECTOR (&Aaxis)[3] = a.axes;
    const VECTOR (&Baxis)[3] = b.axes;

    double Ahalf[3] = { a.halfLen[0], a.halfLen[1], a.halfLen[2] };
    double Bhalf[3] = { b.halfLen[0], b.halfLen[1], b.halfLen[2] };

    double R[3][3], AbsR[3][3];
    const double EPS = 1e-6;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            R[i][j] = VDot(Aaxis[i], Baxis[j]);
            AbsR[i][j] = fabs(R[i][j]) + EPS;
        }
    }

    double tA[3] = {
        VDot(T, Aaxis[0]),
        VDot(T, Aaxis[1]),
        VDot(T, Aaxis[2])
    };

    // A の軸
    for (int i = 0; i < 3; i++) {
        double ra = Ahalf[i];
        double rb = Bhalf[0] * AbsR[i][0] + Bhalf[1] * AbsR[i][1] + Bhalf[2] * AbsR[i][2];
        if (fabs(tA[i]) > ra + rb) return false;
    }

    // B の軸
    for (int j = 0; j < 3; j++) {
        double t = fabs(VDot(T, Baxis[j]));
        double ra = Ahalf[0] * AbsR[0][j] + Ahalf[1] * AbsR[1][j] + Ahalf[2] * AbsR[2][j];
        double rb = Bhalf[j];
        if (t > ra + rb) return false;
    }

    // 交差（外積）9軸
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            double t = fabs(tA[(i+2)%3] * R[(i+1)%3][j] - tA[(i+1)%3] * R[(i+2)%3][j]);

            double ra =
                Ahalf[(i+1)%3] * AbsR[(i+2)%3][j] +
                Ahalf[(i+2)%3] * AbsR[(i+1)%3][j];

            double rb =
                Bhalf[(j+1)%3] * AbsR[i][(j+2)%3] +
                Bhalf[(j+2)%3] * AbsR[i][(j+1)%3];

            if (t > ra + rb) return false;
        }
    }

    return true;
}

// 球の中心とBoxとの最近点との距離で当たり判定
bool ColliderManager::HitCheckBoxToSphere(const OBB& b, const SphereType& s)
{
    VECTOR d = VSub(s.spherePos, b.center);

    float x = VDot(d, b.axes[0]);
    float y = VDot(d, b.axes[1]);
    float z = VDot(d, b.axes[2]);

    float cx = std::fmax(-b.halfLen[0], std::fmin(x, b.halfLen[0]));
    float cy = std::fmax(-b.halfLen[1], std::fmin(y, b.halfLen[1]));
    float cz = std::fmax(-b.halfLen[2], std::fmin(z, b.halfLen[2]));

    VECTOR closest =
        VAdd(b.center,
            VAdd(
                VAdd(VScale(b.axes[0], cx),
                    VScale(b.axes[1], cy)),
                VScale(b.axes[2], cz)));

    float distSq = VSquareSize(VSub(closest, s.spherePos));

    return distSq <= (float)(s.radius * s.radius);
}

// カプセルとBoxの判定
bool ColliderManager::HitCheckBoxToCapsule(const OBB& b, const CapsuleType& c)
{
    auto ToLocal = [&](const VECTOR& p) {
        VECTOR d = VSub(p, b.center);
        return VGet(
            VDot(d, b.axes[0]),
            VDot(d, b.axes[1]),
            VDot(d, b.axes[2])
        );
        };

    VECTOR p0 = ToLocal(c.posTop);
    VECTOR p1 = ToLocal(c.posBottom);

    VECTOR aabbMin = VGet(-b.halfLen[0], -b.halfLen[1], -b.halfLen[2]);
    VECTOR aabbMax = VGet(b.halfLen[0], b.halfLen[1], b.halfLen[2]);

    // 修正：SegmentOBBDistSq ではなく AABB 用の関数を呼ぶ
    double distSq = SegmentBoxDistSqLocal(p0, p1, aabbMin, aabbMax);

    return distSq <= c.radius * c.radius;
}

// 中心点の距離と半径の和で判定
bool ColliderManager::HitCheckSphereToSphere(const SphereType& s1, const SphereType& s2)
{
    VECTOR diff = VSub(s1.spherePos, s2.spherePos);
    double distSq = VDot(diff, diff);
    double rSum = s1.radius + s2.radius;

    return distSq <= rSum * rSum;
}

// Sphere と Capsule の当たり判定
bool ColliderManager::HitCheckSphereToCapsule(const SphereType& s, const CapsuleType& c)
{
    // カプセルの中心軸（線分）と球の中心の距離²を計算
    double distSq = PointToSegmentDistSq(s.spherePos, c.posTop, c.posBottom);

    // 半径の和
    double radiusSum = s.radius + c.radius;

    // 距離²と半径の和²を比較
    return distSq <= radiusSum * radiusSum;
}

// カプセル同士の当たり判定
bool ColliderManager::HitCheckCapsuleToCapsule(const CapsuleType& c1, const CapsuleType& c2)
{
    // c1 の中心線と c2 の中心線の最近距離²
    double distSq = SegmentSegmentDistSq(c1.posTop, c1.posBottom, c2.posTop, c2.posBottom);

    // 半径の和
    double rSum = c1.radius + c2.radius;

    // 距離²が半径の和の²以下なら当たり
    return distSq <= rSum * rSum;
}

// 補助関数

// 線分同士の最近距離²を求める
double ColliderManager::SegmentSegmentDistSq(const VECTOR& p1, const VECTOR& q1, const VECTOR& p2, const VECTOR& q2) 
{
    VECTOR d1 = VSub(q1, p1); // 線分1の方向
    VECTOR d2 = VSub(q2, p2); // 線分2の方向
    VECTOR r = VSub(p1, p2);  // p1 - p2

    double a = VDot(d1, d1);
    double e = VDot(d2, d2);
    double f = VDot(d2, r);

    double s, t;

    if (a <= 1e-6 && e <= 1e-6) return VDot(r, r); // 両方とも点

    if (a <= 1e-6) {
        s = 0.0;
        t = f / e;
        t = fmax(0.0, fmin(1.0, t));
    }
    else {
        double c = VDot(d1, r);
        if (e <= 1e-6) {
            t = 0.0;
            s = fmax(0.0, fmin(1.0, -c / a));
        }
        else {
            double b = VDot(d1, d2);
            double denom = a * e - b * b;
            if (denom != 0.0)
                s = fmax(0.0, fmin(1.0, (b * f - c * e) / denom));
            else
                s = 0.0;

            t = (b * s + f) / e;

            if (t < 0.0) {
                t = 0.0;
                s = fmax(0.0, fmin(1.0, -c / a));
            }
            else if (t > 1.0) {
                t = 1.0;
                s = fmax(0.0, fmin(1.0, (b - c) / a));
            }
        }
    }

    VECTOR c1 = VAdd(p1, VScale(d1, (float)s));
    VECTOR c2 = VAdd(p2, VScale(d2, (float)t));
    VECTOR diff = VSub(c1, c2);
    return VDot(diff, diff); // 距離²を返す
}

// 点 p と線分 ab の距離²を求める
double ColliderManager::PointToSegmentDistSq(const VECTOR& p, const VECTOR& a, const VECTOR& b)
{
    VECTOR ab = VSub(b, a);    // 線分の方向ベクトル
    VECTOR ap = VSub(p, a);    // 点 a から p へのベクトル
    double abLenSq = VDot(ab, ab); // 線分の長さ²

    if (abLenSq == 0.0) return VDot(ap, ap); // 線分が点の場合

    // 点 p を線分 ab に射影
    double t = VDot(ap, ab) / abLenSq;
    t = fmax(0.0, fmin(1.0, t)); // 線分上にクランプ

    VECTOR closest = VAdd(a, VScale(ab, (float)t)); // 線分上の最近点
    VECTOR diff = VSub(p, closest);

    return VDot(diff, diff); // 距離²
}

// 線分と局所座標の距離²
double ColliderManager::SegmentBoxDistSqLocal(const VECTOR& p0, const VECTOR& p1, const VECTOR& mn, const VECTOR& mx)
{
    VECTOR d = VSub(p1, p0);  // 線分方向
    double t0 = 0.0, t1 = 1.0;

    for (int i = 0; i < 3; i++)
    {
        double s = (&p0.x)[i];
        double di = (&d.x)[i];
        double a = (&mn.x)[i];
        double b = (&mx.x)[i];

        if (fabs(di) < 1e-8)
        {
            if (s < a || s > b) return 1e9;  // 線分が平行で範囲外
        }
        else
        {
            double o = 1.0 / di;
            double tA = (a - s) * o;
            double tB = (b - s) * o;
            if (tA > tB) std::swap(tA, tB);
            t0 = std::fmax(t0, tA);
            t1 = std::fmin(t1, tB);
            if (t0 > t1) return 1e9;  // 線分はAABBに交差しない
        }
    }

    double t = std::clamp(t0, 0.0, 1.0);
    VECTOR closest = VAdd(p0, VScale(d, (float)t));

    // 線分上の最近点をAABB内にクランプ
    VECTOR q = {
        std::clamp(closest.x, mn.x, mx.x),
        std::clamp(closest.y, mn.y, mx.y),
        std::clamp(closest.z, mn.z, mx.z)
    };

    return VSquareSize(VSub(closest, q));  // 距離²
}