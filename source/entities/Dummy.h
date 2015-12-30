#pragma once

#include "Creature.h"

class Dummy : public Creature {
private:
	int frame_;
public:
	Dummy();
	virtual void step(Scene*, double);
	virtual void alert(int);
};
