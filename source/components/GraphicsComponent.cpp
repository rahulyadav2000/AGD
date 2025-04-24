#include "../../include/graphics/SpriteSheet.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/Components.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/InputComponent.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/systems/Systems.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/PlayerStateComponent.h"

void SpriteSheetGraphicsComponent::initSpriteSheet(const std::string& spriteSheetFile)
{
	spriteSheet.loadSheet(spriteSheetFile);
	isSpriteSheet = true;
	spriteSheet.setAnimation("Idle", true, true);
}

void SpriteSheetGraphicsComponent::init(const std::string& textureFile, float scale)
{
	texture.loadFromFile(textureFile);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}

void SpriteSheetGraphicsComponent::setPosition(float x ,float y)
{
	spriteSheet.getSprite().setPosition(x, y);
}

void SpriteGraphicsComponent::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void SpriteGraphicsComponent::init(const std::string& textureFile, float scale)
{
	texture.loadFromFile(textureFile);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}
void SpriteGraphicsComponent::draw(Window* window)
{
	window->draw(sprite);
}

void SpriteSheetGraphicsComponent::draw(Window* window)
{
	sf::Sprite* sp = &spriteSheet.getSprite();
	const sf::Vector2f pos = sp->getPosition();
	window->draw(spriteSheet.getSprite());
}

void SpriteGraphicsComponent::update(Entity& entity, float elapsed)
{
	sprite.setPosition(entity.getPosition().x, entity.getPosition().y);
}

void SpriteSheetGraphicsComponent::positionSprite(int row, int col, int spriteWH, float tileScale, Entity* entity)
{
	sf::Vector2f scaleV2f = getSpriteScale();
	sf::Vector2i textureSize = getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally

	entity->setPosition(x + cntrFactorX, y + cntrFactorY);
}

void SpriteGraphicsComponent::positionSprite(int row, int col, int spriteWH, float tileScale, Entity* entity)
{
	sf::Vector2f scaleV2f = getSpriteScale();
	sf::Vector2i textureSize = getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally

	entity->setPosition(x + cntrFactorX, y + cntrFactorY);
}

void SpriteSheetGraphicsComponent::update(Entity& entity, float elapsed)
{
	spriteSheet.getSprite().setPosition(entity.getPosition().x, entity.getPosition().y);
	spriteSheet.update(elapsed);

}
void SpriteSheetGraphicsComponent::setAnimation(const std::string& name, bool play, bool loop)
{
	spriteSheet.setAnimation(name, play, loop);
}


const sf::Vector2f& SpriteSheetGraphicsComponent::getSpriteScale() const
{
	return spriteSheet.getSpriteScale();
}

sf::Vector2i SpriteSheetGraphicsComponent::getTextureSize() const
{
	return spriteSheet.getSpriteSize();
}

sf::Vector2i SpriteGraphicsComponent::getTextureSize() const
{
	return { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) };
}

const sf::Vector2f& SpriteGraphicsComponent::getSpriteScale() const
{
	return sprite.getScale();
}