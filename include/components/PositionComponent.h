#include <iostream>
#include "Components.h"

class PositionComponent : public Components
{
public:
	const Vector2f& getPosition() { return position; }
	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}

	virtual ComponentID getID() const override { return ComponentID::POSITION; }

private:
	Vector2f position;
};