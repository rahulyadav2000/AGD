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

void AchievementManager::init(Game& game)
{
	game.getPlayer()->getPotionSubject().addObserver(this);
	game.getPlayer()->getShoutSubject().addObserver(this);
};

bool AchievementManager::onNotify(Events event)
{
	switch (event)
	{
	case (Events::PotionCollection):
	{
		++poitionCount;
		if (poitionCount == numberOfPotions)
			unlockAchievement(Achievements::PotionAchievement);
		return true;
		break;
	}

	case (Events::ShoutAction):
	{
		++shoutCount;
		if (shoutCount == numberOfShouts)
			unlockAchievement(Achievements::ShoutAchievement);
		return true;
		break;
	}
	}
	return false;
}

void AchievementManager::unlockAchievement(Achievements a)
{
	switch (a)
	{
	case (Achievements::PotionAchievement):
	{
		std::cout << "Player has collected all the potions, Achievement Unlocked!" << std::endl;
		break;
	}

	case (Achievements::ShoutAchievement):
	{
		std::cout << "Player has shouted five times, Achievement Unlocked!" << std::endl;
		break;
	}
	}	
}