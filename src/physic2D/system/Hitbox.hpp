#pragma once

#include "../manifold.hpp"

namespace physic2D { namespace system {
	class Hitbox {
		public:
			bool AABBToAABB(manifold *col);
			bool CircleToCircle(manifold *col);
			bool AABBToCircle(manifold *col);
	};
}}