#pragma once
#include <vector>
#include "Layer.h"

class Collider
{
private:
	Layer layer;
	Layer collisionMask;

public:
	Collider();
	virtual ~Collider();

	Collider(const Collider&) = delete;
	void operator=(const Collider&) = delete;

public:
	void EventCheck(std::vector<Collider> colliders);

	virtual void OnCollisionEnter() {};
	virtual void OnCollisionStay() {};
	virtual void OnCollisionExit() {};
};
