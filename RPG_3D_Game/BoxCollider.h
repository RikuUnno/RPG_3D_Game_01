#pragma once
#include "Collider.h"
#include "DxLib.h"

class ColliderManager;

class BoxCollider
	: public Collider
{
private:

public: // コライダー関係
	BoxCollider(Transform transfrom, ColliderManager* manager);
	virtual ~BoxCollider();
	BoxCollider(const BoxCollider& other);

public:
	void Update() override; // 進行

private: // Transform基準のコライダーサイズ設定
	void SetTrans() override;

public: // ゲッターセッター
	const BoxType* GetBox() const override { return std::get_if<BoxType>(&m_data); } // BoxTypeのゲッター

public: // 当たり判定関係
	void SetAABB() override;
};