#pragma once
#include "Collider.h"
#include "DxLib.h"

class ColliderManager;

class SphereCollider
	: public Collider
{
private:

public: // �R���C�_�[�֌W
	SphereCollider(VECTOR spherePos, double radius, ColliderManager* manager, bool isActive);
	virtual ~SphereCollider();
	SphereCollider(const SphereCollider& other);

public: // �Q�b�^�[�Z�b�^�[
	const SphereType* GetSphere() const override { return std::get_if<SphereType>(&m_data); } // SphereType�̃Q�b�^�[

public: // �����蔻��֌W
	void SetAABB() override;
};