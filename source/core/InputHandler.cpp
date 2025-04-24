
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include <SFML/Graphics.hpp>

InputHandler::InputHandler()
{
	pauseCommand = std::make_shared<PauseCommand>();
}

PlayerInputHandler::PlayerInputHandler()
{
	rightMove = std::make_shared<MoveRightCommand>();
	leftMove = std::make_shared<MoveLeftCommand>();
	downMove = std::make_shared<MoveDownCommand>();
	upMove = std::make_shared<MoveUpCommand>();
	attackPlay = std::make_shared<AttackCommand>();
	shoutPlay = std::make_shared<ShoutCommand>();
	swapInputs = std::make_shared<SwitchInputCommand>();

	inputMode = InputMode::WASD;
}

std::shared_ptr<Command> InputHandler::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return pauseCommand;
	}
	else {
		return nullptr;
	}
}

void PlayerInputHandler::switchInputs()
{
	inputMode = (inputMode == InputMode::WASD) ? InputMode::CURSOR : InputMode::WASD;
}

std::vector<std::shared_ptr<Command>>& PlayerInputHandler::playerInputHandler()
{
	commands.clear();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		commands.push_back(swapInputs);
	}

	if (inputMode == InputMode::WASD)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			commands.push_back(rightMove);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			commands.push_back(leftMove);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			commands.push_back(upMove);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			commands.push_back(downMove);
		}
	}
	else if (inputMode == InputMode::CURSOR) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			commands.push_back(rightMove);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			commands.push_back(leftMove);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			commands.push_back(upMove);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			commands.push_back(downMove);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		commands.push_back(attackPlay);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		commands.push_back(shoutPlay);
	}

	return commands;
}


