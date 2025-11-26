#pragma once
#include "Collider.h"
#include "DxLib.h"

class ColliderManager;

class CapsuleCollider
	: public Collider
{
private:
	float m_originalRadius;   // スケール前の半径

public: // コンストラクタ
	CapsuleCollider(Transform transform, float height, float radius, ColliderManager* manager);
	virtual ~CapsuleCollider();
	CapsuleCollider(const CapsuleCollider& other);

public:
	void Update() override; // 進行

private: // Transform基準のコライダーサイズ設定
	void SetTrans() override;

public: // ゲッターセッター
	const CapsuleType* GetCapsule() const override { return std::get_if<CapsuleType>(&m_data); } // CapsuleTypeのゲッター

public: // 当たり判定関係
	void SetOBB() override;

public: // コライダーの可視化
	void DrawCollider() const override;
};