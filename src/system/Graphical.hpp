//
// Created by seb on 11/02/19.
//

#pragma once

#ifndef SERVER
#include <SFML/Graphics/Color.hpp>
#endif

namespace ecs {
	class Graphical {
	public:
#ifndef SERVER
	static void PutPixel(int x, int y, sf::Color color);

	static void DrawPixels();
#endif
	};

}

