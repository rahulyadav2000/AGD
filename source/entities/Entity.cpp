#include "../../include/components/Components.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/PlayerStateComponent.h"



Entity::Entity() :
	id(0),
	type(EntityType::UNDEFINED),
	deleted(false)
{
	position = std::make_shared<PositionComponent>();
	addComponent(position);

}

Entity::Entity(EntityType et) :
	id(0),
	type(et),
	deleted(false)
{
	position = std::make_shared<PositionComponent>();
	addComponent(position);

}

Entity::~Entity()
{
}

const Vector2f& Entity::getPosition() const
{
	 return position->getPosition();
}

void Entity::addComponent(std::shared_ptr<Components> comp) 
{
	ComponentID id = comp->getID();
	ComponentSet.turnOnBit(static_cast<unsigned int>(id));
}

bool Entity::hasComponent(Bitmask mask) const
{
	return ComponentSet.contains(mask);
}

std::shared_ptr<TTLComponent> Entity::getTTLComponent()
{
	return nullptr;
}

std::shared_ptr<InputComponent> Entity::getInputComponent()
{
	return nullptr;
}

std::shared_ptr<VelocityComponent> Entity::getVelocityComponent()
{
	return nullptr;
}

std::shared_ptr<PositionComponent> Entity::getPositionComponent()
{
	return position;
}

std::shared_ptr<GraphicsComponent> Entity::getGraphicsComponent()
{
	return graphics;
}

std::shared_ptr<PlayerState> Entity::getPlayerStateComponent()
{
	return nullptr;
}

std::shared_ptr<ColliderComponent> Entity::getColliderComponent()
{
	return nullptr;
}

void Entity::draw(Window* window)
{
	graphics->draw(window);
}

void Entity::init(const std::string& textureFile, float scale)
{
	graphics = std::make_shared<SpriteGraphicsComponent>(textureFile);
	addComponent(graphics);
	graphics->init(textureFile, scale);
}

void Entity::initSpriteSheet(const std::string& spriteSheetFile)
{
	graphics = std::make_shared<SpriteSheetGraphicsComponent>(spriteSheetFile);
	addComponent(graphics);
	graphics->initSpriteSheet(spriteSheetFile);
}

void Entity::setPosition(float x, float y)
{
	position->setPosition(x, y);
	graphics->setPosition(x, y);
}

