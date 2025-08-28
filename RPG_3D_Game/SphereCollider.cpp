#include "SphereCollider.h"
#include "ColliderType.h"
#include <variant>

SphereCollider::SphereCollider(VECTOR spherePos, double radius, ColliderManager* manager, bool isActive)
	: Collider(SphereType{ spherePos ,radius }, manager, isActive)
{
	SetAABB(); // AABB�̐ݒ�
}

SphereCollider::~SphereCollider()
{}

SphereCollider::SphereCollider(const SphereCollider& other)
	: Collider(SphereType{ other.GetSphere()->spherePos, other.GetSphere()->radius }, other.m_manager, other.m_isActive)
{
#ifdef _DEBUG
	MessageBoxW(
		nullptr,
		L"SphereCollider �R�s�[�R���X�g���N�^���Ă΂�܂����B",
		L"�ʒm",
		MB_OK | MB_ICONINFORMATION
	);
#endif // _DEBUG
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