#include "vec2.hpp"

namespace physic2D {
	Vec2::Vec2() {
		this->x = 0;
		this->y = 0;
	}

	Vec2::Vec2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	void Vec2::operator=(Vec2 v) {
		this->x = v.x;
		this->y = v.y;
	}

	Vec2 Vec2::operator+(Vec2 v) {
		Vec2 res = Vec2(this->x + v.x, this->y + v.y);
		return res;
	}

	Vec2 Vec2::operator-(Vec2 v) {
		Vec2 res = Vec2(this->x - v.x, this->y - v.y);
		return res;
	}

	Vec2 Vec2::operator/(float v) {
		Vec2 res = Vec2(this->x / v, this->y / v);
		return res;
	}

	Vec2 Vec2::operator*(float v) {
		Vec2 res = Vec2(this->x * v, this->y * v);
		return res;

	}

	float Vec2::length() {
		return this->x * this->x + this->y * this->y;
	}

	float Vec2::lengthSquared() {
		return std::sqrt(this->x * this->x + this->y * this->y);
	}
}