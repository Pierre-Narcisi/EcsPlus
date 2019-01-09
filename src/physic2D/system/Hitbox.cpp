#include "Hitbox.hpp"

namespace physic2D { namespace system {
	void Hitbox::ImpulseResolution(manifold *col) {
		auto &speed = ecs::Ecs::get().getComponentMap<component::Speed>();
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		auto &mat = ecs::Ecs::get().getComponentMap<component::Materials>();
		auto rv = pos[col->B]._pos - pos[col->A]._pos;
		auto dot = col->normal.x * rv.x + col->normal.y * rv.y;
		// auto coef = (Mat[mat[col->A]._name].second > Mat[mat[col->B]._name].second ? Mat[mat[col->B]._name].second : Mat[mat[col->A]._name].second);
		// auto impulse = (-(1 + coef) * dot) / (1 / + 1 / );
	}

	bool Hitbox::AABBToAABB(manifold *col) {
		auto &AB = ecs::Ecs::get().getComponentMap<component::AABB>();
		Vec2 v = AB[col->A]._pos - AB[col->B]._pos;
		float extentX = (((AB[col->A]._max.x - AB[col->A]._min.x) / 2 + (AB[col->B]._max.x - AB[col->B]._min.x)) / 2) * abs(v.x);

		if (extentX > 0) {
			float extentY = (((AB[col->A]._max.y - AB[col->A]._min.y) / 2 + (AB[col->B]._max.y - AB[col->B]._min.y)) / 2) * abs(v.y);

			if (extentY > 0) {
				if (extentX > extentY) {
					col->normal = Vec2((v.x > 0 ? 1 : -1), 0);
					col->penetration = extentX;
				} else {
					col->normal = Vec2(0, (v.y > 0 ? 1 : -1));
					col->penetration = extentY;
				}
				return true;
			} else {
				return false;
			}
		}
		return false;
	}

	bool Hitbox::CircleToCircle(manifold *col) {

	}

	bool Hitbox::AABBToCircle(manifold *col) {

	}
}}
