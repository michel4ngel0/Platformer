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

	std::string word;
	float x, y;
	do {
		input_file >> word;

		if (word == "texture") {
			input_file >> word;
			sf::Texture* new_texture = new sf::Texture;
			new_texture->loadFromFile(path_textures + word);
			textures_.insert(std::make_pair(word.c_str(), new_texture));
		}
		else if (word == "object") {
			input_file >> x >> y >> word;
			sf::Sprite* new_sprite = new sf::Sprite;
			new_sprite->setTexture(*(textures_[word.c_str()]));
			new_sprite->setPosition(x, y);
			scene_.insert_object(new_sprite);
		}

	} while (!input_file.eof());
}

Level::~Level() {
	for (auto& texture : textures_)
		delete texture.second;
}

void Level::step(double dt) {
	auto& objects = scene_.get_objects();
}

void Level::draw(sf::RenderTarget& target) {
	/* TODO */
	aabb view = { 100, 100, 500, 500 };

	scene_.draw_view(target, view);
	gui_.draw(target);
}