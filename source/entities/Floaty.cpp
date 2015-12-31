#include "Floaty.h"
#include "Creature.h"
#include "../Scene.h"
#include "../Clock.h"

Floaty::Floaty() {
	setTextureRect(sf::IntRect(0, 0, 16, 16));
	frame_ = 0;
	Clock::get_clock()->set_alarm(this, 0, 0.125);
}

void Floaty::step(Scene* scene, double dt) {

}

void Floaty::alert(int code) {
	Clock::get_clock()->set_alarm(this, 0, 0.125);
	frame_ = (frame_ + 1) % 8;
	setTextureRect(sf::IntRect(16 * frame_, 0, 16, 16));
}