#include "Dummy.h"
#include "../Scene.h"
#include "../Clock.h"

Dummy::Dummy() {
	frame_ = 0;
	setTextureRect(sf::IntRect(0, 0, 16, 16));
	Clock::get_clock()->set_alarm(this, 0, 0.25);
}

void Dummy::step(Scene*, double dt) {

}

void Dummy::alert(int code) {
	Clock::get_clock()->set_alarm(this, 0, 0.25);
	frame_ = (frame_ + 1) % 4;
	setTextureRect(sf::IntRect(16 * frame_, 0, 16, 16));
}