#include <cmath>
#include <iostream>
#include "Entity.h"

aabb Entity::get_bounding_box() {
	auto box = getLocalBounds();
	auto position = getPosition();
	return { position.x,
		     position.y,
		     box.width,
	         box.height };
}

direction Entity::slide_out(Entity* other) {
	//	TODO
	//	most likely can be done much faster
	constexpr float epsilon = 0.00001f;

	auto my_box = get_bounding_box();
	auto other_box = other->get_bounding_box();
	
	if (!my_box.overlaps(other_box))
		return direction::none;

	sf::Vector2f my_center((float)(my_box.x_) + (float)(my_box.x_size_) / 2,
		                   (float)(my_box.y_) + (float)(my_box.y_size_) / 2);

	sf::Vector2f other_center((float)(other_box.x_) + (float)(other_box.x_size_) / 2,
		                      (float)(other_box.y_) + (float)(other_box.y_size_) / 2);
	
	float x_penetration = (float)(my_box.x_size_ + other_box.x_size_) / 2 -
		                  fabs(my_center.x - other_center.x);
	float y_penetration = (float)(my_box.y_size_ + other_box.y_size_) / 2 -
		                  fabs(my_center.y - other_center.y);

	if (x_penetration < y_penetration) {
		if (my_center.x < other_center.x) {
			setPosition((float)(other_box.x_ - my_box.x_size_ - epsilon), (float)my_box.y_);
			return direction::left;
		}
		else if (my_center.x > other_center.x) {
			setPosition((float)(other_box.x_ + other_box.x_size_ + epsilon), (float)my_box.y_);
			return direction::right;
		}
	}
	else {
		if (my_center.y < other_center.y) {
			setPosition((float)my_box.x_, (float)(other_box.y_ - my_box.y_size_ - epsilon));
			return direction::up;
		}
		else if (my_center.y > other_center.y) {
			setPosition((float)my_box.x_, (float)(other_box.y_ + other_box.y_size_ + epsilon));
			return direction::down;
		}
	}

	//	Shouldn't happen, really
	return direction::none;
}

void Entity::alert(int) {
	
}