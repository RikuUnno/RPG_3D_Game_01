#include "SphereCollider.h"
#include "ColliderType.h"
#include <variant>

// コンストラクタ
SphereCollider::SphereCollider(VECTOR spherePos, double radius, ColliderManager* manager, bool isActive)
	: Collider(SphereType{ spherePos ,radius }, manager, isActive)
{
	SetAABB(); // AABBの設定
}

// デストラクタ
SphereCollider::~SphereCollider()
{}

// コピコン
SphereCollider::SphereCollider(const SphereCollider& other)
	: Collider(SphereType{ other.GetSphere()->spherePos, other.GetSphere()->radius }, other.m_manager, other.m_isActive)
{
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