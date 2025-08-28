#include "BoxCollider.h"
#include "ColliderType.h"
#include <variant>

BoxCollider::BoxCollider(VECTOR min, VECTOR max, ColliderManager* manager, bool isActive)
	: Collider(BoxType{ min ,max }, manager, isActive)
{
	SetAABB(); // AABBの設定
}

BoxCollider::~BoxCollider()
{}

BoxCollider::BoxCollider(const BoxCollider& other)
	: Collider(BoxType{ other.GetBox()->min ,other.GetBox()->max}, other.m_manager, other.m_isActive)
{
#ifdef _DEBUG
	MessageBoxW(
		nullptr,
		L"BoxCollider コピーコンストラクタが呼ばれました。",
		L"通知",
		MB_OK | MB_ICONINFORMATION
	);
#endif // _DEBUG
}

// AABBの設定
void BoxCollider::SetAABB()
{
	const BoxType& BoxPos = std::get<BoxType>(m_data);

	aabb.min = BoxPos.min;
	aabb.max = BoxPos.max;
}
