#pragma once
#include <iostream>

class Fire;
class InputComponent;
class PlayerState;
class Subject;

class Player :  public Entity
{
public:

	const float playerSpeed = 100.f;
	const int startingHealth = 60;
	const int maxHealth = 100;

	Player();
	~Player();

	std::shared_ptr<HealthComponent> getHealthComp();

	bool hasSpriteSheet() const { return graphics->getSpriteSheet(); }

	void positionSprite(int row, int col, int spriteWH, float tileScale);
	virtual void initSpriteSheet(const std::string& spriteSheetFile) override;

	void draw(Window* window) override;

	bool collideWith(Entity& entity);

	virtual std::shared_ptr<InputComponent> getInputComponent() override { return playerInput; }
	virtual std::shared_ptr<VelocityComponent> getVelocityComponent() override { return velocity; }

	virtual std::shared_ptr<ColliderComponent> getColliderComponent() override { return cC; }
	virtual std::shared_ptr<PlayerState> getPlayerStateComponent() override { return playerState; }

	Subject& getPotionSubject() { return potionSub; }
	Subject& getShoutSubject() { return shoutSub; }
	
	void potionCollision(std::shared_ptr<Entity> entity, Game& game);
	void logCollision(std::shared_ptr<Entity> entity, Game& game);

private:

	std::shared_ptr<Fire> createFire(Player& entity) const;

	// VI.A (1/2): Declare a unique pointer to a player input handler.
	std::shared_ptr<InputComponent> playerInput;

	std::shared_ptr<HealthComponent> healthComp;
	std::shared_ptr<VelocityComponent> velocity;
	std::shared_ptr<ColliderComponent> cC;
	std::shared_ptr<PlayerState> playerState;

	Subject potionSub;
	Subject shoutSub;
};

