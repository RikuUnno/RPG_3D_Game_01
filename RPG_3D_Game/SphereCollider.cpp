#include "SphereCollider.h"
#include "ColliderType.h"
#include <variant>

// �R���X�g���N�^
SphereCollider::SphereCollider(VECTOR spherePos, double radius, ColliderManager* manager, bool isActive)
	: Collider(SphereType{ spherePos ,radius }, manager, isActive)
{
	SetAABB(); // AABB�̐ݒ�
}

// �f�X�g���N�^
SphereCollider::~SphereCollider()
{}

// �R�s�R��
SphereCollider::SphereCollider(const SphereCollider& other)
	: Collider(SphereType{ other.GetSphere()->spherePos, other.GetSphere()->radius }, other.m_manager, other.m_isActive)
{
#ifdef _DEBUG // �R�s�R������΂ꂽ�Ƃ��̏����i�c���p�j
	MessageBoxW(
		nullptr,
		L"SphereCollider �R�s�[�R���X�g���N�^���Ă΂�܂����B",
		L"�ʒm",
		MB_OK | MB_ICONINFORMATION
	);
#endif // _DEBUG
}

// Update
void SphereCollider::Update()
{

}

// Transform��̃R���C�_�[�T�C�Y�ݒ�
void SphereCollider::SetTrans()
{

}

// AABB�̐ݒ�
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