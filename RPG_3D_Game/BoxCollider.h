#pragma once
#include "Collider.h"
#include "DxLib.h"

class ColliderManager;

class BoxCollider
	: public Collider
{
private:

public: // コライダー関係
	BoxCollider(VECTOR min, VECTOR max, ColliderManager* manager, bool isActive);
	virtual ~BoxCollider();
	BoxCollider(const BoxCollider& other);

public: // ゲッターセッター
	const BoxType* GetBox() const override { return std::get_if<BoxType>(&m_data); } // BoxTypeのゲッター

public: // 当たり判定関係
	void SetAABB() override;
};