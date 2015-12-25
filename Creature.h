#pragma once

#include <SFML/Graphics.hpp>

class Scene;

class Creature : public sf::Sprite {
public:
	virtual void step(Scene*, double) = 0;
};

class Player : public Creature {
public:
	virtual void step(Scene*, double);
};

class Dummy : public Creature {
public:
	virtual void step(Scene*, double);
};