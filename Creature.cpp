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
	static auto box = getLocalBounds();
	sf::Vector2f position = getPosition();
	aabb below = { (double)position.x,
	                      (double)position.y + box.height,
	                      box.width,
	                      0.0 };
	std::cerr << below.x_ << " " << below.y_ << " " << below.x_size_ << " " << below.y_size_ << std::endl;

	bool airborne = true;
	auto iterator = scene->get_close_objects(below);
	for (; iterator.is_valid(); ++iterator) {
		static int counter = 0;
		counter++;
		if (&(*iterator) != this) {
			airborne = false;
			break;
		}
	}

	if (airborne) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			move(-100 * (float)dt, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			move(100 * (float)dt, 0);
		vy_ += 800.f * (float)dt;
	}
	else {
		vy_ = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			vy_ -= 400.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			move(-300 * (float)dt, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			move(300 * (float)dt, 0);
	}
	move(vx_ * (float)dt, vy_ * (float)dt);

	//	Collision deteciton
	aabb collision_box = { (double)position.x,
	                       (double)position.y,
	                       (double)box.width,
	                       (double)box.height };
	iterator = scene->get_close_objects(collision_box);
	for (; iterator.is_valid(); ++iterator) {
		if (&(*iterator) != this) {
			//
		}
	}

	scene->update_object(this);
}

void Dummy::step(Scene*, double dt) {

}