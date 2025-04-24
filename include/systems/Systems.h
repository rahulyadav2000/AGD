#pragma once
#include <iostream>
#include "../../include/entities/Entity.h"

class Game;

class Systems {
public:
	virtual void update(Game* game, Entity* entity, float elapsedTime) = 0;

	bool validate(Entity* entity) { return entity->hasComponent(componentMask); }
	virtual std::vector<EntityType> getArchetypesEntities() const = 0;

protected:
	Bitmask componentMask;
};

class TTLSystem : public Systems {
public:
	TTLSystem();
	virtual void update(Game* game, Entity* entity, float elapsedTime) override;
	virtual std::vector<EntityType> getArchetypesEntities() const override;
};

class InputSystem : public Systems {
public:
	InputSystem();
	virtual void update(Game* game, Entity* entity, float elapsedTime) override;
	virtual std::vector<EntityType> getArchetypesEntities() const override;
};

class MovementSystem : public Systems {
public:
	MovementSystem();
	virtual void update(Game* game, Entity* entity, float elapsedTime) override;
	virtual std::vector<EntityType> getArchetypesEntities() const override;
};

class GraphicsSystem : public Systems {
public:
	GraphicsSystem();
	virtual void update(Game* game, Entity* entity, float elapsedTime) override;
	virtual std::vector<EntityType> getArchetypesEntities() const override;
};

class ColliderSystem : public Systems {
public:
	ColliderSystem();
	virtual void update(Game* game, Entity* entity, float elapsedTime) override;
	virtual std::vector<EntityType> getArchetypesEntities() const override;
};

class GamePlaySystem : public Systems {
public:
	GamePlaySystem();
	virtual void update(Game* game, Entity* entity, float elapsedTime) override;
	virtual std::vector<EntityType> getArchetypesEntities() const override;
};

class PrintDebugSystem : public Systems {
public:
	PrintDebugSystem();
	virtual void update(Game* game, Entity* entity, float elapsedTime) override;
	virtual std::vector<EntityType> getArchetypesEntities() const override;
};