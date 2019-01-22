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
#include <component/graphical/Drawable.hpp>
#include <zconf.h>
#include "src/physic2D/system/Hitbox.hpp"
#include "src/physic2D/system/Physic2D.hpp"
#include "src/physic2D/system/Gravity.hpp"
#include "src/physic2D/component/AABB.hpp"
#include "src/physic2D/component/Circle.hpp"
#include "src/physic2D/component/Mass.hpp"
#include "src/physic2D/Vec2/vec2.hpp"

void createPile(float size, physic2D::system::Gravity &grav, float x) {
	auto &game = ecs::Ecs::get();

	for (int i = 10; i > 0; i--) {
		for (int j = 4; j > 0; j--) {
			ID sauce = ecs::entity::Entity::getId();
			game.addComponent<physic2D::component::Speed>(sauce, physic2D::Vec2(0, 0));
			game.addComponent<physic2D::component::Pos>(sauce, physic2D::Vec2(x - size * j, 600 - size * i));
			game.addComponent<physic2D::component::AABB>(sauce, physic2D::Vec2(size, size));
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
	game.addUpdate(2, [&physic](){physic.UpdatePhysic();});
	physic2D::system::Gravity grav = physic2D::system::Gravity();
	game.addUpdate(2, [&grav](){grav.updateGravity();});
	game.addUpdate(1, [](){
		physic2D::system::Hitbox hit;
		hit.UpdateHitbox();
		});
	game.addUpdate(100, [](){ecs::Update::UpdateGraphical();});
	game.addUpdate(101, [&screen](){screen.update();});

<<<<<<< HEAD
	createPile(50, grav, 500);
	createPile(50, grav, 1000);

	ID sauce3 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(sauce3);
	game.addComponent<physic2D::component::Pos>(sauce3, physic2D::Vec2(640, 600));
	game.addComponent<physic2D::component::AABB>(sauce3, physic2D::Vec2(1280, 100));
	game.addComponent<physic2D::component::Materials>(sauce3, "Static");
	game.addComponent<physic2D::component::Mass>(sauce3, sauce3);
	game.addComponent<ecs::component::Sprite>(sauce3, std::string("assets/test3.gif"), ecs::core::Vector2<unsigned int>(1280, 100));
	game.addComponent<ecs::component::Drawable>(sauce3, true, 10, GraphicalMethod::Sprite);

	ID sauce10 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(sauce10, physic2D::Vec2(500, 0));
	game.addComponent<physic2D::component::Pos>(sauce10, physic2D::Vec2(0, 350));
	game.addComponent<physic2D::component::Circle>(sauce10, 50);
	game.addComponent<physic2D::component::Materials>(sauce10, "SuperBall");
	game.addComponent<physic2D::component::Mass>(sauce10, sauce10);
	game.addComponent<ecs::component::Sprite>(sauce10, std::string("assets/circle.png"), ecs::core::Vector2<unsigned int>(100, 100));
	game.addComponent<ecs::component::Drawable>(sauce10, true, 10, GraphicalMethod::Sprite);

	ID sauce11 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(sauce11, physic2D::Vec2(1000, 0));
	game.addComponent<physic2D::component::Pos>(sauce11, physic2D::Vec2(0, 200));
	game.addComponent<physic2D::component::Circle>(sauce11, 50);
	game.addComponent<physic2D::component::Materials>(sauce11, "SuperBall");
	game.addComponent<physic2D::component::Mass>(sauce11, sauce11);
	game.addComponent<ecs::component::Sprite>(sauce11, std::string("assets/circle.png"), ecs::core::Vector2<unsigned int>(100, 100));
	game.addComponent<ecs::component::Drawable>(sauce11, true, 10, GraphicalMethod::Sprite);


	// ID test = ecs::entity::Entity::getId();
	// game.addComponent<physic2D::component::Speed>(test, physic2D::Vec2(400, -400));
	// game.addComponent<physic2D::component::Pos>(test, physic2D::Vec2(100, 500));
	// game.addComponent<physic2D::component::AABB>(test, physic2D::Vec2(100, 100));
	// game.addComponent<physic2D::component::Materials>(test, "Wood");
	// game.addComponent<physic2D::component::Mass>(test, test);
	// game.addComponent<ecs::component::Sprite>(test, std::string("assets/test.jpg"), ecs::core::Vector2<unsigned int>(100, 100));
	// game.addComponent<ecs::component::Drawable>(test, true, 10, GraphicalMethod::Sprite);


	// ID test2 = ecs::entity::Entity::getId();
	// game.addComponent<physic2D::component::Speed>(test2, physic2D::Vec2(-400, -400));
	// game.addComponent<physic2D::component::Pos>(test2, physic2D::Vec2(1000, 500));
	// game.addComponent<physic2D::component::AABB>(test2, physic2D::Vec2(100, 100));
	// game.addComponent<physic2D::component::Materials>(test2, "Wood");
	// game.addComponent<physic2D::component::Mass>(test2, test2);
	// game.addComponent<ecs::component::Sprite>(test2, std::string("assets/test2.jpeg"), ecs::core::Vector2<unsigned int>(100, 100));
	// game.addComponent<ecs::component::Drawable>(test2, true, 10, GraphicalMethod::Sprite);
	

	grav.addObject(sauce10);
	grav.addObject(sauce11);

	// grav.addObject(test);
	// grav.addObject(test2);

=======
	ID sauce = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(sauce, 10, physic2D::Vec2(1, 1));
	game.addComponent<ecs::component::AnimatedSprite>(sauce, std::string("assets")/*, ecs::core::Vector2<unsigned int>(500,500)*/);
	game.addComponent<ecs::component::Drawable>(sauce, true, 10, GraphicalMethod::AnimatedSprite);
>>>>>>> 00099fb21481ce0b30bdd640c775db85479e72ce
	while(screen.isOpen()) {

		long time = ecs::Time::get(TimeUnit::MicroSeconds);

		game.update();
		// std::this_thread::sleep_for (std::chrono::seconds(1));
		auto x = static_cast<unsigned int>(16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(x));
		// std::cout << 100 * (16666 - x) / 16666 << std::endl;
	}
	
	return 0;
}
