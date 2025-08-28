#include "SphereCollider.h"
#include "ColliderType.h"
#include <variant>

SphereCollider::SphereCollider(VECTOR spherePos, double radius, ColliderManager* manager, bool isActive)
	: Collider(SphereType{ spherePos ,radius }, manager, isActive)
{
	SetAABB(); // AABBの設定
}

SphereCollider::~SphereCollider()
{}

SphereCollider::SphereCollider(const SphereCollider& other)
	: Collider(SphereType{ other.GetSphere()->spherePos, other.GetSphere()->radius }, other.m_manager, other.m_isActive)
{
#ifdef _DEBUG
	MessageBoxW(
		nullptr,
		L"SphereCollider コピーコンストラクタが呼ばれました。",
		L"通知",
		MB_OK | MB_ICONINFORMATION
	);
#endif // _DEBUG
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