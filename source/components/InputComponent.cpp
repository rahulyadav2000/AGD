#include "../../include/graphics/Window.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/Components.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/InputComponent.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Subject.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Observer.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Player.h"
#include "../../include/core/Command.h"


PlayerInputComponent::PlayerInputComponent() {
	playerInput = std::make_unique<PlayerInputHandler>();
}


	
