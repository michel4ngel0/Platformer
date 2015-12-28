#include <iostream>
#include <cmath>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include "Creature.h"
#include "Scene.h"
#include "aabb-tree\aabb_tree.h"

Player::Player() {
	vx_ = 0.f;
	vy_ = 0.f;
}

void Player::step(Scene* scene, double dt) {
	constexpr double epsilon = 0.001;

	auto box = getLocalBounds();
	sf::Vector2f position = getPosition();
	aabb below = { (double)position.x + 0.1 * box.width,
	               (double)position.y + box.height + epsilon,
	               (double)box.width * 0.8,
	               0.0 };

	bool airborne = true;
	auto iterator = scene->get_close_objects(below);
	for (; iterator.is_valid(); ++iterator) {
		if (iterator->get_bounding_box().overlaps(below)) {
			airborne = false;
			break;
		}
	}

	if (airborne) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			move(-200 * (float)dt, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			move(200 * (float)dt, 0);
		vy_ += 800.f * (float)dt;
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			vy_ = fmin(vy_, -400.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			move(-200 * (float)dt, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			move(200 * (float)dt, 0);
	}
	move(vx_ * (float)dt, vy_ * (float)dt);

	//	Collision deteciton
	aabb collision_box = { (double)position.x,
	                       (double)position.y,
	                       (double)box.width,
	                       (double)box.height };
	iterator = scene->get_close_objects(collision_box);
	for (; iterator.is_valid(); ++iterator) {
		if (&(*iterator) != this &&
			iterator->get_bounding_box().overlaps(get_bounding_box())) {
			direction slide = slide_out(&(*iterator));
			std::cerr << "dir: " << (int)slide << std::endl;
			if (slide == direction::left || slide == direction::right)
				vx_ = 0.f;
			if (slide == direction::up || slide == direction::down)
				vy_ = 0.f;
		}
	}

	scene->update_object(this);
}

void Dummy::step(Scene*, double dt) {

}