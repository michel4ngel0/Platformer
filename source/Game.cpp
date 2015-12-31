#include "Game.h"
#include "Level.h"
#include "Clock.h"
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

	//	Prepare the window and the canvas
	sf::RenderTexture canvas;
	canvas.create(canvas_width, canvas_height, 32);
	auto available_video_modes = sf::VideoMode::getFullscreenModes();
	if (available_video_modes.size() < 1) {
		std::cerr << "Couldn't start in fullscreen mode" << std::endl;
		return -1;
	}
	sf::VideoMode current_video_mode = available_video_modes[0];
	scale_ = (int)fmin(current_video_mode.width / (float)canvas_width,
		               current_video_mode.height / (float)canvas_height);
	sf::RenderWindow window(current_video_mode, 
		                    "Platrofmer",
		                    sf::Style::Fullscreen);
	sf::Sprite window_content(canvas.getTexture());
	window_content.setPosition((current_video_mode.width - (scale_ * canvas_width)) / 2,
	                           (current_video_mode.height - (scale_ * canvas_height)) / 2);
	window_content.setScale((float)scale_, (float)scale_);
	window.clear(sf::Color::Black);

	Level current_level("test.lvl", (float)canvas_width, (float)canvas_height);
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
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
					break;
				}
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

		Clock::get_clock()->step();

		current_level.step(dt);

		canvas.clear(sf::Color(35, 35, 35));
		current_level.draw(canvas);
		canvas.display();	//	very important XD (no, really)

		window.draw(window_content);
		window.display();
	}

	return 0;
}