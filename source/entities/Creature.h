#pragma once

#include <SFML/Graphics.hpp>
#include "aabb-tree/aabb_tree.h"
#include "Entity.h"

class Scene;

class Creature : public Entity {
public:
	virtual void step(Scene*, double) = 0;
};