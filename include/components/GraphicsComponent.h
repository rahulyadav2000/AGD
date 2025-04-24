#include <string>
#include <SFML/Graphics.hpp>


class SpriteSheet;
class Rectangle;
class Entity;
class Window;

class GraphicsComponent: public Components {
public:
	virtual ~GraphicsComponent() {}
	virtual void init(const std::string& textureFile, float scale) = 0;
	virtual void initSpriteSheet(const std::string& spriteSheetFile) = 0;
	virtual void draw(Window* window) = 0;
	virtual const sf::Vector2f& getSpriteScale() const = 0;
	virtual	sf::Vector2i getTextureSize() const = 0;
	virtual SpriteSheet* getSpriteSheet()  = 0;
	virtual sf::Sprite& getSprite() = 0;
	virtual bool isSpriteSheetEntity() const = 0;
	virtual void setPosition(float x, float y) = 0;
	virtual void update(Entity& entity, float elapsed) = 0;
	virtual void positionSprite(int row, int col, int spriteWH, float tileScale, Entity* entity) = 0;
	virtual ComponentID getID() const override { return ComponentID::GRAPHICS; }
};

class SpriteSheetGraphicsComponent : public GraphicsComponent {
public:
	SpriteSheetGraphicsComponent(const std::string& spriteSheetFile) {}
	virtual void initSpriteSheet(const std::string& spriteSheetFile) override;
	virtual void init(const std::string& textureFile, float scale) override;
	virtual const sf::Vector2f& getSpriteScale() const override;
	virtual	sf::Vector2i getTextureSize() const override;
	virtual SpriteSheet* getSpriteSheet() { return &spriteSheet; }
	virtual sf::Sprite& getSprite() { return sprite; }
	virtual bool isSpriteSheetEntity() const { return isSpriteSheet; }
	void setPosition(float x, float y) override;
	void draw(Window* window) override;
	void setAnimation(const std::string& name, bool play, bool loop);
	void setSpriteDirection(const Direction& dir) { spriteSheet.setSpriteDirection(dir); }
	virtual void update(Entity& entity, float elapsed) override;
	virtual void positionSprite(int row, int col, int spriteWH, float tileScale, Entity* entity) override;

protected:
	bool isSpriteSheet;
	SpriteSheet spriteSheet;
	sf::Texture texture;
	sf::Sprite sprite;
};

class SpriteGraphicsComponent : public GraphicsComponent {
public:
	SpriteGraphicsComponent(const std::string& simpleSprite) {}
	virtual void init(const std::string& textureFile, float scale) override;
	void setPosition(float x, float y) override;
	void draw(Window* window) override;
	virtual void update(Entity& entity, float elapsed) override;
	virtual void initSpriteSheet(const std::string& spriteSheetFile) override {}
	virtual const sf::Vector2f& getSpriteScale() const override;
	virtual	sf::Vector2i getTextureSize() const override;
	virtual sf::Sprite& getSprite() { return sprite; }
	virtual SpriteSheet* getSpriteSheet() override { return &spriteSheet; }
	virtual bool isSpriteSheetEntity() const override { return isSpriteSheet; }
	virtual void positionSprite(int row, int col, int spriteWH, float tileScale, Entity* entity) override;

protected:
	bool isSpriteSheet;
	SpriteSheet spriteSheet;
	sf::Sprite sprite;
	sf::Texture texture;
};

