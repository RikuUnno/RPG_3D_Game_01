#pragma once
#include <vector>
#include <variant>
#include "Layer.h"
#include "Tag.h"
#include "ColliderType.h"

class ColliderManager; 

class Collider
{
private: // オブジェクトの状態
	bool m_isActive; // オブジェクト（コライダー）の状態

private: // コライダーの種類に応じたPos用
	ColliderType m_type;									// コライダーの種類
	std::variant<BoxType, SphereType, CapsuleType> m_data;	// 上記の変数に応じたコライダーのPos

private: // 簡易的な当たり判定用
	AABB aabb;	// 当たり判定用

private: // コライダーの登録用
	ColliderManager* m_manager; // コライダーの登録先のマネージャー

private: // レイヤー/マスク処理用
	Layer m_layer;			// 自身のレイヤー
	Layer m_collisionMask;	// 衝突判定
	Tag m_tag;				// Tag

public: // コンストラクタ云々
	Collider(const std::variant<BoxType, SphereType, CapsuleType>& data, ColliderManager* manager, bool isActive);
	virtual ~Collider();

	Collider(const Collider&) = delete;			// 設計中に変えるかも
	void operator=(const Collider&) = delete;	// 設計中に変えるかも

public: // 進行用
	void Update();		// 基本進行の関数
	void Activate();	// アクティブ時
	void Deactivate();	// 非アクティブ時

public: // レイヤー/マスク処理用変数の設定/再設定用
	virtual void SetLayer(Layer l) { m_layer = l; }									// レイヤーの設定/再設定
	virtual void SetMask(uint32_t m) { m_collisionMask = static_cast<Layer>(m); }	// マスクの設定/再設定
	virtual void SetTag(Tag t) { m_tag = t; }										// タグの設定/再設定

public: // 状態設定
	void SetActiveCollider(bool active) { m_isActive = active; } // 状態の設定

public: // 当たり判定の応答
	void EventCheck(std::vector<Collider*> &colliders);

	virtual void OnCollisionEnter() {};
	virtual void OnCollisionStay() {};
	virtual void OnCollisionExit() {};
};
