#pragma once

#include <SFML/Graphics.hpp>
#include "aabb-tree\aabb_tree.h"
#include "types.h"

class Entity : public sf::Sprite {
public:
	aabb get_bounding_box();
	direction slide_out(Entity*);
	virtual void alert(int);
};