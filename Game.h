#pragma once

#include "types.h"
#include <SFML/Graphics.hpp>

class Game {
private:
	static Game* singleton;
	static const int window_width = 800;
	static const int window_height = 600;
	static const int minimum_fps = 10;

	game_state state_;

	Game();
	Game& operator=(const Game&) = delete;

public:
	static Game* get_game_object();
	~Game();

	int run();
};
