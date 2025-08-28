#include "Collider.h"
#include "ColliderManager.h"

// コンストラクタ
Collider::Collider(const std::variant<BoxType, SphereType, CapsuleType>& data, ColliderManager* manager, bool isActive)	:
	m_type((ColliderType)data.index()), m_data(data), 
	m_manager(manager), m_isActive(isActive)
{
	// 変数の初期化
	m_layer = Layer::None;
	m_collisionMask = Layer::None;
	m_tag = Tag::None;

	m_manager->AddCollider(this); // ColliderをManagerに追加

}

//デストラクタ
Collider::~Collider()
{
	m_manager->DeleteCollider(this); // colliderManagerの変数から削除
}

Collider::Collider(const Collider&)
{
// ここに入ったらエラーはほぼ確定である
#ifdef _DEBUG
	MessageBoxW(
		nullptr,
		L"Collider コピーコンストラクタが呼ばれました。",
		L"通知",
		MB_OK | MB_ICONINFORMATION
	);
#endif // _DEBUG
}

// 基本進行
void Collider::Update()
{
	if (m_isActive)
	{
		Activate();
	}
	else if (!m_isActive)
	{
		Deactivate();
	}
}

// アクティブ時
void Collider::Activate()
{

}

// 非アクティブ時
void Collider::Deactivate()
{

}

// イベントチェック
void Collider::EventCheck(std::vector<Collider*>& colliders)
{
	{
		for (Collider* other : currentHitColliders)
		{
			if (std::find(previousHitColliders.begin(), previousHitColliders.end(), other) == previousHitColliders.end())
			{
				OnCollisionEnter(other); // 初めて当たった
			}
			else
			{
				OnCollisionStay(other); // 前も今も当たってる
			}
		}

		for (Collider* other : previousHitColliders)
		{
			if (std::find(currentHitColliders.begin(), currentHitColliders.end(), other) == currentHitColliders.end())
			{
				OnCollisionExit(other); // 今回は当たっていない
			}
		}

		previousHitColliders = currentHitColliders; // 前の状態を更新
		currentHitColliders.clear(); // 今の状態は初期化
	}
}