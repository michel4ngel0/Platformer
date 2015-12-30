#pragma once

#include <chrono>
#include "Clock.h"
#include "Entity.h"

Clock* Clock::clock = nullptr;

Clock::Clock() {
	begin_ = std::chrono::high_resolution_clock::now();
}

Clock* Clock::get_clock() {
	if (Clock::clock == nullptr)
		Clock::clock = new Clock();
	return Clock::clock;
}

void Clock::set_alarm(Entity* object, int code, double dt) {
	std::chrono::milliseconds delay((int)(dt * 1000));
	std::chrono::high_resolution_clock::time_point deadline =
		std::chrono::high_resolution_clock::now() + delay;
	std::chrono::duration<double> delay_from_begin =
		std::chrono::duration_cast<std::chrono::duration<double>>(deadline - begin_);

	tasks_.insert(std::make_pair(delay_from_begin.count(), task{ object, code }));
}

void Clock::step() {
	auto now = std::chrono::high_resolution_clock::now();
	double from_begin =
		std::chrono::duration_cast<std::chrono::duration<double>>(now - begin_).count();
	
	while (true) {
		auto first_task = tasks_.begin();
		if (first_task == tasks_.end())
			break;

		if (first_task->first <= from_begin) {
			auto& object = first_task->second.object;
			auto& code = first_task->second.code;
			object->alert(code);
			
			tasks_.erase(first_task);
		}
		else {
			break;
		}
	}
}