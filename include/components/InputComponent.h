#include <iostream>

class Game;
class PlayerInputHandler;

class InputComponent : public Components {
public:
	virtual ~InputComponent() {}

	virtual ComponentID getID() const override { return ComponentID::INPUT; }
	virtual std::shared_ptr<PlayerInputHandler> getPlayerInput() = 0;
};


class PlayerInputComponent : public InputComponent {
public:
	PlayerInputComponent();
	virtual std::shared_ptr<PlayerInputHandler> getPlayerInput() override { return playerInput; }
private:
	std::shared_ptr<PlayerInputHandler> playerInput;
};