#include "Game.h"
#include "Level.h"
#include <cassert>
#include <chrono>
#include <iostream>

Game* Game::singleton = nullptr;

Game* Game::get_game_object() {
	if (Game::singleton == nullptr)
		Game::singleton = new Game();

	return Game::singleton;
}

Game::Game() {
	state_ = game_state::not_started;
}

Game::~Game() {

}

int Game::run() {
	assert(state_ == game_state::not_started);

	auto previous_time =
		std::chrono::high_resolution_clock::now();
	decltype(previous_time) time;
	double time_counter = 0.0;
	unsigned long frame_counter = 0;

	sf::RenderWindow window(sf::VideoMode(window_width, window_height, 32),
	                        "Platformer");

	Level current_level("test.lvl", (float)window_width, (float)window_height);
	state_ = game_state::playing;

	while (window.isOpen()) {
		time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> delta_t =
			std::chrono::duration_cast<std::chrono::duration<double>>(time - previous_time);
		previous_time = time;
		double dt = delta_t.count();
		if (dt > 1.0 / minimum_fps)
			dt = 1.0 / minimum_fps;

		frame_counter += 1;
		time_counter += dt;
		if (time_counter >= 1.0) {
			std::cerr << "FPS: " << frame_counter << std::endl;
			frame_counter = 0;
			time_counter -= 1.0;
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				//
				//
				//
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				//
				//
				//
			}
		}

		current_level.step(dt);

		window.clear(sf::Color(35, 35, 35));
		current_level.draw(window);
		window.display();
	}

	return 0;
}