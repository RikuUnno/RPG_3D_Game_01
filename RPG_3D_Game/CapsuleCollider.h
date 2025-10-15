#pragma once
#include "Collider.h"
#include "DxLib.h"

class ColliderManager;

class CapsuleCollider
	: public Collider
{
private:

public: // コンストラクタ
	CapsuleCollider(VECTOR top, VECTOR bottom, double height, double radius, ColliderManager* manager, bool isActive);
	virtual ~CapsuleCollider();
	CapsuleCollider(const CapsuleCollider& other);

public: // ゲッターセッター
	const CapsuleType* GetCapsule() const override { return std::get_if<CapsuleType>(&m_data); } // CapsuleTypeのゲッター

public: // 当たり判定関係
	void SetAABB() override;
};