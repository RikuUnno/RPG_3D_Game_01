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

//// �A�N�e�B�u��
//void Collider::Activate()
//{
//
//}
//
//// ��A�N�e�B�u��
//void Collider::Deactivate()
//{
//
//}

// �f�o�b�N�p��AABB����ŕ\��
void Collider::DrawAABB() const
{
	int color = GetColor(255, 255, 255);

	VECTOR p[8] = {
		VGet(aabb.min.x, aabb.min.y, aabb.min.z),
		VGet(aabb.max.x, aabb.min.y, aabb.min.z),
		VGet(aabb.max.x, aabb.max.y, aabb.min.z),
		VGet(aabb.min.x, aabb.max.y, aabb.min.z),
		VGet(aabb.min.x, aabb.min.y, aabb.max.z),
		VGet(aabb.max.x, aabb.min.y, aabb.max.z),
		VGet(aabb.max.x, aabb.max.y, aabb.max.z),
		VGet(aabb.min.x, aabb.max.y, aabb.max.z)
	};

	// ����`��
	DrawLine3D(p[0], p[1], color); DrawLine3D(p[1], p[2], color);
	DrawLine3D(p[2], p[3], color); DrawLine3D(p[3], p[0], color);
	DrawLine3D(p[4], p[5], color); DrawLine3D(p[5], p[6], color);
	DrawLine3D(p[6], p[7], color); DrawLine3D(p[7], p[4], color);
	DrawLine3D(p[0], p[4], color); DrawLine3D(p[1], p[5], color);
	DrawLine3D(p[2], p[6], color); DrawLine3D(p[3], p[7], color);
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