#pragma once
#include <iostream>

using EntityID = unsigned int;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3
};

class Game; //forward declaration
class PositionComponent;
class PlayerState;

class Entity
{
public:

	//Constructors and Desctrutors
	Entity();
	Entity(EntityType et);
	~Entity();

	//Init and update functions
	virtual void init(const std::string& textureFile, float scale);
	virtual void initSpriteSheet(const std::string& spriteSheetFile);
	virtual void draw(Window* window);
	
	void addComponent(std::shared_ptr<Components> comp);

	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	void setPosition(float x, float y);
	
	const Vector2f& getPosition() const;
	
	EntityType getEntityType() const { return type; }

	Bitmask getComponentSet() const { return ComponentSet; }
	bool hasComponent(Bitmask mask) const;

	virtual std::shared_ptr<TTLComponent> getTTLComponent();
	virtual std::shared_ptr<InputComponent> getInputComponent();
	virtual std::shared_ptr<VelocityComponent> getVelocityComponent();
	virtual std::shared_ptr<PositionComponent> getPositionComponent();
	virtual std::shared_ptr<GraphicsComponent> getGraphicsComponent();
	virtual std::shared_ptr<PlayerState> getPlayerStateComponent();
	virtual std::shared_ptr<ColliderComponent> getColliderComponent();
	
	bool isDeleted() const { return deleted; } 
	void deleteEntity() { deleted = true; }

protected:

	EntityType type;
	EntityID id;

	Bitmask ComponentSet;

	std::shared_ptr<PositionComponent> position;
	bool deleted;

	std::shared_ptr<GraphicsComponent> graphics;

};