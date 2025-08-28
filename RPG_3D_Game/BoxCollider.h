#pragma once
#include "Collider.h"
#include "DxLib.h"

class ColliderManager;

class BoxCollider
	: public Collider
{
private:

public:
	BoxCollider(VECTOR min, VECTOR max, ColliderManager* manager, bool isActive);
	virtual ~BoxCollider();
	BoxCollider(const BoxCollider& other);

public:
	const BoxType* GetBox() const { return std::get_if<BoxType>(&m_data); } // BoxType�̃Q�b�^�[

public:
	void SetAABB() override;
};