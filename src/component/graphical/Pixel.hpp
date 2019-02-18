//
// Created by seb on 09/01/19.
//

#pragma once

#include "ecs/Vector2.hpp"
#ifndef SERVER
#include <SFML/Graphics.hpp>
#endif
namespace ecs { namespace component {
	struct Pixel {
		Pixel(): rec(sf::Vector2f(1,1)){}

		Pixel(sf::Color color): rec(sf::Vector2f(1,1)){
			this->color = color;
		}

#ifndef SERVER
		sf::Color			color;
		sf::RectangleShape	rec;
#endif
	};
}}