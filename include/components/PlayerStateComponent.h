#pragma once
#include <iostream>
#include "../../include/entities/Player.h"


class Game;
class Entity;
class GraphicsComponent;
class Fire;


class PlayerStateComponent: public Components
{
public:
	virtual void update(Entity* entity, Game* game, float elapsed) = 0;
};

class PlayerState : public PlayerStateComponent {
public:
	PlayerState() : attacking(false), shouting(false), wood(0), shootCooldown(0) {}
	virtual void update(Entity* entity, Game* game, float elapsed) override;


	bool isAttacking() const { return attacking; }
	void setAttacking(bool at) { attacking = at; }

	bool isShouting() const { return shouting; }
	void setShouting(bool sh) { shouting = sh; }

	int getWood() const { return wood; }
	void addWood(int w);
	std::shared_ptr<Fire> createFire(Player& entity, std::shared_ptr<GraphicsComponent> graphics) const;
	virtual ComponentID getID() const override { return ComponentID::GAMEPLAY; }

	int shoutCount = 0;
	float shoutTimer = 0.0f;

protected:


	const int maxWood = 100;
	const int shootingCost = 20;
	const float fireSpeed = 200.f;
	const float shootCooldownTime = 3.f;

	int wood;
	bool attacking;
	bool shouting;
	float shootCooldown;
};
