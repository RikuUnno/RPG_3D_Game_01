#pragma once
#include "Collider.h"

#include <vector>

class ColliderManager
{
private:
	std::vector<Collider*> colliders;

public:
	ColliderManager();
	virtual ~ColliderManager();

	ColliderManager(const ColliderManager&) = delete;
	void operator=(const ColliderManager&) = delete;

public:
	void Update();

public:
	void AddCollider(Collider* collider); // コライダーの追加

	void DeleteCollider(Collider* collider); // コライダーの削除

public:
	void HitJudgment(); // 当たり判定
};