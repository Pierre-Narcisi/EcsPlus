//
// Created by seb on 14/01/19.
//

#pragma once

#include <list>
#include "Sprite.hpp"

namespace ecs { namespace component {
	struct AnimatedSprite {

		std::list<Sprite>	sprites;
		int			pos;
		float 			delta;
		long 			last;
	};
}}