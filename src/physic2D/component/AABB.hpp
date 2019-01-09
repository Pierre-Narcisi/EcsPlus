#pragma once

#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct AABB {
		AABB() {
			_min = Vec2(0, 0);
			_max = Vec2(0, 0);
			_pos = Vec2(0, 0);
			_size = Vec2(0, 0);
		}

		AABB(float minx, float miny, float maxx, float maxy) {
			_min = Vec2(minx, miny);
			_max = Vec2(maxx, maxy);
			_pos = Vec2(minx + (maxx - minx) / 2, miny + (maxy - miny) / 2);
			_size = Vec2(maxx - minx, maxy - miny);
		}

		AABB(Vec2 min, Vec2 max) {
			_min = min;
			_max = max;
			_pos = Vec2(min.x + (max.x - min.x) / 2, min.y + (max.y - min.y) / 2);
			_size = Vec2(max.x - min.x, max.y - min.y);
		}

		Vec2 _min;
		Vec2 _max;
		Vec2 _pos;
		Vec2 _size;
	};
}}