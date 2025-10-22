#include "BoxCollider.h"
#include "ColliderType.h"
#include <variant>

// コンストラクタ
BoxCollider::BoxCollider(VECTOR min, VECTOR max, ColliderManager* manager, bool isActive)
	: Collider(BoxType{ min ,max }, manager, isActive)
{
	SetAABB(); // AABBの設定
}

// デストラクタ
BoxCollider::~BoxCollider()
{}

// コピコン
BoxCollider::BoxCollider(const BoxCollider& other)
	: Collider(BoxType{ other.GetBox()->min ,other.GetBox()->max}, other.m_manager, other.m_isActive)
{
#ifdef _DEBUG // コピコンがよばれたときの処理（把握用）
	MessageBoxW(
		nullptr,
		L"BoxCollider コピーコンストラクタが呼ばれました。",
		L"通知",
		MB_OK | MB_ICONINFORMATION
	);
#endif // _DEBUG
}

// Update
void BoxCollider::Update()
{

}

// Transform基準のコライダーサイズ設定
void BoxCollider::SetTrans()
{

}

// AABBの設定
void BoxCollider::SetAABB()
{
	const BoxType& BoxPos = std::get<BoxType>(m_data);

	aabb.min = BoxPos.min;
	aabb.max = BoxPos.max;
}

