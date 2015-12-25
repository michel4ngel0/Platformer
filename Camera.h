#pragma once

#include <SFML/Graphics.hpp>
#include "aabb-tree\aabb_tree.h"

class Camera {
public:
	virtual aabb get_view() = 0;
};

class CameraStationary : public Camera {
private:
	float left_;
	float top_;
	float width_;
	float height_;
public:
	CameraStationary(float, float, float, float);
	virtual aabb get_view();
};

class CameraFollower : public Camera {
private:
	sf::Sprite* followed_;
	float x_translation_;
	float y_translation_;
	float width_;
	float height_;
public:
	CameraFollower(sf::Sprite*, float, float);
	virtual aabb get_view();
};