//
// Created by seb on 11/02/19.
//

#include "Graphical.hpp"
#include "ecs/Graphic.hpp"
#include "ecs/Ecs.hpp"

namespace ecs {
	void Graphical::PutPixel(int x, int y, sf::Color color) {
		auto &graph = ecs::Graphic::get();
		auto pixels = graph.getPixels();
		int width = static_cast<int>(ecs::Graphic::getWindow()->getSize().x);

		pixels[((y * width) + x) * 4 + 0] = color.r;
		pixels[((y * width) + x) * 4 + 1] = color.g;
		pixels[((y * width) + x) * 4 + 2] = color.b;
		pixels[((y * width) + x) * 4 + 3] = color.a;
	}

	void Graphical::DrawPixels() {
		auto &ecs = ecs::Ecs::get();
		auto win = ecs::Graphic::getWindow();
		sf::Sprite sprite;
		sf::Texture texture;

		texture.loadFromMemory(ecs::Graphic::get().getPixels(), (win->getSize().x * win->getSize().y * 4) * sizeof(sf::Uint8));
		sprite.setTexture(texture);
		ecs::Graphic::getWindow()->draw(sprite);
	}
}