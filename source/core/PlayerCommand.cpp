#include "../../include/core/Command.h"
#include "../../include/core/Board.h"
#include "../../include/graphics/SpriteSheet.h"
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
#include "../../include/components/HealthComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/core/Observer.h"
#include "../../include/core/Game.h"
#include "../../include/core/AudioManager.h"
#include <iostream>

void MoveRightCommand::execute(Game& game)
{
	game.getPlayer()->getVelocityComponent()->setVelocity(1.0f, game.getPlayer()->getVelocityComponent()->getVelocity().y);
}

void MoveLeftCommand::execute(Game& game)
{
	game.getPlayer()->getVelocityComponent()->setVelocity(-1.0f, game.getPlayer()->getVelocityComponent()->getVelocity().y);
}

void MoveUpCommand::execute(Game& game)
{
	game.getPlayer()->getVelocityComponent()->setVelocity(game.getPlayer()->getVelocityComponent()->getVelocity().x, -1.0f);
}

void MoveDownCommand::execute(Game& game)
{
	game.getPlayer()->getVelocityComponent()->setVelocity(game.getPlayer()->getVelocityComponent()->getVelocity().x, 1.0f);
}

void AttackCommand::execute(Game& game)
{
	AudioManager& audio = Locator::getAudioManager();
	game.getPlayer()->getPlayerStateComponent()->setAttacking(true);
	if (game.getPlayer()->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isInAction()) {
		audio.PlayAxeSound();
	}
}

void ShoutCommand::execute(Game& game)
{
	if (!game.getPlayer()->getPlayerStateComponent()->isShouting()) {
		game.getPlayer()->getPlayerStateComponent()->setShouting(true);
		game.getPlayer()->getShoutSubject().notify(Events::ShoutAction);
	}
}

void SwitchInputCommand::execute(Game& game)
{
	auto inputComp = game.getPlayer()->getInputComponent();
	inputComp->getPlayerInput()->switchInputs();
}