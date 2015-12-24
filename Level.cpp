#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "types.h"
#include "Scene.h"
#include "Gui.h"
#include "Level.h"

Level::Level(const char* level_name) {
	std::fstream input_file(path_levels + level_name);
	std::cerr << "Loading level " << level_name << std::endl;

	player_ = nullptr;

	std::string word;
	float x, y;
	do {
		input_file >> word;

		if (word == "texture") {
			input_file >> word;
			sf::Texture* new_texture = new sf::Texture;
			new_texture->loadFromFile(path_textures + word);
			textures_.insert(std::make_pair(word, new_texture));
		}
		else if (word == "object") {
			input_file >> x >> y >> word;
			sf::Sprite* new_sprite = new sf::Sprite;
			new_sprite->setTexture(*(textures_[word.c_str()]));
			new_sprite->setPosition(x, y);
			scene_.insert_object(new_sprite);
			input_file >> word;
			if (word == "player") {
				if (player_ != nullptr)
					std::cerr << "Error: more than one controllable character" << std::endl;
				player_ = new_sprite;
			}
			else if (word == "mob") {
				mobs_.insert(new_sprite);
			}
			else if (word == "block") {

			}
		}

	} while (!input_file.eof());

	input_file.close();
}

Level::~Level() {
	for (auto& texture : textures_)
		delete texture.second;
}

void Level::step(double dt) {
	auto& objects = scene_.get_objects();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		player_->move(0, -200 * (float)dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		player_->move(0, 200 * (float)dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		player_->move(-200 * (float)dt, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		player_->move(200 * (float)dt, 0);

	scene_.update_object(player_);
}

void Level::draw(sf::RenderTarget& target) {
	/* TODO */
	aabb view;
	if (player_ != nullptr)
		view = { player_->getPosition().x - (800 - player_->getTextureRect().width) / 2,
		         player_->getPosition().y - (600 - player_->getTextureRect().height) / 2,
				 800,
	             600 };
	else
		view = { 0, 0, 800, 600 };

	scene_.draw_view(target, view);
	gui_.draw(target);
}