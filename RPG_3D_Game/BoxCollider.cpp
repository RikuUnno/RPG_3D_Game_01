#include "BoxCollider.h"
#include "ColliderType.h"
#include <variant>

// �R���X�g���N�^
BoxCollider::BoxCollider(VECTOR min, VECTOR max, ColliderManager* manager, bool isActive)
	: Collider(BoxType{ min ,max }, manager, isActive)
{
	SetAABB(); // AABB�̐ݒ�
}

// �f�X�g���N�^
BoxCollider::~BoxCollider()
{}

// �R�s�R��
BoxCollider::BoxCollider(const BoxCollider& other)
	: Collider(BoxType{ other.GetBox()->min ,other.GetBox()->max}, other.m_manager, other.m_isActive)
{
#ifdef _DEBUG // �R�s�R������΂ꂽ�Ƃ��̏����i�c���p�j
	MessageBoxW(
		nullptr,
		L"BoxCollider �R�s�[�R���X�g���N�^���Ă΂�܂����B",
		L"�ʒm",
		MB_OK | MB_ICONINFORMATION
	);
#endif // _DEBUG
}

// Update
void BoxCollider::Update()
{

}

// Transform��̃R���C�_�[�T�C�Y�ݒ�
void BoxCollider::SetTrans()
{

}

// AABB�̐ݒ�
void BoxCollider::SetAABB()
{
	const BoxType& BoxPos = std::get<BoxType>(m_data);

	aabb.min = BoxPos.min;
	aabb.max = BoxPos.max;
}

