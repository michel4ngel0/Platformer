#include "Camera.h"

CameraStationary::CameraStationary(float left, float top, float width, float height) :
	left_(left), top_(top), width_(width), height_(height) {
}

aabb CameraStationary::get_view() {
	aabb result = { left_, top_, width_, height_ };
	return result;
}

CameraFollower::CameraFollower(sf::Sprite* followed, float width, float height) :
	followed_(followed), width_(width), height_(height) {
	
	x_translation_ = -(width - followed->getTextureRect().width) / 2;
	y_translation_ = -(height - followed->getTextureRect().height) / 2;
}

aabb CameraFollower::get_view() {
	aabb result = { followed_->getPosition().x + x_translation_,
				    followed_->getPosition().y + y_translation_,
				    width_,
				    height_ };
	return result;
}