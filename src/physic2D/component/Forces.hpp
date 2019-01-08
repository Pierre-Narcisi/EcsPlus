#pragma once

#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct Forces {
		Forces() {
			_normal = Vec2(0, 0);
			_force = 0;
		}

		Forces(float _force, Vec2 normal) {
			
		}

		float _force;
		Vec2 _normal;
	};
}}