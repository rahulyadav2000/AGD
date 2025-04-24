#pragma once
#include <iostream>
#include <vector>


class Command;
enum class InputMode {
	WASD,
	CURSOR
};

class InputHandler {

private:
	std::shared_ptr<Command> pauseCommand;

public:
	InputHandler();
	std::shared_ptr<Command> handleInput();
};

class PlayerInputHandler
{

private:
	std::vector<std::shared_ptr<Command>> commands;
	
	std::shared_ptr<Command> rightMove;
	std::shared_ptr<Command> leftMove;
	std::shared_ptr<Command> upMove;
	std::shared_ptr<Command> downMove;
	std::shared_ptr<Command> attackPlay;
	std::shared_ptr<Command> shoutPlay;
	std::shared_ptr<Command> swapInputs;

	InputMode inputMode;
public:
	PlayerInputHandler();
	std::vector<std::shared_ptr<Command>>& playerInputHandler();
	void switchInputs();
};