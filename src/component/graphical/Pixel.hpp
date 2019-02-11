//
// Created by seb on 09/01/19.
//

#pragma once

#include "ecs/Vector2.hpp"

namespace ecs { namespace component {
	struct Pixel {
		Pixel(){
			this->pos.x = 0;
			this->pos.y = 0;
		}

		Pixel(int x, int y){
			this->pos.x = x;
			this->pos.y = y;
		}

		Pixel(ecs::core::Vector2<int> pos){
			this->pos = pos;
		}

		ecs::core::Vector2<int> pos;
	};
}}