#pragma once

#include <chrono>
#include "Clock.h"
#include "Entity.h"

Clock::Clock() {
	begin_ = std::chrono::high_resolution_clock::now();
}

void Clock::schedule_deletion(Entity* object, double dt) {
	std::chrono::milliseconds delay((int)(dt * 1000));
	std::chrono::high_resolution_clock::time_point deadline =
		std::chrono::high_resolution_clock::now() + delay;
	std::chrono::duration<double> delay_from_begin =
		std::chrono::duration_cast<std::chrono::duration<double>>(deadline - begin_);

	tasks_.insert(std::make_pair(delay_from_begin.count(), object));
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
			auto deleted_object = first_task->second;
			delete deleted_object;
			tasks_.erase(first_task);
		}
		else {
			break;
		}
	}
}