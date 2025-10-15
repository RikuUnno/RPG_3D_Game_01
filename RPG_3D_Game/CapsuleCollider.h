#pragma once
#include "Collider.h"
#include "DxLib.h"

class ColliderManager;

class CapsuleCollider
	: public Collider
{
private:

public: // �R���X�g���N�^
	CapsuleCollider(VECTOR top, VECTOR bottom, double height, double radius, ColliderManager* manager, bool isActive);
	virtual ~CapsuleCollider();
	CapsuleCollider(const CapsuleCollider& other);

public: // �Q�b�^�[�Z�b�^�[
	const CapsuleType* GetCapsule() const override { return std::get_if<CapsuleType>(&m_data); } // CapsuleType�̃Q�b�^�[

public: // �����蔻��֌W
	void SetAABB() override;
};