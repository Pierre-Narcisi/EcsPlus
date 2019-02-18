//
// Created by seb on 07/01/19.
//

#include <iostream>
#include <ecs/Ecs.hpp>
#include <ecs/Time.hpp>
#include <thread>
#include <ecs/ThreadPool.hpp>
#include <ecs/Graphic.hpp>
#include <system/Update.hpp>
#include <ecs/DataBank.hpp>
#include <component/graphical/AnimatedSprite.hpp>
#include <component/graphical/Pixel.hpp>
#include <component/graphical/Drawable.hpp>
#include <zconf.h>
#include <system/control/Controls.hpp>
#include "src/physic2D/system/Hitbox.hpp"
#include "src/physic2D/system/Physic2D.hpp"
#include "src/physic2D/system/Gravity.hpp"
#include "src/physic2D/component/AABB.hpp"
#include "src/physic2D/component/Poly.hpp"
#include "src/physic2D/component/Circle.hpp"
#include "src/physic2D/component/Mass.hpp"
#include "src/physic2D/Vec2/vec2.hpp"
#include "src/Pool/Pool.hpp"

void createPile(float size, physic2D::system::Gravity &grav, float x) {
	auto &game = ecs::Ecs::get();

	for (int i = 10; i > 0; i--) {
		for (int j = 4; j > 0; j--) {
			ID sauce = ecs::entity::Entity::getId();
			game.addComponent<physic2D::component::Speed>(sauce, physic2D::Vec2(0, 0));
			game.addComponent<physic2D::component::Pos>(sauce, physic2D::Vec2(x - size * j, 600 - size * i));
			game.addComponent<physic2D::component::AABB>(sauce, physic2D::Vec2(size, size), false, true);
			game.addComponent<physic2D::component::Materials>(sauce, "Wood");
			game.addComponent<physic2D::component::Mass>(sauce, sauce);
			if (i == 10 || j == 1 || j == 4 || i % 2 == 0)
				game.addComponent<ecs::component::Sprite>(sauce, std::string("assets/test.jpg"), ecs::core::Vector2<unsigned int>(size, size));
			else
				game.addComponent<ecs::component::Sprite>(sauce, std::string("assets/test2.jpeg"), ecs::core::Vector2<unsigned int>(size, size));
			game.addComponent<ecs::component::Drawable>(sauce, true, 10, GraphicalMethod::Sprite);
			grav.addObject(sauce);
		}
	}
}


int main() {
	auto &game = ecs::Ecs::get();
	auto &screen = ecs::Graphic::get();

	ecs::DataBank<std::string, sf::Texture>::get().creator = [](std::string path){
		sf::Texture texture;
		texture.loadFromFile(path);
		return (texture);
	};

	physic2D::system::Physic2D physic = physic2D::system::Physic2D();
	game.addUpdate(1, &ecs::system::Controls::UpdateKeyboards);
	game.addUpdate(1, &ecs::system::Controls::UpdateMouses);
	game.addUpdate(2, [&physic](){physic.UpdatePhysic();});
	physic2D::system::Gravity grav = physic2D::system::Gravity();
	game.addUpdate(2, [&grav](){grav.updateGravity();});
	physic2D::system::Hitbox hit;
	game.addUpdate(1, [&hit](){
		hit.UpdateHitbox();
	});
	game.addUpdate(100, [](){ecs::Update::UpdateGraphical();});
	game.addUpdate(110, [&screen](){screen.update();});
	Pool(25);

	while(screen.isOpen()) {

		long time = ecs::Time::get(TimeUnit::MicroSeconds);

		game.update();
		// std::this_thread::sleep_for (std::chrono::seconds(1));
		auto x = static_cast<unsigned int>(16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(x));
		std::cout << 100 * (16666 - x) / 16666 << std::endl;
	}
	
	return 0;
}
