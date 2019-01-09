#include "physic2D.hpp"

namespace physic2D { namespace system {
	physic2D::physic2D() {
		_lastTime = ecs::Time::get(TimeUnit::NanoSeconds);
	}

	void UpdatePos() {

	}

	void physic2D::UpdateSpeed() {
		auto ids = ecs::Ecs::get().filter<component::Speed>();
		auto &speed = ecs::Ecs::get().getComponentMap<component::Speed>();
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();

		for (auto id : ids) {
			if (!ecs::Ecs::get().idHasComponents<component::Pos>(id)) {
				ecs::Ecs::get().addComponent<component::Pos>(id);
				pos = ecs::Ecs::get().getComponentMap<component::Pos>();
			}
			double angle = std::atan2(speed[id]._normal.x, speed[id]._normal.y);
			pos[id]._pos.x += sinf(angle) * (speed[id]._speed * _deltaTime);
			pos[id]._pos.y += (cosf(angle) * (speed[id]._speed * _deltaTime));
			std::cout << "speed: " << speed[id]._speed << std::endl;
			std::cout << "X: " << pos[id]._pos.x << std::endl;
			std::cout << "Y: " << pos[id]._pos.y << std::endl;
			std::cout << "ouais: " << (sinf(angle) * (speed[id]._speed * _deltaTime)) << std::endl;
			std::cout << "DT: " << _deltaTime << std::endl;
		}

	}

	void physic2D::UpdateAcceleration() {
		auto ids = ecs::Ecs::get().filter<component::Acceleration>();
		auto &accel = ecs::Ecs::get().getComponentMap<component::Acceleration>();
		auto &speed = ecs::Ecs::get().getComponentMap<component::Speed>();

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
		long newTime = ecs::Time::get(TimeUnit::NanoSeconds);
	
		_deltaTime = (newTime - _lastTime) / 1000000000.f;
		_lastTime = newTime;
		UpdateAcceleration();
		UpdateSpeed();
	}
}}