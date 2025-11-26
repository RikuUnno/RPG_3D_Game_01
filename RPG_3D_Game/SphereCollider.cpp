#include "SphereCollider.h"
#include "ColliderType.h"
#include <variant>

// コンストラクタ
SphereCollider::SphereCollider(Transform transform, float radius, ColliderManager* manager)
	: Collider([transform, radius]() {
			SphereType s;
			s.spherePos = transform.GetPos(); // Transformの座標
			s.radius = radius;
			return s;
		}(),
	manager,
	transform),
	m_originalRadius(radius)
{
	SetOBB(); // AABBの設定
}

// デストラクタ
SphereCollider::~SphereCollider()
{}

// コピコン
SphereCollider::SphereCollider(const SphereCollider& other)
	: Collider(
		[&other]() {
			SphereType s;
			s.spherePos = other.GetSphere()->spherePos;
			s.radius = other.GetSphere()->radius;
			return s;
		}(),
			other.m_manager,
			other.m_transform), // Transformをそのままコピー
			m_originalRadius(other.m_originalRadius)
{

	SetOBB(); // AABBの再設定

#ifdef _DEBUG // コピコンがよばれたときの処理（把握用）
	MessageBoxW(
		nullptr,
		L"SphereCollider コピーコンストラクタが呼ばれました。",
		L"通知",
		MB_OK | MB_ICONINFORMATION
	);
#endif // _DEBUG
}

// Update
void SphereCollider::Update()
{
	SetTrans(); // Transform基準のコライダーサイズ設定
	SetOBB(); // ワールド座標の AABB を更新
}

// Transform基準のコライダーサイズ設定
void SphereCollider::SetTrans()
{
	// Transform をワールドまで更新
	m_transform.LocalToWorld();

	SphereType& sph = std::get<SphereType>(m_data);

	VECTOR center = m_transform.GetPos();
	VECTOR scale = m_transform.GetScale();

	// X/Y/Z の平均スケールを使って radius を調整
	float scaleAvg = (scale.x + scale.y + scale.z) / 3.0f;

	sph.spherePos = center;
	sph.radius = m_originalRadius * scaleAvg;
}

// OBB 設定
void SphereCollider::SetOBB()
{
	const SphereType& s = std::get<SphereType>(m_data);

	obb.center = s.spherePos;

	// 球は回転しても形が変わらないので軸は単純
	obb.axes[0] = VGet(1, 0, 0); // X軸
	obb.axes[1] = VGet(0, 1, 0); // Y軸
	obb.axes[2] = VGet(0, 0, 1); // Z軸

	// 半長はすべて半径
	obb.halfLen[0] = s.radius;
	obb.halfLen[1] = s.radius;
	obb.halfLen[2] = s.radius;
}

// コライダーの可視化
void SphereCollider::DrawCollider() const
{
	const SphereType& SphePos = std::get<SphereType>(m_data);

	DrawSphere3D(SphePos.spherePos, SphePos.radius, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), TRUE);
}