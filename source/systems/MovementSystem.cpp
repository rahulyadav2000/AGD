#include "../../include/graphics/SpriteSheet.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/Components.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/systems/Systems.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/core/Observer.h"
#include "../../include/core/Game.h"

MovementSystem::MovementSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
}

void MovementSystem::update(Game* game, Entity* entity, float elapsedTime)
{
	std::shared_ptr<VelocityComponent> velocityComponent = entity->getVelocityComponent();
	std::shared_ptr<PositionComponent> positionComponent = entity->getPositionComponent();

	positionComponent->setPosition(positionComponent->getPosition().x + (velocityComponent->getVelocity().x * velocityComponent->getSpeed() * elapsedTime),
		positionComponent->getPosition().y + (velocityComponent->getVelocity().y * velocityComponent->getSpeed() * elapsedTime));
}

std::vector<EntityType> MovementSystem::getArchetypesEntities() const
{
	return { EntityType::PLAYER , EntityType::FIRE };
}