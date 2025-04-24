#include <functional>

class Observer;
class InputHandler;
class Window;
class Board;
class Player;

enum class ECSType {
	BIGARRAY,
	ARCHETYPE
};

class Game 
{

public:

	const int spriteWH = 50;
	const float tileScale = 2.0f;
	const float itemScale = 1.0f;

	Game();
	~Game();

	void init(std::vector<std::string> lines);
	void addEntity(std::shared_ptr<Entity> newEntity);

	void buildBoard(size_t width, size_t height);
	void initWindow(size_t width, size_t height);

	void handleInput();
	void update(float elapsed);
	void render(float elapsed);
	Window* getWindow() { return &window; }

	sf::Time getElapsed() const;
	void setFPS(int FPS);
	void togglePause() { paused = !paused; }
	bool isPaused() const { return paused; }

	//  IV.A (2/2) Write a function that returns the shared pointer of the player of the game.
	std::shared_ptr<Player> getPlayer() { return player; }

	EntityID getIDCounter();
	std::shared_ptr<Entity> getEntity(unsigned int idx);

	template <typename T>
	std::shared_ptr<T> buildEntityAt(const std::string& filename, int col, int row);

	void bigArray(float elapsed, std::vector<std::shared_ptr<Systems>> sys);

	void archetypes(float elasped, std::vector<std::shared_ptr<Systems>> systems);

	const std::vector<std::shared_ptr<Entity>>& getPlayerArchetype() const { return playerEntityArchetype; }
	const std::vector<std::shared_ptr<Entity>>& getFireArchetype() const { return fireEntityArchetype; }
	const std::vector<std::shared_ptr<Entity>>& getStaticArchetype() const { return staticEntitiesArchetype; }

private:

	Window window;
	bool paused;
	sf::Clock gameClock;
	sf::Time elapsed;

	// II.A Declare a unique pointer of type Board 
	std::unique_ptr<Board> board;

	// III.D Declare a vector from the standard template library that 
	//       contains shared pointers to Entity classes. Recommended name: entities.
	std::vector<std::shared_ptr<Entity>> entities;

	// III.E Declare a variable of type EntityID (which is declared in Entity.h). This variable will
	//       be incremented by one every time an entity is added to the game.
	EntityID id;

	
	// IV.A (1/2) Declare a pointer to a player object. The pointer must be shared pointer from the standard library.
	std::shared_ptr<Player> player;

	// V.A Declare a unique pointer to an Input Handler object for this class.
	std::unique_ptr<InputHandler> inputHandler;
	std::vector <std::shared_ptr<Systems>> logSystem;
	std::vector<std::shared_ptr<Systems>> graphicSystem;

	AchievementManager achievementManager;

	std::vector <std::shared_ptr<Entity>> playerEntityArchetype;
	std::vector<std::shared_ptr<Entity>> fireEntityArchetype;
	std::vector<std::shared_ptr<Entity>> staticEntitiesArchetype;
	ECSType ecsTypes;

	std::map<EntityType, std::function<void(std::shared_ptr<Entity>, Game&)>> collisionCallbacks;
};

