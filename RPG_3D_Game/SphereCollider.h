#pragma once
#include "Collider.h"
#include "DxLib.h"

class ColliderManager;

class SphereCollider
	: public Collider
{
private:

public:
	SphereCollider(VECTOR spherePos, double radius, ColliderManager* manager, bool isActive);
	virtual ~SphereCollider();
	SphereCollider(const SphereCollider& other);

public:
	const SphereType* GetSphere() const { return std::get_if<SphereType>(&m_data); } // SphereType‚ÌƒQƒbƒ^[

public:
	void SetAABB() override;
};