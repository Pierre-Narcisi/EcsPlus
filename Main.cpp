//
// Created by seb on 07/01/19.
//

#include <iostream>
#include <ecs/Ecs.hpp>
#include <ecs/Time.hpp>
#include <thread>
#include <ecs/ThreadPool.hpp>
#include <ecs/Graphic.hpp>
#include "src/physic2D/system/physic2D.hpp"
#include "src/physic2D/Vec2/vec2.hpp"

int main() {
	auto &game = ecs::Ecs::get();
	auto &screen = ecs::Graphic::get();
	physic2D::system::physic2D physic = physic2D::system::physic2D();

	game.addUpdate(1, [](){
		std::cout << "Je suis une update" << std::endl;
	});
	game.addUpdate(1, [&physic](){physic.UpdatePhysic();});

	ID sauce = ecs::entity::Entity::getId();
	ecs::Ecs::get().addComponent<physic2D::component::Speed>(sauce, 1, physic2D::Vec2(1, 0));
	while(screen.isOpen()) {
		game.update();
	}
	
	return 0;
}
