#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/Components.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/systems/Systems.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/graphics/Window.h"
#include "../../include/core/Observer.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"
#include "../../include/utils/Vector2.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/entities/Entity.h"

void PlayerState::update(Entity* entity, Game* game, float elapsed)
{
	auto player = dynamic_cast<Player*>(entity);

	if (isAttacking())
	{
		player->getGraphicsComponent()->getSpriteSheet()->setAnimation("Attack", true, false);
	}
	else if (isShouting())
	{
		player->getGraphicsComponent()->getSpriteSheet()->setAnimation("Shout", true, false);
	}
	else if (player->getVelocityComponent()->getVelocity().x > 0)
	{
		player->getGraphicsComponent()->getSpriteSheet()->setAnimation("Walk", true, true);
		player->getGraphicsComponent()->getSpriteSheet()->setSpriteDirection(Direction::Right);
	}
	else if (player->getVelocityComponent()->getVelocity().x < 0)
	{
		player->getGraphicsComponent()->getSpriteSheet()->setAnimation("Walk", true, true);
		player->getGraphicsComponent()->getSpriteSheet()->setSpriteDirection(Direction::Left);
	}
	else if (player->getVelocityComponent()->getVelocity().y != 0)
	{
		player->getGraphicsComponent()->getSpriteSheet()->setAnimation("Walk", true, true);
	}
	else {
		player->getGraphicsComponent()->getSpriteSheet()->setAnimation("Idle", true, true);
	}



	if (shootCooldown > 0) {
		shootCooldown -= elapsed;
	}

	if (player->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->getName() == "Shout" && player->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isInAction() && wood >= shootingCost && shootCooldown <= 0)
	{
		game->addEntity(createFire(*player, entity->getGraphicsComponent()));
		wood -= shootingCost;

		shootCooldown = shootCooldownTime;
	}

	if (attacking && !player->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isPlaying())
	{
		attacking = false;
	}

	if (shouting && !player->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isPlaying())
	{
		shouting = false;
	}


}

void PlayerState::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
}

std::shared_ptr<Fire> PlayerState::createFire(Player& entity, std::shared_ptr<GraphicsComponent> graphics) const
{
	auto fireEntity = std::make_shared<Fire>();

	Vector2f pos{ entity.getPosition().x + graphics->getTextureSize().x * 0.5f, entity.getPosition().y + graphics->getTextureSize().y * 0.5f };
	fireEntity->init("img/fire.png", 1.0f);
	fireEntity->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.f);
	if (graphics->getSpriteSheet()->getSpriteDirection() == Direction::Left) vel.x = vel.x * -1.0f;
	auto fireVelocity = fireEntity->getVelocityComponent();
	fireVelocity->setVelocity(vel.x, vel.y);

	return fireEntity;
}
