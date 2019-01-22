#pragma once

#include "../component/AABB.hpp"
#include "../component/Speed.hpp"
#include "../component/Pos.hpp"
#include "../component/Materials.hpp"
#include "../component/Mass.hpp"
#include "../../ecs/Ecs.hpp"
#include "../manifold.hpp"
#include <algorithm>

namespace physic2D { namespace system {
	class Hitbox {
		public:
			bool AABBToAABB(manifold *col);
			bool CircleToCircle(manifold *col);
			bool AABBToCircle(manifold *col);
			void ImpulseResolution(manifold *col);
			void FrictionResolution(manifold *col);
			void Correction(manifold *col, const float percent);
			Vec2 Normalize(Vec2 v);
			void UpdateHitbox();
	};
}}