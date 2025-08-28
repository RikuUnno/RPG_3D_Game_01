#pragma once
#include <vector>
#include <variant>
#include "Layer.h"
#include "Tag.h"
#include "ColliderType.h"

class ColliderManager; 

class Collider
{
protected: // オブジェクトの状態
	bool m_isActive; // オブジェクト（コライダー）の状態

protected: // コライダーの種類に応じたPos用
	ColliderType m_type;									// コライダーの種類
	std::variant<BoxType, SphereType, CapsuleType> m_data;	// 上記の変数に応じたコライダーのPos

protected: // 簡易的な当たり判定用
	AABB aabb;	// 当たり判定用

protected: // 当たり判定後のイベントチェック用変数
	std::vector<Collider*>previousHitColliders; //前（処理中のフレーム）の当たったCollider
	std::vector<Collider*>currentHitColliders;  //現在(処理中のフレーム)の当たったCollider

protected: // コライダーの登録用
	ColliderManager* m_manager; // コライダーの登録先のマネージャー

protected: // レイヤー/マスク処理用
	Layer m_layer;			// 自身のレイヤー
	Layer m_collisionMask;	// 衝突判定
	Tag m_tag;				// Tag

public: // コンストラクタ云々
	Collider(const std::variant<BoxType, SphereType, CapsuleType>& data, ColliderManager* manager, bool isActive);
	virtual ~Collider();

	Collider(const Collider&);			// 設計中に変えるかも
	void operator=(const Collider&) = delete;	// 設計中に変えるかも

public: // 進行用
	void Update();		// 基本進行の関数
	void Activate();	// アクティブ時
	void Deactivate();	// 非アクティブ時

public: // レイヤー/マスク処理用変数の設定/再設定用
	virtual void SetLayer(Layer layer)	 { m_layer = layer; }								// レイヤーの設定/再設定
	virtual void SetMask(uint32_t mask) { m_collisionMask = static_cast<Layer>(mask); }	// マスクの設定/再設定
	virtual void SetTag(Tag tag)		 { m_tag = tag; }									// タグの設定/再設定

public: // Typeゲッター
	ColliderType GetType() const { return m_type; }

public: // Layerゲッター
	Layer GetLayer() const { return m_layer; }
	Layer GetCollisionMask() const { return m_collisionMask; }

public: // Posゲッター
	virtual const BoxType* GetBox() const { return nullptr; }
	virtual const SphereType* GetSphere() const { return nullptr; }
	virtual const CapsuleType* GetCapsule() const { return nullptr; }

	const AABB* GetAABB() const { return &aabb; }

public: // 状態設定
	void SetActiveCollider(bool active) { m_isActive = active; } // 状態の設定

public: // 当たり判定の応答
	virtual void SetAABB() = 0; // AABBの設定（純粋）

	// イベントチェック
	void EventCheck(std::vector<Collider*> &colliders);

	virtual void OnCollisionEnter(Collider* other) {};	// 接触時
	virtual void OnCollisionStay(Collider* other) {};	// 接触中
	virtual void OnCollisionExit(Collider* other) {};	// 接触後
};
