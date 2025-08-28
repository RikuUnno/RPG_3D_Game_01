#include "CapsuleCollider.h"
#include "ColliderType.h"
#include <variant>

CapsuleCollider::CapsuleCollider(VECTOR top, VECTOR bottom, double height, double radius, ColliderManager* manager, bool isActive)
	: Collider(CapsuleType{ top, bottom, height, radius }, manager, isActive)
{
	SetAABB(); // AABB�̐ݒ�
}

CapsuleCollider::~CapsuleCollider()
{}

CapsuleCollider::CapsuleCollider(const CapsuleCollider& other)
    : Collider(CapsuleType{ other.GetCapsule()->posTop, other.GetCapsule()->posBottom,other.GetCapsule()->height, other.GetCapsule()->radius },
        other.m_manager, other.m_isActive)
{
#ifdef _DEBUG
    MessageBoxW(
        nullptr,
        L"CapsuleCollider �R�s�[�R���X�g���N�^���Ă΂�܂����B",
        L"�ʒm",
        MB_OK | MB_ICONINFORMATION
    );
#endif // _DEBUG
}

// AABB�̐ݒ�
void CapsuleCollider::SetAABB()
{
    const CapsuleType& capPos = std::get<CapsuleType>(m_data);

    aabb.min.x = fmin(capPos.posTop.x, capPos.posBottom.x) - (float)capPos.radius;
    aabb.min.y = fmin(capPos.posTop.y, capPos.posBottom.y) - (float)capPos.radius;
    aabb.min.z = fmin(capPos.posTop.z, capPos.posBottom.z) - (float)capPos.radius;

    aabb.max.x = fmax(capPos.posTop.x, capPos.posBottom.x) + (float)capPos.radius;
    aabb.max.y = fmax(capPos.posTop.y, capPos.posBottom.y) + (float)capPos.radius;
    aabb.max.z = fmax(capPos.posTop.z, capPos.posBottom.z) + (float)capPos.radius;
}
