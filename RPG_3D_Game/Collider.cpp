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

void Collider::EventCheck(std::vector<Collider*>& colliders)
{
	
}