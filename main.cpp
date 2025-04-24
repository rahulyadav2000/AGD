#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "include/graphics/Window.h"
#include "include/graphics/SpriteSheet.h"
#include "include/components/Components.h"
#include "include/components/GraphicsComponent.h"
#include "include/components/VelocityComponent.h"
#include "include/utils/Rectangle.h"
#include "include/components/ColliderComponent.h"
#include "include/components/TTLComponent.h"
#include "include/core/InputHandler.h"
#include "include/components/InputComponent.h"
#include "include/utils/Bitmask.h"
#include "include/systems/Systems.h"
#include "include/core/Subject.h"
#include "include/entities/Entity.h"
#include "include/components/HealthComponent.h"
#include "include/components/PlayerStateComponent.h"
#include "include/core/Observer.h"
#include "include/core/Game.h"

void adaptiveLoop(Game& game, float& lastTime, float updateTarget = 0)
{
    float current = game.getElapsed().asSeconds();
    float elapsedSeconds = current - lastTime;

    // I.A: Three function calls for the game loop: handleInput, update and render.
    //   Update and Render are frame-dependent
    game.handleInput();
    game.update(elapsedSeconds); 
    game.render(elapsedSeconds); 

    // I.B: This loop is time-variable, set the game to sleep in order to get a 
    //      constant framerate.
    float currentTime = game.getElapsed().asSeconds();

    sf::Time timeSpent = sf::seconds(0.0);
    timeSpent = sf::seconds(current + updateTarget - currentTime);
    sf::sleep(timeSpent);

    // I.C: Calculate the current frame rate and set it to the game.
    float afterTime = game.getElapsed().asSeconds();

    lastTime = afterTime - current;
    int FPS = static_cast<int> (1 / lastTime);


    // I.D: Call the function game.setFPS(int) to inform the game about the current FPS. Print this value to console as well.
    std::cout << "Elapsed Time : " << lastTime << " " << " FPS : " << FPS << std::endl;
    std::cout << "TimeSpent: " << timeSpent.asSeconds() << std::endl;
    game.setFPS(FPS);

    lastTime = current;
}

int main(int argc, char** argv[])
{
    // Try to load the level:
    std::ifstream levelRead{ "levels/lvl0.txt" };
    if (!levelRead)
    {
        throw std::exception("File not found\n");
    }

    // Convert the read file into a vector of strings, one per line:
    std::vector<std::string> lines;
    while (levelRead)
    {
        std::string strInput;
        std::getline(levelRead, strInput);
        lines.emplace_back(strInput);
    }


    // Create and initalize the game.
    Game game;
    game.init(lines);

    // GAME LOOP (with an update target time at 60FPS)
    float updateTarget = 0.016f; //FPS: 60
    float lastTime = game.getElapsed().asSeconds();

    while (!game.getWindow()->isWindowDone())
    {
        //Adaptive loop to elapsed time, with a target update.
        adaptiveLoop(game, lastTime, updateTarget);
    }
    return 0;
}