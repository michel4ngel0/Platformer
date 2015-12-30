#pragma once

#include <chrono>
#include <map>

class Entity;

class Clock {
private:
	struct task {
		Entity* object;
		int code;
	};

	std::chrono::high_resolution_clock::time_point begin_;
	std::multimap<double, task> tasks_;

	static Clock* clock;
	Clock();
public:
	static Clock* get_clock();
	void set_alarm(Entity*, int, double);
	void step();
};
