#include "ColliderManager.h"

ColliderManager::ColliderManager()
{}

ColliderManager::~ColliderManager()
{}

void ColliderManager::Update()
{

}

void ColliderManager::AddCollider(Collider* collider)
{
    m_allColliders.emplace_back(collider);
}

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

#ifdef _DEBUG
    DrawFormatString(0, 150, GetColor(255, 255, 255), "colliderSize = %d", (int)m_layerMaskPairs.size());
#endif // _DEBUG

    for (auto& pair : m_layerMaskPairs)
    {
        Collider* a = pair.first;
        Collider* b = pair.second;

        // AABB を取得
        AABB aAABB = *a->GetAABB();
        AABB bAABB = *b->GetAABB();

        if (CheckAABB(aAABB, bAABB))
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
            const BoxType* a = colA->GetBox();
            const BoxType* b = colB->GetBox();
            if (a && b) isHit = CheckAABB(*a, *b);
        }
        else if (typeA == ColliderType::Box && typeB == ColliderType::Capsule)
        {
            const BoxType* a = colA->GetBox();
            const CapsuleType* b = colB->GetCapsule();
            if (a && b) isHit = HitCheckBoxToCapsule(*a, *b);
        }
        else if (typeA == ColliderType::Box && typeB == ColliderType::Sphere)
        {
            const BoxType* a = colA->GetBox();
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

// AABBの判定 兼 BoxとBoxの判定
bool ColliderManager::CheckAABB(const AABB& a, const AABB& b)
{
    return (a.min.x <= b.max.x && a.max.x >= b.min.x) &&
        (a.min.y <= b.max.y && a.max.y >= b.min.y) &&
        (a.min.z <= b.max.z && a.max.z >= b.min.z);
}

// 球の中心とBoxとの最近点との距離で当たり判定
bool ColliderManager::HitCheckBoxToSphere(const BoxType& b, const SphereType& s)
{
    VECTOR c = s.spherePos;

    // Box内の最近点を取得
    VECTOR closest = {
        fmax(b.min.x, fmin(c.x, b.max.x)),
        fmax(b.min.y, fmin(c.y, b.max.y)),
        fmax(b.min.z, fmin(c.z, b.max.z))
    };

    VECTOR diff = VSub(c, closest);
    double distSq = VDot(diff, diff);

    // 球の半径と比較
    return distSq <= s.radius * s.radius;
}

// カプセルとBoxの判定
bool ColliderManager::HitCheckBoxToCapsule(const BoxType& b, const CapsuleType& c)
{
    double distSq = SegmentAABBDistSq(c.posTop, c.posBottom, b);
    return distSq <= (c.radius * c.radius);
}

// 中心点の距離と半径の和で判定
bool ColliderManager::HitCheckSphereToSphere(const SphereType& s1, const SphereType& s2)
{
    VECTOR diff = VSub(s1.spherePos, s2.spherePos);
    double distSq = VDot(diff, diff);
    double rSum = s1.radius + s2.radius;

    return distSq <= rSum * rSum;
}

// 球の中心とカプセル線分の距離で判定
bool ColliderManager::HitCheckSphereToCapsule(const SphereType& s, const CapsuleType& c)
{
    double distSq = PointToSegmentDistSq(s.spherePos, c.posTop, c.posBottom);
    double rSum = s.radius + c.radius;

    return distSq <= rSum * rSum;
}

// 中心線同士の最近距離と半径の和で判定
bool ColliderManager::HitCheckCapsuleToCapsule(const CapsuleType& c1, const CapsuleType& c2)
{
    double distSq = SegmentSegmentDistSq(c1.posTop, c1.posBottom, c2.posTop, c2.posBottom);
    double rSum = c1.radius + c2.radius;

    return distSq <= rSum * rSum;
}

// 補助関数

// 線分同士の最近距離²を求める
double ColliderManager::SegmentSegmentDistSq(const VECTOR& p1, const VECTOR& q1, const VECTOR& p2, const VECTOR& q2)
{
    VECTOR d1 = VSub(q1, p1); // 線分1の方向
    VECTOR d2 = VSub(q2, p2); // 線分2の方向
    VECTOR r = VSub(p1, p2);  // 差ベクトル

    double a = VDot(d1, d1);
    double e = VDot(d2, d2);
    double f = VDot(d2, r);

    double s, t;

    if (a <= 1e-6 && e <= 1e-6) return VDot(r, r); // 両方とも点

    if (a <= 1e-6) {
        s = 0;
        t = f / e;
        t = fmax(0.0, fmin(1.0, t));
    }
    else {
        double c = VDot(d1, r);
        if (e <= 1e-6) {
            t = 0;
            s = fmax(0.0, fmin(1.0, -c / a));
        }
        else {
            double b = VDot(d1, d2);
            double denom = a * e - b * b;

            if (denom != 0.0)
                s = fmax(0.0, fmin(1.0, (b * f - c * e) / denom));
            else
                s = 0;

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
    VECTOR d = VSub(c1, c2);

    return VDot(d, d);
}

// 点と線分の距離²を求める
double ColliderManager::PointToSegmentDistSq(const VECTOR& p, const VECTOR& a, const VECTOR& b)
{
    VECTOR ab = VSub(b, a);
    VECTOR ap = VSub(p, a);
    double abLenSq = VDot(ab, ab);

    if (abLenSq == 0.0) return VDot(ap, ap); // 線分が点の場合

    // 最近点を線分上に投影
    double t = VDot(ap, ab) / abLenSq;
    t = fmax(0.0, fmin(1.0, t)); // t を 0〜1 にクランプ

    VECTOR closest = VAdd(a, VScale(ab, (float)t));
    VECTOR d = VSub(p, closest);
    return VDot(d, d); // 距離の2乗
}

// 点とAABBの距離²を計算（点がAABB内なら0）
double ColliderManager::PointToAABBDistSq(const VECTOR& p, const BoxType& box)
{
    double dx = fmax(fmax(box.min.x - p.x, 0.0), p.x - box.max.x);
    double dy = fmax(fmax(box.min.y - p.y, 0.0), p.y - box.max.y);
    double dz = fmax(fmax(box.min.z - p.z, 0.0), p.z - box.max.z);
    return dx * dx + dy * dy + dz * dz;
}

// 線分とAABBの距離²を計算
double ColliderManager::SegmentAABBDistSq(const VECTOR& p1, const VECTOR& p2, const BoxType& box)
{
    // 線分方向ベクトル
    VECTOR d = VSub(p2, p1);
    double length = sqrt(VDot(d, d));
    if (length < 1e-6) {
        // 線分が点なら点とAABBの距離
        return PointToAABBDistSq(p1, box);
    }
    VECTOR dir = VScale(d, 1.0f / (float)length);

    // 線分パラメータの範囲
    double t_min = 0.0;
    double t_max = length;

    // 3軸でスラブテストを行い、線分がAABBに交差するか判定
    for (int i = 0; i < 3; ++i) {
        double p = ((float*)&p1)[i];
        double d_i = ((float*)&dir)[i];
        double box_min = ((float*)&box.min)[i];
        double box_max = ((float*)&box.max)[i];

        if (fabs(d_i) < 1e-8) {
            // 平行で線分外なら距離は最短点との距離
            if (p < box_min || p > box_max) {
                return PointToAABBDistSq(p1, box);
            }
        }
        else {
            // t の範囲を更新
            double t1 = (box_min - p) / d_i;
            double t2 = (box_max - p) / d_i;
            if (t1 > t2) std::swap(t1, t2);
            t_min = fmax(t_min, t1);
            t_max = fmin(t_max, t2);
            if (t_min > t_max) {
                // 線分はAABBに交差しない → 距離は最近点の距離
                return PointToAABBDistSq(p1, box);
            }
        }
    }

    // 線分がAABBと交差する → 距離は0
    if (t_min <= t_max && t_min <= length && t_max >= 0)
        return 0.0;

    // 線分とAABBが交差しない場合は
    // 線分の端点とAABBの距離の最小値を返す
    double dist1 = PointToAABBDistSq(p1, box);
    double dist2 = PointToAABBDistSq(p2, box);
    return fmin(dist1, dist2);
}
