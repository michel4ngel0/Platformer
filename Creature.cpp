#include <cmath>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include "Creature.h"
#include "Scene.h"
#include "aabb-tree\aabb_tree.h"

void Player::step(Scene* scene, double dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		move(0, -200 * (float)dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		move(0, 200 * (float)dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		move(-200 * (float)dt, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		move(200 * (float)dt, 0);

	scene->update_object(this);
}

void Dummy::step(Scene*, double dt) {

}