#pragma once

#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct Acceleration {
		Acceleration() {
			_accel = 0;
			_normal = Vec2(0, 0);
		}

		Acceleration(float accel, Vec2 normal) {
			_accel = accel;
			_normal = normal;
		}

		float _accel;
		Vec2 _normal;
	};
}}