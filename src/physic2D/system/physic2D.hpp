#pragma once

#include "../manifold.hpp"
#include "../../ecs/Time.hpp"
#include "../../ecs/Ecs.hpp"
#include "../component/Acceleration.hpp"
#include "../component/Forces.hpp"
#include "../component/Pos.hpp"
#include "../component/Speed.hpp"
#include "../component/AABB.hpp"
#include "math.h"

namespace physic2D { namespace system {
	class physic2D {
		public:
			physic2D();
			void UpdatePos();
			void UpdateSpeed();
			void UpdateAcceleration();
			void UpdateForces();
			void UpdatePhysic();

			long _lastTime;
			float _deltaTime;
	};
}}