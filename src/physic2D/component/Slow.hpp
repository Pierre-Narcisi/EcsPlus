#pragma once

#include <functional>
#include "../../ecs/Ecs.hpp"
#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct Slow {
		Slow() {
			_perc = 0;
		}

		Slow(float perc) {
			_perc = perc;
		}

		float _perc;
	};
}}