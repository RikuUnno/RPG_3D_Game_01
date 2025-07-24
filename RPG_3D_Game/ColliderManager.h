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
	void AddCollider(Collider* collider); // �R���C�_�[�̒ǉ�

	void DeleteCollider(Collider* collider); // �R���C�_�[�̍폜

public:
	void HitJudgment(); // �����蔻��
};