#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/Components.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/systems/Systems.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/entities/Entity.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/graphics/Window.h"
#include "../../include/core/Observer.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/utils/Vector2.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/core/AudioManager.h"
#include <iostream>



Player::Player() : Entity(EntityType::PLAYER)
{
	playerInput = std::make_shared<PlayerInputComponent>();
	addComponent(playerInput);

	healthComp = std::make_shared<HealthComponent>(startingHealth, maxHealth);

	velocity = std::make_shared<VelocityComponent>(playerSpeed);
	addComponent(velocity);

	cC = std::make_shared<ColliderComponent>();
	addComponent(cC);

	playerState = std::make_shared<PlayerState>();
	addComponent(playerState);
}

Player::~Player() {}



void Player::potionCollision(std::shared_ptr<Entity> entity, Game& game)
{
	Potion* potion = dynamic_cast<Potion*>(entity.get());
	if (potion) {
		
		getHealthComp()->changeHealth(potion->getHealth());
		potion->deleteEntity();

		AudioManager& audio = Locator::getAudioManager();
		audio.PlayPotionSound();
		std::cout << "Restored Health: " << potion->getHealth() << " Player Health: " << getHealthComp()->getHealth() << std::endl;
		getPotionSubject().notify(Events::PotionCollection);
	}
}

void Player::logCollision(std::shared_ptr<Entity> entity, Game& game)
{
	if (getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->getName() == "Attack" && 
		getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isInAction())
	{
		Log* log = dynamic_cast<Log*>(entity.get());
		if (log)
		{
			getPlayerStateComponent()->addWood(log->getWood());
			log->deleteEntity();
			std::cout << "Woods Collected!!" << std::endl;
		}
	}
	std::cout << "Collide with Log!" << std::endl;
}

std::shared_ptr<Fire> Player::createFire(Player& entity) const
{
	return playerState->createFire(entity, graphics);
}

std::shared_ptr<HealthComponent> Player::getHealthComp()
{
	return healthComp;
}

void Player::draw(Window* window)
{
	Entity::draw(window);
	cC->draw(window);
}

void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	graphics->positionSprite(row, col, spriteWH, tileScale, this);
	velocity->setVelocity(0.f, 0.f);
}

void Player::initSpriteSheet(const std::string& spriteSheetFile)
{
	Entity::initSpriteSheet(spriteSheetFile);
	auto size{ Vector2f(graphics->getSpriteSheet()->getSpriteSize().x * graphics->getSpriteSheet()->getSpriteScale().x,
		graphics->getSpriteSheet()->getSpriteSize().y * graphics->getSpriteSheet()->getSpriteScale().y) };
	cC->init(*this, size);
}

bool Player::collideWith(Entity& entity)
{
	std::shared_ptr<ColliderComponent> collider = getColliderComponent();
	if (collider != nullptr)
	{
		std::shared_ptr<ColliderComponent> otherCollider = entity.getColliderComponent();
		if (otherCollider != nullptr)
		{
			return collider->intersect(otherCollider);
		}
		return false;
	}
	return false;
}