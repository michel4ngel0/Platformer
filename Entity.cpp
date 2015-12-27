#include <cmath>
#include "Entity.h"

aabb Entity::get_bounding_box() {
	static auto box = getLocalBounds();
	auto position = getPosition();
	return { position.x,
		     position.y,
		     box.width,
	         box.height };
}

void Entity::slide_out(Entity* other) {
	//	TODO
	//	most likely can be done much faster
	constexpr float epsilon = 0.00001;

	auto my_box = get_bounding_box();
	auto other_box = other->get_bounding_box();
	
	if (!my_box.overlaps(other_box))
		return;

	sf::Vector2f my_center(my_box.x_ + my_box.x_size_ / 2,
		                   my_box.y_ + my_box.y_size_ / 2);

	sf::Vector2f other_center(other_box.x_ + other_box.x_size_ / 2,
		                      other_box.y_ + other_box.y_size_ / 2);
	
	float x_penetration = (my_box.x_size_ + other_box.x_size_) / 2 -
		                  fabs(my_center.x - other_center.x);
	float y_penetration = (my_box.y_size_ + other_box.y_size_) / 2 -
		                  (my_center.y - other_center.y);

	if (x_penetration < y_penetration) {
		if (my_center.x < other_center.x) {

			setPosition(other_box.x_ - my_box.x_size_ - epsilon, my_box.y_);
		}
		else if (my_center.x > other_center.x) {

			setPosition(other_box.x_ + other_box.x_size_ + epsilon, my_box.y_);
		}
	}
	else {
		if (my_center.y < other_center.y) {

			setPosition(my_box.x_, other_box.y_ - my_box.y_size_ - epsilon);
		}
		else if (my_center.y > other_center.y) {

			setPosition(my_box.x_, other_box.y_ + other_box.y_size_ + epsilon);
		}
	}
}