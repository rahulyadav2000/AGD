#include "../../include/graphics/SpriteSheet.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/Components.h"
#include "../../include/components/GraphicsComponent.h"
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

GamePlaySystem::GamePlaySystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::GAMEPLAY));
}

void GamePlaySystem::update(Game* game, Entity* entity, float elapsedTime) {
	std::shared_ptr<PlayerState> playerStateComponent = entity->getPlayerStateComponent();
	
	if (playerStateComponent == nullptr)
	{
		throw std::runtime_error("Component unavailable!");
	}
	else
		playerStateComponent->update(entity, game, elapsedTime);
}

std::vector<EntityType> GamePlaySystem::getArchetypesEntities() const
{
	return { EntityType::PLAYER , EntityType::FIRE, EntityType::LOG , EntityType::POTION };
}