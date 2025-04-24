#include "../../include/components/TTLComponent.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/AudioManager.h"
#include <iostream>

Fire::Fire() : Entity(EntityType::FIRE)
{
	ttlComponent = std::make_shared<TTLComponent>(startTimeToLive);
	addComponent(ttlComponent);

	velComp = std::make_shared<VelocityComponent>();
	addComponent(velComp);

	AudioManager& audio = Locator::getAudioManager();
	audio.PlayFireSound();
}

Fire::~Fire()
{}

std::shared_ptr<VelocityComponent> Fire::getVelocityComponent() {
	return velComp;
}

std::shared_ptr<TTLComponent> Fire::getTTLComponent()
{
	return ttlComponent;
}
