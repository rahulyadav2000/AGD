#include "../../include/graphics/SpriteSheet.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/Components.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/systems/Systems.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/core/Observer.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/PlayerStateComponent.h"

TTLSystem::TTLSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::TTL));
} 

void TTLSystem::update(Game* game, Entity* entity, float elapsedTime)
{
	std::shared_ptr<TTLComponent> ttlComponent = entity->getTTLComponent();

	if (!ttlComponent)
	{
		throw std::runtime_error("TTLComponent unavailable!");
	}
	else
	{
		ttlComponent->decreaseTTL();

		if (ttlComponent->getTTL() <= 0) {
			entity->deleteEntity();
		}
	}
}

std::vector<EntityType> TTLSystem::getArchetypesEntities() const
{
	return { EntityType::FIRE };
}