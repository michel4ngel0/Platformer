#pragma once

#include <SFML/Graphics.hpp>
#include "aabb-tree\aabb_tree.h"

class Entity : public sf::Sprite {
public:
	aabb get_bounding_box();
	void slide_out(Entity*);
};