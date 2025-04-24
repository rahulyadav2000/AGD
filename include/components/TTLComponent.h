#include "Components.h" 

class TTLComponent : public Components{
public:
	TTLComponent(int timeToLive) : ttl(timeToLive) {};

	int getTTL() const { return ttl; }
	int decreaseTTL() { return --ttl; }
	virtual ComponentID getID() const override { return ComponentID::TTL; }
private:
	int ttl;
};