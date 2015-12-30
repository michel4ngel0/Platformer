#pragma once

#include "Creature.h"

class Floaty : public Creature {
private:
	float vx_;
	float vy_;
public:
	Floaty();
	virtual void step(Scene*, double);
	virtual void alert(int);
};