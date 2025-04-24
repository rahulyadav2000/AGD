#pragma once
#include "../utils/Vector2.h"

class Entity;
class VelocityComponent : public Components {
public:
	VelocityComponent(float s = 1.f) : speed(s){}
	void setVelocity(float x, float y) { direction.x = x, direction.y = y; }
	const Vector2f& getVelocity() const {
		return direction;
	}

	virtual ComponentID getID() const override { return ComponentID::VELOCITY; }

	const float& getSpeed() { return speed; }
private:
	Vector2f direction;
	float speed;
};