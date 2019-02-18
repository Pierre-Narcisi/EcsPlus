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
#include <system/Graphical.hpp>
#include "src/physic2D/system/Hitbox.hpp"
#include "src/physic2D/system/Physic2D.hpp"
#include "src/physic2D/system/Gravity.hpp"
#include "src/physic2D/component/AABB.hpp"
#include "src/physic2D/component/Poly.hpp"
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

void createBillard(float size) {
	auto &game = ecs::Ecs::get();
	physic2D::Vec2 pos1 = physic2D::Vec2(400, 400);

	ID Ball8 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball8);
	game.addComponent<physic2D::component::Pos>(Ball8, pos1);
	game.addComponent<physic2D::component::Circle>(Ball8, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball8, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball8, std::string("assets/BOULES/b8.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball8, Ball8);
	game.addComponent<ecs::component::Drawable>(Ball8, true, 10, GraphicalMethod::Sprite);

	ID Ball7 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball7);
	game.addComponent<physic2D::component::Pos>(Ball7, physic2D::Vec2(pos1.x - size * 2, pos1.y - size));
	game.addComponent<physic2D::component::Circle>(Ball7, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball7, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball7, std::string("assets/BOULES/b7.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball7, Ball7);
	game.addComponent<ecs::component::Drawable>(Ball7, true, 10, GraphicalMethod::Sprite);

	ID Ball14 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball14);
	game.addComponent<physic2D::component::Pos>(Ball14, physic2D::Vec2(pos1.x - size * 2, pos1.y + size));
	game.addComponent<physic2D::component::Circle>(Ball14, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball14, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball14, std::string("assets/BOULES/b14.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball14, Ball14);
	game.addComponent<ecs::component::Drawable>(Ball14, true, 10, GraphicalMethod::Sprite);

	ID Ball9 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball9);
	game.addComponent<physic2D::component::Pos>(Ball9, physic2D::Vec2(pos1.x + size * 2, pos1.y - size));
	game.addComponent<physic2D::component::Circle>(Ball9, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball9, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball9, std::string("assets/BOULES/b9.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball9, Ball9);
	game.addComponent<ecs::component::Drawable>(Ball9, true, 10, GraphicalMethod::Sprite);

	ID Ball2 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball2);
	game.addComponent<physic2D::component::Pos>(Ball2, physic2D::Vec2(pos1.x + size * 2, pos1.y + size));
	game.addComponent<physic2D::component::Circle>(Ball2, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball2, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball2, std::string("assets/BOULES/b2.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball2, Ball2);
	game.addComponent<ecs::component::Drawable>(Ball2, true, 10, GraphicalMethod::Sprite);

	ID Ball1 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball1);
	game.addComponent<physic2D::component::Pos>(Ball1, physic2D::Vec2(pos1.x + size * 4, pos1.y));
	game.addComponent<physic2D::component::Circle>(Ball1, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball1, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball1, std::string("assets/BOULES/b1.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball1, Ball1);
	game.addComponent<ecs::component::Drawable>(Ball1, true, 10, GraphicalMethod::Sprite);

	ID Ball3 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball3);
	game.addComponent<physic2D::component::Pos>(Ball3, physic2D::Vec2(pos1.x, pos1.y + size * 2));
	game.addComponent<physic2D::component::Circle>(Ball3, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball3, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball3, std::string("assets/BOULES/b3.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball3, Ball3);
	game.addComponent<ecs::component::Drawable>(Ball3, true, 10, GraphicalMethod::Sprite);
	
	ID Ball10 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball10);
	game.addComponent<physic2D::component::Pos>(Ball10, physic2D::Vec2(pos1.x, pos1.y - size * 2));
	game.addComponent<physic2D::component::Circle>(Ball10, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball10, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball10, std::string("assets/BOULES/b10.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball10, Ball10);
	game.addComponent<ecs::component::Drawable>(Ball10, true, 10, GraphicalMethod::Sprite);

	ID Ball11 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball11);
	game.addComponent<physic2D::component::Pos>(Ball11, physic2D::Vec2(pos1.x - size * 2, pos1.y - size * 3));
	game.addComponent<physic2D::component::Circle>(Ball11, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball11, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball11, std::string("assets/BOULES/b11.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball11, Ball11);
	game.addComponent<ecs::component::Drawable>(Ball11, true, 10, GraphicalMethod::Sprite);

	ID Ball4 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball4);
	game.addComponent<physic2D::component::Pos>(Ball4, physic2D::Vec2(pos1.x - size * 2, pos1.y + size * 3));
	game.addComponent<physic2D::component::Circle>(Ball4, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball4, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball4, std::string("assets/BOULES/b4.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball4, Ball4);
	game.addComponent<ecs::component::Drawable>(Ball4, true, 10, GraphicalMethod::Sprite);

	ID Ball5 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball5);
	game.addComponent<physic2D::component::Pos>(Ball5, physic2D::Vec2(pos1.x - size * 4, pos1.y - size * 4));
	game.addComponent<physic2D::component::Circle>(Ball5, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball5, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball5, std::string("assets/BOULES/b5.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball5, Ball5);
	game.addComponent<ecs::component::Drawable>(Ball5, true, 10, GraphicalMethod::Sprite);

	ID Ball13 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball13);
	game.addComponent<physic2D::component::Pos>(Ball13, physic2D::Vec2(pos1.x - size * 4, pos1.y - size * 2));
	game.addComponent<physic2D::component::Circle>(Ball13, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball13, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball13, std::string("assets/BOULES/b13.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball13, Ball13);
	game.addComponent<ecs::component::Drawable>(Ball13, true, 10, GraphicalMethod::Sprite);

	ID Ball15 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball15);
	game.addComponent<physic2D::component::Pos>(Ball15, physic2D::Vec2(pos1.x - size * 4, pos1.y));
	game.addComponent<physic2D::component::Circle>(Ball15, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball15, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball15, std::string("assets/BOULES/b15.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball15, Ball15);
	game.addComponent<ecs::component::Drawable>(Ball15, true, 10, GraphicalMethod::Sprite);

	ID Ball6 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball6);
	game.addComponent<physic2D::component::Pos>(Ball6, physic2D::Vec2(pos1.x - size * 4, pos1.y + size * 2));
	game.addComponent<physic2D::component::Circle>(Ball6, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball6, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball6, std::string("assets/BOULES/b6.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball6, Ball6);
	game.addComponent<ecs::component::Drawable>(Ball6, true, 10, GraphicalMethod::Sprite);

	ID Ball12 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball12);
	game.addComponent<physic2D::component::Pos>(Ball12, physic2D::Vec2(pos1.x - size * 4, pos1.y + size * 4));
	game.addComponent<physic2D::component::Circle>(Ball12, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball12, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball12, std::string("assets/BOULES/b12.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball12, Ball12);
	game.addComponent<ecs::component::Drawable>(Ball12, true, 10, GraphicalMethod::Sprite);

	ID sauce3 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(sauce3);
	game.addComponent<physic2D::component::Pos>(sauce3, physic2D::Vec2(640, 550));
	game.addComponent<physic2D::component::AABB>(sauce3, physic2D::Vec2(1280, 100), false, true);
	game.addComponent<physic2D::component::Materials>(sauce3, "Static");
	game.addComponent<physic2D::component::Mass>(sauce3, sauce3);
	game.addComponent<ecs::component::Sprite>(sauce3, std::string("assets/test3.gif"), ecs::core::Vector2<unsigned int>(1280, 100));
	game.addComponent<ecs::component::Drawable>(sauce3, true, 10, GraphicalMethod::Sprite);

	ID sauce4 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(sauce4);
	game.addComponent<physic2D::component::Pos>(sauce4, physic2D::Vec2(640, 250));
	game.addComponent<physic2D::component::AABB>(sauce4, physic2D::Vec2(1280, 100), false, true);
	game.addComponent<physic2D::component::Materials>(sauce4, "Static");
	game.addComponent<physic2D::component::Mass>(sauce4, sauce4);
	game.addComponent<ecs::component::Sprite>(sauce4, std::string("assets/test3.gif"), ecs::core::Vector2<unsigned int>(1280, 100));
	game.addComponent<ecs::component::Drawable>(sauce4, true, 10, GraphicalMethod::Sprite);
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
	game.addUpdate(101, [](){ecs::Graphical::DrawPixels();});
	game.addUpdate(110, [&screen](){screen.update();});

	ID Blanche = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Blanche, physic2D::Vec2(-400, 0));
	game.addComponent<physic2D::component::Pos>(Blanche, physic2D::Vec2(1000, 400));
	game.addComponent<physic2D::component::Circle>(Blanche, 10, false, true);
	game.addComponent<physic2D::component::Materials>(Blanche, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Blanche, std::string("assets/BOULES/bblanche.png"), ecs::core::Vector2<unsigned int>(10 * 2, 10 * 2));
	game.addComponent<physic2D::component::Mass>(Blanche, Blanche);
	game.addComponent<ecs::component::Drawable>(Blanche, true, 10, GraphicalMethod::Sprite);


	createBillard(10);

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
