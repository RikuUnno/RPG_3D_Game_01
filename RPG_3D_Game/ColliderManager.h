// 当たり判定を管理するクラス

#pragma once
#include "Collider.h"

#include <vector>

class ColliderManager
{
private:
	std::vector<Collider*> m_allColliders;	// すべてのコライダーを格納
	std::vector<std::pair<Collider*, Collider*>> m_layerMaskPairs; // レイヤーマスク通過
	std::vector<std::pair<Collider*, Collider*>> m_broadPhasePairs;     // AABB 通過
	std::vector<std::pair<Collider*, Collider*>> m_collisionPairs;      // 実際に衝突中


public: // コンストラクタ関係
	ColliderManager();
	virtual ~ColliderManager();

	ColliderManager(const ColliderManager&) = delete;
	void operator=(const ColliderManager&) = delete;

public: // アップデート
	void Update();

public: // コライダー追加/削除
	void AddCollider(Collider* collider); // コライダーの追加
	void DeleteCollider(Collider* collider); // コライダーの削除

private: // 当たり判定処理
	void HitJudgment(); // 当たり判定

	void LayerAndMaskPhase();	// レイヤー/マスク判定
	void BroadPhase();			// 簡易的な当たり判定
	void NarrowPhase();			// 当たり判定の実装

private: // 当たり判定
	bool CheckAABB(const AABB& a, const AABB& b); // AABBの判定 兼 BoxとBoxの判定
	bool HitCheckBoxToSphere(const BoxType& b, const SphereType& s); // BoxとSphereの判定
	bool HitCheckBoxToCapsule(const BoxType& b, const CapsuleType& c); // BoxとCapsaleの判定
	bool HitCheckSphereToSphere(const SphereType& s1, const SphereType& s2); // SphereとSphereの判定
	bool HitCheckSphereToCapsule(const SphereType& s, const CapsuleType& c); // SphereとCapsaleの判定
	bool HitCheckCapsuleToCapsule(const CapsuleType& c1, const CapsuleType& c2); // CapsaleとCapsaleの判定

private: // 当たり判定用の補助関数
	// 線分同士の最近距離²を求める
	double SegmentSegmentDistSq(const VECTOR& p1, const VECTOR& q1, const VECTOR& p2, const VECTOR& q2);
	// 点と線分の距離²を求める
	double PointToSegmentDistSq(const VECTOR& p, const VECTOR& a, const VECTOR& b);
	// 点とAABBの距離²を計算（点がAABB内なら0）
	double PointToAABBDistSq(const VECTOR& p, const BoxType& box);
	// 線分とAABBの距離²を計算
	double SegmentAABBDistSq(const VECTOR& p1, const VECTOR& p2, const BoxType& box);
};