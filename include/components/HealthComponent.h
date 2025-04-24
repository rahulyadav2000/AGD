

class HealthComponent : public Components{
protected:
	int currentHealth, maxHealth;

public:
	HealthComponent(int startingHealth, int maximumHealth) : currentHealth(startingHealth), maxHealth(maximumHealth) {};

	int getHealth() { return currentHealth; }

	void changeHealth(int h) {
		currentHealth += h;
		if (currentHealth > maxHealth) currentHealth = maxHealth;
		if (currentHealth < 0) currentHealth = 0;
	}

	virtual ComponentID getID() const override { return ComponentID::HEALTH; }
};