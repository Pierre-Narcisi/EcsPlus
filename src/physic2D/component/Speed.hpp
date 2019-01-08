#pragma once

#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct Speed {
		Speed() {
			_speed = 0;
			_normal = Vec2(0, 0);
		}

		Speed(float speed, Vec2 normal) {
			_speed = speed;
			_normal = normal;
		}

		float _speed;
		Vec2 _normal;
	};
}}