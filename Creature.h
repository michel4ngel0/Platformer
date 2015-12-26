#pragma once

#include <SFML/Graphics.hpp>
#include "aabb-tree\aabb_tree.h"

class Scene;

class Creature : public sf::Sprite {
public:
	virtual void step(Scene*, double) = 0;
};

class Player : public Creature {
private:
	float vx_;
	float vy_;

public:
	Player();
	virtual void step(Scene*, double);
};

class Dummy : public Creature {
public:
	virtual void step(Scene*, double);
};