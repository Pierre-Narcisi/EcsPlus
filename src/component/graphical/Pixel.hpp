//
// Created by seb on 09/01/19.
//

#pragma once

#include <cstring>
#ifndef SERVER
#include <SFML/Graphics.hpp>
#endif

namespace ecs { namespace component {
	struct Pixel {
		Pixel() {}

#ifndef SERVER
		Pixel(sf::Vector2u size) {
			_pixels = new sf::Uint8[size.x * size.y * 4];
			std::memset(_pixels, 0x00, size.x * size.y * 4);
			_size = size;
		}

		void setPixel(sf::Vector2u pos, sf::Color color) {
			_pixels[((_size.x * pos.y) * 4 + pos.x * 4 + 0) % (_size.x * _size.y * 4)] = color.r;
			_pixels[((_size.x * pos.y) * 4 + pos.x * 4 + 1) % (_size.x * _size.y * 4)] = color.g;
			_pixels[((_size.x * pos.y) * 4 + pos.x * 4 + 2) % (_size.x * _size.y * 4)] = color.b;
			_pixels[((_size.x * pos.y) * 4 + pos.x * 4 + 3) % (_size.x * _size.y * 4)] = color.a;
		}

		void clean() {
			std::memset(_pixels, 0x00, _size.x * _size.y * 4);
		}

		sf::Uint8 *_pixels;
		sf::Vector2u _size;
#endif
	};
}}