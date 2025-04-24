#pragma once

class VelocityComponent;

class Fire : public Entity
{
public:
	const int startTimeToLive = 150; //frames

	Fire();
	~Fire();

	virtual std::shared_ptr<VelocityComponent> getVelocityComponent() override;
	virtual std::shared_ptr<TTLComponent> getTTLComponent() override;

	
private:

	std::shared_ptr<TTLComponent> ttlComponent;
	std::shared_ptr<VelocityComponent> velComp;
};

