#pragma once

#include <set>
#include <map>
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Gui.h"

class Creature;
class Camera;

class Level {
private:
	Scene scene_;
	Gui gui_;
	Camera* camera_;
	std::map<std::string, sf::Texture*> textures_;
	std::set<Creature*> creatures_;
	float window_width_;
	float window_height_;

public:
	Level(const char*, float, float);
	~Level();

	void step(double dt);
	void draw(sf::RenderTarget&);
};