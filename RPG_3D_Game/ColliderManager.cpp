#include "ColliderManager.h"

ColliderManager::ColliderManager()
{}

ColliderManager::~ColliderManager()
{}

void ColliderManager::AddCollider(Collider* collider)
{
	colliders.emplace_back(collider);
}

void ColliderManager::DeleteCollider(Collider* collider)
{
	std::erase_if(colliders, [&](const auto& elem) { return elem == collider; });
}