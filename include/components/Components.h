#pragma once

enum class ComponentID
{
	UNDEFINED = -1,
	TTL = 0,
	INPUT = 1,
	POSITION = 2,
	VELOCITY = 3,
	HEALTH = 4,
	GRAPHICS = 5,
	COLLIDER = 6,
	GAMEPLAY= 7
};

class Components
{
public:
	virtual ComponentID getID() const = 0;
	~Components() {}
};