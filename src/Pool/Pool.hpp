#pragma once

#include "component/graphical/AnimatedSprite.hpp"
#include "../physic2D/system/Hitbox.hpp"
#include "../physic2D/system/Physic2D.hpp"
#include "../physic2D/system/Gravity.hpp"
#include "../physic2D/component/AABB.hpp"
#include "../physic2D/component/Poly.hpp"
#include "../physic2D/component/Circle.hpp"
#include "../physic2D/component/Mass.hpp"
#include "../physic2D/Vec2/vec2.hpp"
#include "component/graphical/Drawable.hpp"

class Pool {
	public:
		Pool(float size);
};