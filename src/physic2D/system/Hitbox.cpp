#include "Hitbox.hpp"

namespace physic2D { namespace system {
	Vec2 Hitbox::Normalize(Vec2 v) {
		auto d = v.length();
		if (d == 0)
			return v;
		return v / d;
	}

	void Hitbox::Correction(manifold *col, const float percent) {
		auto &mas = ecs::Ecs::get().getComponentMap<component::Mass>();
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();

		Vec2 correct = col->normal * percent * (col->penetration / (mas[col->A]._invMass + mas[col->B]._invMass));
		pos[col->A]._pos -= correct * mas[col->A]._invMass;
		pos[col->B]._pos += correct * mas[col->B]._invMass;
	}

	void Hitbox::UpdateHitbox() {
		auto AABBIds = ecs::Ecs::get().filter<component::AABB>();
		auto circ = ecs::Ecs::get().filter<component::Circle>();

		for (auto it = AABBIds.begin(); it != AABBIds.end();++it) {
			for (auto it2 = it+1; it2 != AABBIds.end();++it2) {
				manifold col;
				col.A = *it;
				col.B = *it2;
				if (AABBToAABB(&col) == true)  {
					ImpulseResolution(&col);
					Correction(&col, 0.5);
					FrictionResolution(&col);
				}
			}
			for (auto it2 = circ.begin(); it2 != circ.end();++it2) {
				manifold col;
				col.A = *it;
				col.B = *it2;
				if (AABBToCircle(&col) == true)  {
					ImpulseResolution(&col);
					Correction(&col, 0.5);
					FrictionResolution(&col);
				}
			}
		}
		for (auto it = circ.begin(); it != circ.end();++it) {
			for (auto it2 = it+1; it2 != circ.end();++it2) {
				manifold col;
				col.A = *it;
				col.B = *it2;
				if (CircleToCircle(&col) == true) {
					ImpulseResolution(&col);
					Correction(&col, 0.5);
					FrictionResolution(&col);
				}
			}
		}
	}

	void Hitbox::FrictionResolution(manifold *col) {
		auto &speed = ecs::Ecs::get().getComponentMap<component::Speed>();
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		auto &mat = ecs::Ecs::get().getComponentMap<component::Materials>();
		auto &mas = ecs::Ecs::get().getComponentMap<component::Mass>();

		auto rv = speed[col->B]._speed - speed[col->A]._speed;
		auto dot = rv.dot(col->normal);
		auto t = rv - col->normal * dot;
		std::cout << "t.x: " << t.x << std::endl;
		std::cout << "t.y: " << t.y << std::endl;
		std::cout << "rv.x: " << rv.x << std::endl;
		std::cout << "rv.y: " << rv.y << std::endl;
		std::cout << "col->normal.x: " << col->normal.x << std::endl;
		std::cout << "col->normal.y: " << col->normal.y << std::endl;
		std::cout << "dot: " << dot << std::endl;
		t = Normalize(t);
		std::cout << "nt.x: " << t.x << std::endl;
		std::cout << "nt.y: " << t.y << std::endl;
		auto jt = -t.dot(rv) / (mas[col->A]._invMass + mas[col->A]._invMass);

		float coef = Vec2(Mat[mat[col->B]._name]._fricS, Mat[mat[col->A]._name]._fricS).length();
		Vec2 impulse;
		if (coef * col->j > abs(jt)) {
			impulse = t * jt;
			std::cout << "sauce" << std::endl;
		} else {
			float coefD = Vec2(Mat[mat[col->B]._name]._fricD, Mat[mat[col->A]._name]._fricD).length();
			impulse = t * -col->j * coefD;
			std::cout << "col->j: " << col->j << std::endl;
			// std::cout << "t.x: " << t.x << std::endl;
			// std::cout << "t.y: " << t.y << std::endl;
		}
		speed[col->A]._speed -= impulse * mas[col->A]._invMass;
		speed[col->B]._speed += impulse * mas[col->B]._invMass;
		std::cout << "impulse.x: " << impulse.x << std::endl;
		std::cout << "impulse.y: " << impulse.y << std::endl << std::endl;
	}

	void Hitbox::ImpulseResolution(manifold *col) {
		auto &speed = ecs::Ecs::get().getComponentMap<component::Speed>();
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		auto &mat = ecs::Ecs::get().getComponentMap<component::Materials>();
		auto &mas = ecs::Ecs::get().getComponentMap<component::Mass>();

		auto rv = speed[col->B]._speed - speed[col->A]._speed;
		auto dot = rv.dot(col->normal);
		if (dot > 0) {
			return;
		}
		float coef;
		if (Mat[mat[col->A]._name]._boing > Mat[mat[col->B]._name]._boing)
			coef = Mat[mat[col->B]._name]._boing;
		else 
			coef = Mat[mat[col->A]._name]._boing;
		auto j = (-(1 + coef) * dot) / (mas[col->A]._invMass + mas[col->B]._invMass);
		col->j = j;
		std::cout << "j: " << j << std::endl;
		auto impulse = col->normal * j;
		speed[col->A]._speed -= impulse * mas[col->A]._invMass;
		speed[col->B]._speed += impulse * mas[col->B]._invMass;
	}

	bool Hitbox::AABBToAABB(manifold *col) {
		auto &AB = ecs::Ecs::get().getComponentMap<component::AABB>();
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		Vec2 v = pos[col->B]._pos - pos[col->A]._pos;


		float extentXA = (AB[col->A]._max.x - AB[col->A]._min.x) / 2;
		float extentXB = (AB[col->B]._max.x - AB[col->B]._min.x) / 2;
		float extentX = extentXA + extentXB - abs(v.x);
			
		if (extentX > 0) {
			float extentYA = (AB[col->A]._max.y - AB[col->A]._min.y) / 2;
			float extentYB = (AB[col->B]._max.y - AB[col->B]._min.y) / 2;
			float extentY = extentYA + extentYB - abs(v.y);
 			// std::cout << "sauce" << std::endl;

			if (extentY > 0) {
				if (extentX < extentY) {
					col->normal = Vec2((v.x < 0 ? -1 : 1), 0);
					col->penetration = extentX;
				} else {
					col->normal = Vec2(0, (v.y < 0 ? -1 : 1));
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
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		auto &circ = ecs::Ecs::get().getComponentMap<component::Circle>();
		auto v = pos[col->B]._pos - pos[col->A]._pos;
		auto r = circ[col->A]._radius + circ[col->B]._radius;

		if (v.lengthSquared() > r * r)
			return false;
		auto d = v.length();

		if (d != 0) {
			col->penetration = r - d;
			col->normal = v / d;
			return true;
		} else {
			col->penetration = circ[col->A]._radius;
			col->normal = Vec2(1, 0);
			return true;
		}
	}

	bool Hitbox::AABBToCircle(manifold *col) {
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		auto &AB = ecs::Ecs::get().getComponentMap<component::AABB>();
		auto &circ = ecs::Ecs::get().getComponentMap<component::Circle>();
		Vec2 v = pos[col->B]._pos - pos[col->A]._pos;
		float extentX = (AB[col->A]._max.x - AB[col->A]._min.x) / 2;
		float extentY = (AB[col->A]._max.y - AB[col->A]._min.y) / 2;
		float r = circ[col->B]._radius;
		Vec2 clos = v;
		clos.x = std::clamp(clos.x, -extentX, extentX);
		clos.y = std::clamp(clos.y, -extentY, extentY);
		if (clos == v) {
			if (abs(v.x) > abs(v.y))
				clos.x = (clos.x > 0 ? extentX : -extentX);
			else
				clos.y = (clos.y > 0 ? extentY : -extentY);
			Vec2 normal = v - clos;
			col->normal = Normalize(-normal);
			col->penetration = r - normal.length();
			return true;
		} 
		else {
			Vec2 normal = v - clos;
			// std::cout << "normal.lengthSquared(): "<< normal.lengthSquared() << std::endl;
			// std::cout << "circ[col->B]._radius * circ[col->B]._radius: "<< circ[col->B]._radius * circ[col->B]._radius << std::endl;
			// std::cout << "v.x: " << v.x << std::endl;
			// std::cout << "v.y: " << v.y << std::endl;
			// std::cout << "clos.x: " << clos.x << std::endl;
			// std::cout << "clos.y: " << clos.y << std::endl;
			if (normal.lengthSquared()  > r * r) {
				return false;
			} else
				col->penetration = r - normal.length();
				col->normal = Normalize(normal);
				return true;
		}
	}
}}
