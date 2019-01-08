#pragma once

#include <math.h>

namespace physic2D {
	class Vec2 {
		public:
			Vec2();
			Vec2(float x, float y);
			void operator=(Vec2 v);
			Vec2 operator+(Vec2 v);
			Vec2 operator-(Vec2 v);
			float length();
			float lengthSquared();
			float x;
			float y;
	};
}