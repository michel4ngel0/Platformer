#pragma once

#include <set>
#include <map>
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Gui.h"

class Level {
private:
	Scene scene_;
	Gui gui_;
	std::map<const char*, sf::Texture*> textures_;

public:
	Level(const char*);
	~Level();

	void step(double dt);
	void draw(sf::RenderTarget&);
};