#include "ColliderManager.h"

ColliderManager::ColliderManager()
{}

ColliderManager::~ColliderManager()
{}

void ColliderManager::Update()
{

}

void ColliderManager::AddCollider(Collider* collider)
{
	colliders.emplace_back(collider);
}

void ColliderManager::DeleteCollider(Collider* collider)
{
	std::erase_if(colliders, [&](const auto& elem) { return elem == collider; });
}

void ColliderManager::HitJudgment()
{
    for (size_t i = 0; i < colliders.size(); ++i) {
        for (size_t j = i + 1; j < colliders.size(); ++j) {
            
        }
    }
}