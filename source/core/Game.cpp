#include "../../include/graphics/Window.h"
#include "../../include/core/Board.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/Components.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/utils/Bitmask.h"
#include "../../include/systems/Systems.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Observer.h"
#include "../../include/core/Game.h"
#include "../../include/core/AudioManager.h"
#include <iostream>
#include <vector>

Game::Game() : paused(false), id{ 0 }, ecsTypes{ECSType::ARCHETYPE}
{
	inputHandler = std::make_unique<InputHandler>();

	std::shared_ptr<Systems> inputSystem = std::make_shared<InputSystem>();
	logSystem.push_back(inputSystem);

	std::shared_ptr<Systems> movementSystem = std::make_shared<MovementSystem>();
	logSystem.push_back(movementSystem);

	std::shared_ptr<Systems> graphicsSystem = std::make_shared<GraphicsSystem>();
	graphicSystem.push_back(graphicsSystem);

	std::shared_ptr<Systems> printDebugSystem = std::make_shared<PrintDebugSystem>();
	graphicSystem.push_back(printDebugSystem);

	std::shared_ptr<Systems> colliderSystem = std::make_shared<ColliderSystem>();
	logSystem.push_back(colliderSystem);

	std::shared_ptr<Systems> gamePlaySystem = std::make_shared<GamePlaySystem>();
	logSystem.push_back(gamePlaySystem);
	
	std::shared_ptr<Systems> ttlSytem = std::make_shared<TTLSystem>();
	logSystem.push_back(ttlSytem);
}

Game::~Game()
{
}

template <typename T>
std::shared_ptr<T> Game::buildEntityAt(const std::string& filename, int col, int row)
{
	auto ent = std::make_shared<T>();
	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;

	ent->init(filename, itemScale);

	ent->setPosition(x + cntrFactor, y + cntrFactor);

	return ent;
}

void Game::buildBoard(size_t width, size_t height)
{
	// II.B Instantiate the unique pointer of type "Board". 
	//     Use the constructor of Board that receives the width and the height for the game grid.
	board = std::make_unique<Board>(width, height);

}

void Game::initWindow(size_t width, size_t height)
{
	int wdt = static_cast<int>(width * spriteWH * tileScale);
	int hgt = static_cast<int>(height * spriteWH * tileScale);
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::init(std::vector<std::string> lines)
{
	// Make sure that the vector of lines is not emtpy. h is the number of lines (height of the level)
	size_t h = lines.size() - 1;
	if (h < 0)
		throw std::exception("No data in level file");
	size_t w = -1;

	// Load the font for the window and set its title
	window.loadFont("font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");
	
	auto it = lines.cbegin();
	int row = 0;
	while (it != lines.cend())
	{
		int col = 0;

		// First iteration: we determine the width of the level (w) by the number of symbols in the first line.
		if(w == -1)
		{
			//The size of the window must be equal to the number of tiles it has, factoring their dimensions.
			w = it->size();
			buildBoard(w, h);
			initWindow(w, h);		
		}
		
		std::string::const_iterator is = it->cbegin();
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.':
			{
				// II.C (1/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				//      The parameters are the column (for x) and row (for y) where the tile is to be placed, the scale 
				//      of the tile (you can use the variable "tileScale") and the tile type. TileTypes are 
				//      defined in the enumerator TileType in Tile.h. You DON'T need to pass a filename parameter for the texture.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case 'w':
			{
				// II.C (2/5) Use the function addTile from Board to add a WALL tile to this position.
				board->addTile(col, row, tileScale, TileType::WALL);
				break;
			}
			case 'x':
			{
				/// III.A Call the function "buildEntityAt" to create a Log pointer. The parameters are the filename to 
				///       the file with the sprite ("img/log.png"), the column and the row where the log should be place.
				///		  Then, uncomment the call to the funcion "addEntity" passing the pointer to the new entity as parameter.
				
				std::shared_ptr<Log> logPtr = buildEntityAt<Log> ("img/log.png", col, row);

				addEntity(logPtr);			/// uncomment this (you may have to change "ent" for the name of the pointer you've just created above).

				//By default, entities stand on corridors
				// II.C (3/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'p':
			{

				/// III.B Call the function "buildEntityAt" to create a Potion pointer. The parameters are the filename to 
				///       the file with the sprite ("img/potion.png"), the column and the row where the potion should be place.
				///		  Then, uncomment the call to the funcion "addEntity" passing the pointer to the new entity as parameter.
				
				std::shared_ptr<Potion> potionPtr = buildEntityAt<Potion>("img/potion.png", col, row);
				addEntity(potionPtr);			/// uncomment this
	
				//By default, entities stand on corridors
				// II.C (4/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case '*':
				{

				// IV.B (1/4): Create the player shared pointer.
				player = std::make_shared<Player>();

				// IV.B (2/4): Call the function that initializes the Sprite Sheet with a single parameter, a const std::string& filename.
				//			   This string should be "img/DwarfSpriteSheet_data.txt"
				player->initSpriteSheet("img/DwarfSpriteSheet_data.txt");

				// IV.B (3/4): Call the function that positions the sprite of the player in the board (Player::positionSprite). 
				//			   Parameters are the row and column where this object goes in the board, the sprite width and height (const int Game::spriteWH) 
				//			   and the scale for the tiles (const float Game::tileScale)
				player->positionSprite(row, col, spriteWH, tileScale);

				// IV.B (4/4): Call our function to add an entity to a game passing the player that has just been created.

				addEntity(player);
				//By default, entities stand on corridors:
				// II.C (5/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
				}
			}

			col++; is++;
		}
		row++; it++;
	}
	achievementManager.init(*this);

	collisionCallbacks[EntityType::LOG] = std::bind(&Player::logCollision, player.get(), std::placeholders::_1, std::placeholders::_2);
	collisionCallbacks[EntityType::POTION] = std::bind(&Player::potionCollision, player.get(), std::placeholders::_1, std::placeholders::_2);
}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
	id++;
	newEntity->setID(id);
	entities.push_back(newEntity);

	switch (newEntity->getEntityType())
	{
	case EntityType::PLAYER:
		playerEntityArchetype.push_back(std::dynamic_pointer_cast <Entity>(newEntity));
		break;

	case EntityType::FIRE:
		fireEntityArchetype.push_back(std::dynamic_pointer_cast<Entity>(newEntity));
		break;

	case EntityType::LOG:
		staticEntitiesArchetype.push_back(std::dynamic_pointer_cast<Entity>(newEntity));
		break;

	case EntityType::POTION:
		staticEntitiesArchetype.push_back(std::dynamic_pointer_cast<Entity>(newEntity));
		break;
	}
}

void Game::handleInput()
{
	std::shared_ptr<Command> command = inputHandler->handleInput();
	if (command) { 
		command->execute(*this);
	}
}


void Game::update(float elapsed)
{
	if (!paused) {

		switch (ecsTypes)
		{
		case ECSType::BIGARRAY:
			bigArray(elapsed, logSystem);
			break;
		case ECSType::ARCHETYPE:
			archetypes(elapsed, logSystem);
			break;
		}

		auto ite = entities.begin();
		while (ite != entities.end())
		{
			if (player->collideWith(*ite->get()))
			{
				switch ((*ite)->getEntityType())
				{
				case EntityType::POTION: {
					collisionCallbacks[EntityType::POTION](*ite, *this);
					break;
				}

				case EntityType::LOG: {
					collisionCallbacks[EntityType::LOG](*ite, *this);
					break;
				}
				default:
					break;
				}
			}
			ite++;
		}

		
		ite = entities.begin();
		while (ite != entities.end())
		{
			if ((*ite)->isDeleted())
			{
				ite = entities.erase(ite);
			}
			else {
				++ite;
			}
		}

	}

	window.update();
}

void Game::render(float elapsed)
{
	window.beginDraw();

	board->draw(&window); 
	
	switch (ecsTypes)
	{
	case ECSType::BIGARRAY:
		bigArray(elapsed, graphicSystem);
		break;
	case ECSType::ARCHETYPE:
		archetypes(elapsed, graphicSystem);
		break;
	}

	
	for (auto& e : entities) { 
		e->draw(&window);
	}

	window.drawGUI(*this);

	window.endDraw();
}


sf::Time Game::getElapsed() const { return gameClock.getElapsedTime(); }


void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

EntityID Game::getIDCounter()
{
	return id; 
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{
	if (idx >= entities.size()) 
	{
		return nullptr;
	}

	return entities[idx];
}

void Game::bigArray(float elapsed, std::vector<std::shared_ptr<Systems>> sys)
{
	auto SystemIte = sys.begin();
	while (SystemIte != sys.end())
	{
		auto entIte = entities.begin();
		while (entIte != entities.end())
		{
			if (!(*entIte)->isDeleted() && (*SystemIte)->validate(entIte->get()))
			{
				(*SystemIte)->update(this, entIte->get(), elapsed);
			}
			entIte++;
		}
		SystemIte++;
	}
}

void Game::archetypes(float elapsed, std::vector<std::shared_ptr<Systems>> systems)
{
	for (const auto& system : systems)
	{
		const std::vector<EntityType>& archetypes = system->getArchetypesEntities();
		for (const auto& entity : entities)
		{
			if (!entity->isDeleted() && std::find(archetypes.begin(), archetypes.end(), entity->getEntityType()) != archetypes.end() && system->validate(entity.get()))
			{
				system->update(this, entity.get(), elapsed);
			}
		}
	}
}

