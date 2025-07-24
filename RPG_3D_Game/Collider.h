#pragma once
#include <vector>
#include "Layer.h"
#include "Tag.h"

class Collider
{
private:
	Layer layer;
	Layer collisionMask;
	Tag tag;

public:
	Collider();
	virtual ~Collider();

	Collider(const Collider&) = delete;
	void operator=(const Collider&) = delete;

public:
	void SetLayer(Layer l) { layer = l; }
	void SetMask(uint32_t m) { collisionMask = static_cast<Layer>(m); }
	void SetTag(Tag t) { tag = t; }

public:
	void EventCheck(std::vector<Collider*> &colliders);

	virtual void OnCollisionEnter() {};
	virtual void OnCollisionStay() {};
	virtual void OnCollisionExit() {};
};
