#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include "Game.h"

int main() {
	Game* game = Game::get_game_object();
	return game->run();
}