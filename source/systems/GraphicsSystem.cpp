#include "../../include/graphics/SpriteSheet.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/Components.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/systems/Systems.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/core/Observer.h"
#include "../../include/core/Game.h"

GraphicsSystem::GraphicsSystem() {
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
	componentMask.turnOnBit(static_cast<int>(ComponentID::GRAPHICS));
}

void GraphicsSystem::update(Game* game, Entity* entity, float elapsedTime) {
	std::shared_ptr<PositionComponent> positionComponent = entity->getPositionComponent();
	std::shared_ptr<GraphicsComponent> graphicsComponent = entity->getGraphicsComponent();

	if (graphicsComponent == nullptr && positionComponent == nullptr)
	{
		throw std::runtime_error("Components unavailable!");
	}
	else {
		graphicsComponent->update(*entity, elapsedTime);
	}
}

std::vector<EntityType> GraphicsSystem::getArchetypesEntities() const
{
	return { EntityType::PLAYER , EntityType::FIRE, EntityType::LOG , EntityType::POTION };
}