#include "aabb_tree.h"

#include <cmath>

double aabb::area() const {
	return (x_size_) * (y_size_);
}

double aabb::hull_area(const aabb& other) const {
	return (fmax(x_size_ + x_, other.x_size_ + other.x_) - fmin(x_, other.x_)) *
		   (fmax(y_size_ + y_, other.y_size_ + other.y_) - fmin(y_, other.y_));
}

void aabb::hull(const aabb& other) {
	x_size_ = fmax(x_size_ + x_, other.x_size_ + other.x_);
	x_ = fmin(x_, other.x_);
	x_size_ -= x_;

	y_size_ = fmax(y_size_ + y_, other.y_size_ + other.y_);
	y_ = fmin(y_, other.y_);
	y_size_ -= y_;
}

bool aabb::is_contained(const aabb& other) const {
	if (x_ < other.x_ - eps)
		return false;
	if (x_ + x_size_ > other.x_ + other.x_size_ + eps)
		return false;
	if (y_ < other.y_ - eps)
		return false;
	if (y_ + y_size_ > other.y_ + other.y_size_ + eps)
		return false;

	return true;
}

bool aabb::overlaps(const aabb& other) const {
	if (x_ > other.x_ + other.x_size_ + eps)
		return false;
	if (x_ + x_size_ < other.x_ - eps)
		return false;
	if (y_ > other.y_ + other.y_size_ + eps)
		return false;
	if (y_ + y_size_ < other.y_ - eps)
		return false;

	return true;
}

void aabb::scale(double k) {
	x_ -= (k - 1.0) * x_size_ / 2.0;
	y_ -= (k - 1.0) * y_size_ / 2.0;

	x_size_ *= k;
	y_size_ *= k;
}