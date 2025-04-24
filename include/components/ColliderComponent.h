#include <iostream>

class Rectangle;
class Window;
class Entity;

class ColliderComponent: public Components
{
public:
	ColliderComponent() {}
	~ColliderComponent() {}
	
	Rectangle& getBoundingBox();

	void init(Entity& entity, Vector2f size);

	void draw(Window* window);
	Vector2f& getSize();

	bool intersect(std::shared_ptr<ColliderComponent> collider);

	virtual ComponentID getID() const override { return ComponentID::COLLIDER; }

private:
	Rectangle boundingBox;
	Vector2f bboxSize;
};