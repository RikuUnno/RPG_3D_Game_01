#pragma once
#include <vector>


class Collider
{
private:
	

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
