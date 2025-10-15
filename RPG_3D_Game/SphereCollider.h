#pragma once
#include "Collider.h"
#include "DxLib.h"

class ColliderManager;

class SphereCollider
	: public Collider
{
private:

public: // コライダー関係
	SphereCollider(VECTOR spherePos, double radius, ColliderManager* manager, bool isActive);
	virtual ~SphereCollider();
	SphereCollider(const SphereCollider& other);

public: // ゲッターセッター
	const SphereType* GetSphere() const override { return std::get_if<SphereType>(&m_data); } // SphereTypeのゲッター

public: // 当たり判定関係
	void SetAABB() override;
};