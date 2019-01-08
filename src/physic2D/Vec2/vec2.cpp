#include "vec2.hpp"

namespace physic2D {
	Vec2::Vec2() {
		_x = 0;
		_y = 0;
	}

	Vec2::Vec2(float x, float y) {
		_x = x;
		_y = y;
	}

	void Vec2::operator=(Vec2 v) {
		_x = v.getX();
		_y = v.getY();
	}

	Vec2 Vec2::operator+(Vec2 v) {
		Vec2 res = Vec2(_x + v.getX(), _y + v.getY());
		return res;
	}

	Vec2 Vec2::operator-(Vec2 v) {
		Vec2 res = Vec2(_x - v.getX(), _y - v.getY());
		return res;
	}

	float Vec2::length() {
		return _x * _x + _y * _y;
	}

	float Vec2::lengthSquared() {
		return std::sqrt(_x * _x + _y * _y);
	}

	float Vec2::getX() {
		return _x;
	}

	float Vec2::getY() {
		return _y;
	}

	void Vec2::setX(float x) {
		_x = x;
	}

	void Vec2::setY(float y) {
		_y = y;
	}
}