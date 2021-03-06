#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "types.h"
#include "Scene.h"
#include "Gui.h"
#include "Level.h"
#include "entities\Creature.h"
#include "entities\Player.h"
#include "entities\Dummy.h"
#include "entities\Floaty.h"
#include "Camera.h"

Level::Level(const char* level_name, float window_width, float window_height) :
	window_width_(window_width), window_height_(window_height) {

	camera_ = new CameraStationary(0, 0, window_width_, window_height_);

	std::fstream input_file(path_levels + level_name);
	std::cerr << "Loading level " << level_name << std::endl;

	std::string type, texture, creature_type;
	float x, y;
	do {
		input_file >> type;

		if (type == "texture") {
			input_file >> texture;
			sf::Texture* new_texture = new sf::Texture;
			new_texture->loadFromFile(path_textures + texture);
			textures_.insert(std::make_pair(texture, new_texture));
		}
		else if (type == "creature") {
			input_file >> x >> y >> texture >> creature_type;
			Creature* new_creature = nullptr;
			if (creature_type == "player") {
				new_creature = new Player;
				delete camera_;
				camera_ = new CameraFollower(new_creature, window_width_, window_height_);
			}
			else if (creature_type == "dummy") {
				new_creature = new Dummy;
			}
			else if (creature_type == "floaty") {
				new_creature = new Floaty;
			}

			if (new_creature == nullptr)
				continue;

			if (textures_.find(texture) == textures_.end()) {
				std::cerr << "Texture not found: " << texture << std::endl;
				continue;
			}

			new_creature->setTexture(*(textures_[texture]));
			new_creature->setPosition(x, y);
			scene_.insert_object(new_creature);
			creatures_.insert(new_creature);
		}
		else if (type == "tile") {
			input_file >> x >> y >> texture;
			Entity* new_tile = new Entity;
			new_tile->setTexture(*(textures_[texture]));
			new_tile->setPosition(x, y);
			scene_.insert_object(new_tile);
		}

	} while (!input_file.eof());

	input_file.close();
}

Level::~Level() {
	for (auto& texture : textures_)
		delete texture.second;

	delete camera_;
}

void Level::step(double dt) {
	for (auto& creature : creatures_)
		creature->step(&scene_, dt);
}

void Level::draw(sf::RenderTarget& target) {
	aabb view = camera_->get_view();

	scene_.draw_view(target, view);
	gui_.draw(target);
}