#pragma once
#include "Observer.h"


class Subject 
{
public:
	void addObserver(Observer* o);
	void notify(Events events);

private:
	Observer* observer;
};
