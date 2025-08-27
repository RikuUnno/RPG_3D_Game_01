#include "Collider.h"
#include "ColliderManager.h"

// �R���X�g���N�^
Collider::Collider(const std::variant<BoxType, SphereType, CapsuleType>& data, ColliderManager* manager, bool isActive)	:
	m_type((ColliderType)data.index()), m_data(data), 
	m_manager(manager), m_isActive(isActive)
{
	// �ϐ��̏�����
	m_layer = Layer::None;
	m_collisionMask = Layer::None;
	m_tag = Tag::None;

	m_manager->AddCollider(this); // Collider��Manager�ɒǉ�

}

//�f�X�g���N�^
Collider::~Collider()
{
	m_manager->DeleteCollider(this); // colliderManager�̕ϐ�����폜
}

// ��{�i�s
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

// �A�N�e�B�u��
void Collider::Activate()
{

}

// ��A�N�e�B�u��
void Collider::Deactivate()
{

}

void Collider::EventCheck(std::vector<Collider*>& colliders)
{
	
}