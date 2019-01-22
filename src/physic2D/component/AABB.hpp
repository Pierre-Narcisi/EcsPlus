#pragma once

#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct AABB {
		AABB() {
			_min = Vec2(0, 0);
			_max = Vec2(0, 0);
			_size = Vec2(0, 0);
		}

		AABB(float minx, float miny, float maxx, float maxy) {
			_min = Vec2(minx, miny);
			_max = Vec2(maxx, maxy);
			_size = Vec2(maxx - minx, maxy - miny);
		}

		AABB(Vec2 min, Vec2 max) {
			_min = min;
			_max = max;
			_size = Vec2(max.x - min.x, max.y - min.y);
		}

		AABB(Vec2 size) {
			_size = size;
		}

		Vec2 _min;
		Vec2 _max;
		Vec2 _size;
	};
}}