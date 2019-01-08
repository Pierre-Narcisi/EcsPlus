//
// Created by seb on 07/01/19.
//

#include <iostream>
#include <ecs/Ecs.hpp>
#include <ecs/Time.hpp>
#include <thread>
#include <ecs/ThreadPool.hpp>
#include "src/physic2D/system/physic2D.hpp"
#include "src/physic2D/Vec2/vec2.hpp"

int main() {
	auto &game = ecs::Ecs::get();
	physic2D::system::physic2D physic = physic2D::system::physic2D();
	game.addUpdate(1, [&physic](){physic.UpdatePhysic();});

	ID sauce = ecs::entity::Entity::getId();
	ecs::Ecs::get().addComponent<physic2D::component::Speed>(sauce, 1, physic2D::Vec2(1, 1));
	while(1) {
		game.update();
		// std::this_thread::sleep_for (std::chrono::seconds(1));
	}
	
	return 0;
}
