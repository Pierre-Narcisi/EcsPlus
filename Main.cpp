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
#include <component/graphical/Sprite.hpp>
#include <component/graphical/Drawable.hpp>
#include <zconf.h>
#include "src/physic2D/system/physic2D.hpp"
#include "src/physic2D/Vec2/vec2.hpp"

int main() {
	auto &game = ecs::Ecs::get();
	auto &screen = ecs::Graphic::get();

	ecs::DataBank<std::string, sf::Texture>::get().creator = [](std::string path){
		sf::Texture texture;
		texture.loadFromFile(path);
		return (texture);
	};

	physic2D::system::physic2D physic = physic2D::system::physic2D();
	game.addUpdate(1, [&physic](){physic.UpdatePhysic();});
	game.addUpdate(100, [](){ecs::Update::UpdateGraphical();});
	game.addUpdate(101, [&screen](){screen.update();});

	ID sauce = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(sauce, 100, physic2D::Vec2(1, 1));
	game.addComponent<ecs::component::Sprite>(sauce, std::string("assets/test.jpg")/*, ecs::core::Vector2<unsigned int>(500,500)*/);
	game.addComponent<ecs::component::Drawable>(sauce, true, 10, GraphicalMethod::Sprite);

	while(screen.isOpen()) {

		long time = ecs::Time::get(TimeUnit::MicroSeconds);

		game.update();
		// std::this_thread::sleep_for (std::chrono::seconds(1));
		auto x = static_cast<unsigned int>(16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::cout << x << std::endl;
		std::this_thread::sleep_for(std::chrono::microseconds(x));
	}
	
	return 0;
}
