#pragma once

#include <chrono>
#include <map>

class Entity;

//	Unused for now. Propably gonna modify it to trigger events.
class Clock {
private:
	std::chrono::high_resolution_clock::time_point begin_;
	std::multimap<double, Entity*> tasks_;

public:
	Clock();
	void schedule_deletion(Entity*, double);
	void step();
};
