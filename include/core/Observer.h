#pragma once
class Game;

enum class Events {
	PotionCollection,
	ShoutAction
};

enum class Achievements {
	PotionAchievement,
	ShoutAchievement
};

class Observer
{
public:
	virtual ~Observer() {}
	virtual bool onNotify(Events event) = 0;
};

class AchievementManager : public Observer
{
public:
	void init(Game& game);
	virtual bool onNotify(Events event) override;

private:
	int poitionCount = 0;
	int shoutCount = 0;
	int numberOfPotions = 6;
	int numberOfShouts = 5;
	void unlockAchievement(Achievements a);
};