#pragma once

#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct Circle {
		Circle() {
			_radius = 0;
		}

		Circle(float radius) {
			_radius = radius;
		}

		float _radius;
	};
}}