#pragma once

#include "types.h"
#include <SFML/Graphics.hpp>

class Game {
private:
	static Game* singleton;
	static const unsigned int canvas_width = 320;
	static const unsigned int canvas_height = 240;
	static const int minimum_fps = 10;

	unsigned int scale_;
	game_state state_;

	Game();
	Game& operator=(const Game&) = delete;

public:
	static Game* get_game_object();
	~Game();

	int run();
};
