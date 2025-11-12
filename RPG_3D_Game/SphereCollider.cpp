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
	transform)
{
	SetAABB(); // AABBの設定
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
			other.gameObject.GetTrans() // Transformをそのままコピー
			)
{

	SetAABB(); // AABBの再設定

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
	// Transform の位置を反映
	std::get<SphereType>(m_data).spherePos = gameObject.GetTrans().GetPos();
	SetAABB(); // ワールド座標の AABB を更新
}

// Transform基準のコライダーサイズ設定
void SphereCollider::SetTrans()
{

}

// AABBの設定
void SphereCollider::SetAABB()
{
	const SphereType& SphePos = std::get<SphereType>(m_data);

	aabb.min = VGet(
		SphePos.spherePos.x - (float)SphePos.radius,
		SphePos.spherePos.y - (float)SphePos.radius,
		SphePos.spherePos.z - (float)SphePos.radius
	);

	aabb.max = VGet(
		SphePos.spherePos.x + (float)SphePos.radius,
		SphePos.spherePos.y + (float)SphePos.radius,
		SphePos.spherePos.z + (float)SphePos.radius
	);
}