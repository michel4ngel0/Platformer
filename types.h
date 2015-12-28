#pragma once

#include <string>

const std::string path_levels = "resources/levels/";
const std::string path_textures = "resources/textures/";

enum class game_state {
	not_started,
	playing,
	paused,
};

enum class direction {
	up,
	down,
	left,
	right,
	none,
};