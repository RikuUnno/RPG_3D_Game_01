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

Collider::Collider(const Collider&)
{
// �����ɓ�������G���[�͂قڊm��ł���
#ifdef _DEBUG
	MessageBoxW(
		nullptr,
		L"Collider �R�s�[�R���X�g���N�^���Ă΂�܂����B",
		L"�ʒm",
		MB_OK | MB_ICONINFORMATION
	);
#endif // _DEBUG
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

// �C�x���g�`�F�b�N
void Collider::EventCheck(std::vector<Collider*>& colliders)
{
	{
		for (Collider* other : currentHitColliders)
		{
			if (std::find(previousHitColliders.begin(), previousHitColliders.end(), other) == previousHitColliders.end())
			{
				OnCollisionEnter(other); // ���߂ē�������
			}
			else
			{
				OnCollisionStay(other); // �O�������������Ă�
			}
		}

		for (Collider* other : previousHitColliders)
		{
			if (std::find(currentHitColliders.begin(), currentHitColliders.end(), other) == currentHitColliders.end())
			{
				OnCollisionExit(other); // ����͓������Ă��Ȃ�
			}
		}

		previousHitColliders = currentHitColliders; // �O�̏�Ԃ��X�V
		currentHitColliders.clear(); // ���̏�Ԃ͏�����
	}
}