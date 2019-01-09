#pragma once

#include "../component/AABB.hpp"
#include "../component/Speed.hpp"
#include "../component/Pos.hpp"
#include "../component/Materials.hpp"
#include "../../ecs/Ecs.hpp"
#include "../manifold.hpp"

namespace physic2D { namespace system {
	class Hitbox {
		public:
			bool AABBToAABB(manifold *col);
			bool CircleToCircle(manifold *col);
			bool AABBToCircle(manifold *col);
			void ImpulseResolution(manifold *col);
	};
}}