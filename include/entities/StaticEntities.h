#pragma once


class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION), cC{ std::make_shared<ColliderComponent>() } { addComponent(cC); }
	~Potion() {}

	void init(const std::string& textureFile, float scale) override
	{
		// III.C (1/2) Call the init() function in Entity to initalize this object
		Entity::init(textureFile, scale);

		// VIII.C (1/2) Set the top left and bottom right corners of the bounding box for this entity.
		auto size{ Vector2f(graphics->getTextureSize().x * graphics->getSpriteSheet()->getSpriteScale().x, graphics->getTextureSize().y * graphics->getSpriteSheet()->getSpriteScale().y) };
		cC->init(*this, size);
	}

	virtual void draw(Window* window) override
	{
		Entity::draw(window);
		cC->draw(window);
	}

	int getHealth() const { return potionHealth; }

	virtual std::shared_ptr<ColliderComponent> getColliderComponent() override { return cC; }

protected:
	const int potionHealth = 10;
	std::shared_ptr <ColliderComponent> cC;
};


class Log : public Entity
{
public:
	Log() : Entity(EntityType::LOG), cC{ std::make_shared<ColliderComponent>() } { addComponent(cC); }
	~Log() {}

	void init(const std::string& textureFile, float scale) override
	{
		// III.C (2/2) Call the init() function in Entity to initalize this object
		Entity::init(textureFile, scale);


		// VIII.C (2/2) Set the top left and bottom right corners of the bounding box for this entity.
		auto size{ Vector2f(graphics->getTextureSize().x * graphics->getSpriteSheet()->getSpriteScale().x, graphics->getTextureSize().y * graphics->getSpriteSheet()->getSpriteScale().y) };
		cC->init(*this, size);
	}


	virtual void draw(Window* window) override
	{
		Entity::draw(window);
		cC->draw(window);
	}

	int getWood() const { return woodAdded; }

	virtual std::shared_ptr<ColliderComponent> getColliderComponent() override { return cC; }

protected:
	const int woodAdded = 15;
	std::shared_ptr <ColliderComponent> cC;
};