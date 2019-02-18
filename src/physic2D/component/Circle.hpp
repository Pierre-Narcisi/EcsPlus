#pragma once

#include "../Vec2/vec2.hpp"
#include "../../component/graphical/Pixel.hpp"
#include "../../component/graphical/Drawable.hpp"
#include "../../ecs/Graphic.hpp"
#include "../../physic2D/system/Physic2D.hpp"
#include "Pos.hpp"

namespace physic2D { namespace component {
	struct Circle {
		Circle() {
			_radius = 0;
		}

		Circle(float radius, bool trigger, bool collidable) {
			_radius = radius;
			_trigger = trigger;
			_collidable = collidable;
		}

		void draw(ID pix, ID circ) {
			auto &game = ecs::Ecs::get();
			auto &pixels = game.getComponentMap<ecs::component::Pixel>();
			auto &pos = game.getComponentMap<physic2D::component::Pos>();
			auto &pixel = pixels[pix];

			int y = _radius;
    		int d = 3 - 2 * y;

			for (int x = 0; x < y; ++x) {
		        if (d > 0) { 
            		y--;
            		d = d + 4 * (x - y) + 10; 
        		} else {
            		d = d + 4 * x + 6;
				}
        		pixel.setPixel(sf::Vector2u(pos[circ]._pos.x+x, pos[circ]._pos.y+y), sf::Color(255, 255, 255, 255)); 
    			pixel.setPixel(sf::Vector2u(pos[circ]._pos.x-x, pos[circ]._pos.y+y), sf::Color(255, 255, 255, 255));
    			pixel.setPixel(sf::Vector2u(pos[circ]._pos.x+x, pos[circ]._pos.y-y), sf::Color(255, 255, 255, 255));
    			pixel.setPixel(sf::Vector2u(pos[circ]._pos.x-x, pos[circ]._pos.y-y), sf::Color(255, 255, 255, 255));
    			pixel.setPixel(sf::Vector2u(pos[circ]._pos.x+y, pos[circ]._pos.y+x), sf::Color(255, 255, 255, 255));
    			pixel.setPixel(sf::Vector2u(pos[circ]._pos.x-y, pos[circ]._pos.y+x), sf::Color(255, 255, 255, 255));
    			pixel.setPixel(sf::Vector2u(pos[circ]._pos.x+y, pos[circ]._pos.y-x), sf::Color(255, 255, 255, 255));
    			pixel.setPixel(sf::Vector2u(pos[circ]._pos.x-y, pos[circ]._pos.y-x), sf::Color(255, 255, 255, 255));
    		}
		}

		float _radius;
		bool _trigger;
		bool _collidable;
	};
}}