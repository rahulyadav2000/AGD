#include "../../include/graphics/Window.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/Components.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/systems/Systems.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/core/Board.h"


void Subject::addObserver(Observer* o) {
	observer = o;
}


void Subject::notify(Events events) {
	observer->onNotify(events);
}
