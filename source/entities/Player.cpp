#include "Player.h"
#include "../Scene.h"

void Player::update_texture() {

}

Player::Player() {
	vx_ = 0.f;
	vy_ = 0.f;

	setTextureRect(sf::IntRect(0, 0, 16, 16));
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

	if (!airborne) {
		setTextureRect(sf::IntRect(0, 0, 16, 16));
	}
	else {
		if (vy_ < -200.f)
			setTextureRect(sf::IntRect(0, 16, 16, 16));
		else if (vy_ > 200.f)
			setTextureRect(sf::IntRect(32, 16, 16, 16));
		else
			setTextureRect(sf::IntRect(16, 16, 16, 16));
	}

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
			if (slide == direction::left)
				vx_ = fmin(vx_, 0);
			if (slide == direction::right)
				vx_ = fmax(vx_, 0);
			if (slide == direction::up)
				vy_ = fmin(vy_, 0);
			if (slide == direction::down)
				vy_ = fmax(vy_, 0);
		}
	}

	scene->update_object(this);
}