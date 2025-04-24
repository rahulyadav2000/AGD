#include "../../include/graphics/SpriteSheet.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/Components.h"
#include "../../include/components/GraphicsComponent.h"
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

InputSystem::InputSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::INPUT));
	componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
}

void InputSystem::update(Game* game, Entity* entity, float elapsedTime) {

	std::shared_ptr<VelocityComponent> velocityComponent = entity->getVelocityComponent();
	std::shared_ptr<InputComponent> inputComponent = entity->getInputComponent();

	velocityComponent->setVelocity(0.f, 0.f);
	auto& commands = inputComponent->getPlayerInput()->playerInputHandler();
	for (auto& c : commands) {
		c->execute(*game);
	}
}

std::vector<EntityType> InputSystem::getArchetypesEntities() const
{
	return { EntityType::PLAYER };
}