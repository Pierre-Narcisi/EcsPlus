#pragma once

#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct circle {
		circle() {
			_radius = 0;
			_pos = Vec2(0, 0);
		}

		circle(float radius, float x, float y) {
			_radius = radius;
			_pos = Vec2(x, y);
		}

		circle(float radius, Vec2 pos) {
			_radius = radius;
			_pos = pos;
		}

		float _radius;
		Vec2 _pos;
	};
}}