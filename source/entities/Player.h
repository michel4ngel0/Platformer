#pragma once

#include "Creature.h"

class Player : public Creature {
private:
	float vx_;
	float vy_;

	void update_texture();
public:
	Player();
	virtual void step(Scene*, double);
};