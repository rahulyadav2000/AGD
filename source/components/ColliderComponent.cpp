#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/PlayerStateComponent.h"

Rectangle& ColliderComponent::getBoundingBox()
{
	return boundingBox;
}

void ColliderComponent::init(Entity& entity, Vector2f size)
{
	bboxSize = size;
	boundingBox.setTopLeft(entity.getPosition());
	boundingBox.setBottomRight(bboxSize + entity.getPosition());
}


void ColliderComponent::draw(Window* window)
{
	window->draw(boundingBox.getDrawableRect());
}

Vector2f& ColliderComponent::getSize()
{
	return bboxSize;
}

bool ColliderComponent::intersect(std::shared_ptr<ColliderComponent> collider)
{
	return boundingBox.intersects(collider->boundingBox);
}
