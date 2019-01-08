#include "physic2D.hpp"

namespace physic2D { namespace system {
	physic2D::physic2D() {
		_lastTime = ecs::Time::get(TimeUnit::MilliSeconds);
	}

	void UpdatePos() {

	}

	void physic2D::UpdateSpeed() {
		auto ids = ecs::Ecs::get().filter<component::Speed>();
		auto speed = ecs::Ecs::get().getComponentMap<component::Speed>();
		auto pos = ecs::Ecs::get().getComponentMap<component::Pos>();

		for (auto id : ids) {
			if (!ecs::Ecs::get().idHasComponents<component::Pos>(id)) {
				ecs::Ecs::get().addComponent<component::Pos>(id);
				pos = ecs::Ecs::get().getComponentMap<component::Pos>();
			}
			double angle = std::atan2(speed[id]._normal.getX(), speed[id]._normal.getY());
			pos[id]._pos.setX(pos[id]._pos.getX() + (sinf(angle) * (speed[id]._speed * _deltaTime)));
			pos[id]._pos.setY(pos[id]._pos.getY() + (cosf(angle) * (speed[id]._speed * _deltaTime)));
			// std::cout << "X: " << pos[id]._pos.getX() << std::endl;
			// std::cout << "DT: " << _deltaTime << std::endl;
		}

	}

	void physic2D::UpdateAcceleration() {
		auto ids = ecs::Ecs::get().filter<component::Acceleration>();
		auto accel = ecs::Ecs::get().getComponentMap<component::Acceleration>();
		auto speed = ecs::Ecs::get().getComponentMap<component::Speed>();

		for (auto id : ids) {
			if (!ecs::Ecs::get().idHasComponents<component::Speed>(id)) {
				ecs::Ecs::get().addComponent<component::Speed>(id);
				speed = ecs::Ecs::get().getComponentMap<component::Speed>();
			}
			speed[id]._speed += accel[id]._accel * _deltaTime;
			speed[id]._normal = accel[id]._normal;
		}
	}

	void physic2D::UpdateForces() {

	}

	void physic2D::UpdatePhysic() {
		long newTime = ecs::Time::get(TimeUnit::MilliSeconds);
	
		_deltaTime = (newTime - _lastTime) / 1000;
		_lastTime = newTime;
		UpdateAcceleration();
		UpdateSpeed();
	}
}}