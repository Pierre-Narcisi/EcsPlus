#include "Pool.hpp"


Pool::Pool(float size) {
	auto &game = ecs::Ecs::get();
	physic2D::Vec2 pos1 = physic2D::Vec2(400, 400);
	auto &screen = ecs::Graphic::get();


	ID Blanche = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Blanche, physic2D::Vec2(0, 0));
	game.addComponent<physic2D::component::Pos>(Blanche, physic2D::Vec2(1000, 400));
	game.addComponent<physic2D::component::Circle>(Blanche, size, false, true);
	game.addComponent<physic2D::component::Slow>(Blanche, 40);
	game.addComponent<physic2D::component::Materials>(Blanche, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Blanche, std::string("assets/BOULES/bblanche.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Blanche, Blanche);
	game.addComponent<ecs::component::Drawable>(Blanche, true, 100, GraphicalMethod::Sprite);

	ID table = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Pos>(table, physic2D::Vec2(screen.getWindow()->getSize().x / 2, screen.getWindow()->getSize().y / 2));
	game.addComponent<ecs::component::Sprite>(table, std::string("assets/pool.png"), ecs::core::Vector2<unsigned int>(screen.getWindow()->getSize().x, screen.getWindow()->getSize().y));
	game.addComponent<physic2D::component::Mass>(table, table);
	game.addComponent<ecs::component::Drawable>(table, true, 5, GraphicalMethod::Sprite);

	Balls(size);
	Walls(10, Blanche);

	ID id = ecs::entity::Entity::getId();
	game.addComponent<ecs::component::Mouse>(id);
	game.addComponent<ecs::component::Keyboard>(id);
	auto &mouse = game.getComponentMap<ecs::component::Mouse>()[id];

	mouse.mouseMap[KeyMouse::LCLICK] = std::pair<bool, std::function<void(bool, ID)>>(false, [&game, Blanche](bool state, ID id){
		static long _lastTime = 0;
		long newTime= ecs::Time::get(TimeUnit::Seconds);

		if (!state || newTime - _lastTime < 2)
			return;
		_lastTime = newTime;
		auto &pos = game.getComponentMap<ecs::component::Mouse>()[id].position;
		auto &posB = game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos;
		physic2D::Vec2 v = physic2D::Vec2(posB.x - pos.x, posB.y - pos.y);
		float dist = v.length() * 3;
		if (dist > 50 * 30)
			dist = 50 * 30;
		float angle = std::atan2(v.x, v.y);

		game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.x += sinf(angle) * dist;
		game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.y += cosf(angle) * dist;
	});

	auto &keyboard = game.getComponentMap<ecs::component::Keyboard>()[id];
	keyboard.keyMap[KeyKeyboard::UP_ARROW] = std::pair<bool, std::function<void(bool, ID)>>(false, [&game, Blanche](bool state, ID id){
		if (!state)
			return;
		game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y += -1;
		// std::cout << game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x << "\t" << game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y << std::endl;
	});
	keyboard.keyMap[KeyKeyboard::LEFT_ARROW] = std::pair<bool, std::function<void(bool, ID)>>(false, [&game, Blanche](bool state, ID id){
		if (!state)
			return;
		game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x += -1;
		// std::cout << game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x << "\t" << game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y << std::endl;
	});
	keyboard.keyMap[KeyKeyboard::DOWN_ARROW] = std::pair<bool, std::function<void(bool, ID)>>(false, [&game, Blanche](bool state, ID id){
		if (!state)
			return;
		game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y += 1;
		// std::cout << game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x << "\t" << game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y << std::endl;
	});
	keyboard.keyMap[KeyKeyboard::RIGHT_ARROW] = std::pair<bool, std::function<void(bool, ID)>>(false, [&game, Blanche](bool state, ID id){
		if (!state)
			return;
		game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x += 1;
		// std::cout << game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x << "\t" << game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y << std::endl;
	});
	keyboard.keyMap[KeyKeyboard::SPACE] = std::pair<bool, std::function<void(bool, ID)>>(false, [&game, Blanche](bool state, ID id){
		if (!state)
			return;
		game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x = 1000;
		game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y = 400;
		game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.x = 0;
		game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.y = 0;
	});
}

void Pool::Balls(float size) {
	auto &game = ecs::Ecs::get();
	physic2D::Vec2 pos1 = physic2D::Vec2(400, 400);

	ID Ball8 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball8);
	game.addComponent<physic2D::component::Pos>(Ball8, pos1);
	game.addComponent<physic2D::component::Circle>(Ball8, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball8, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball8, std::string("assets/BOULES/b8.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball8, Ball8);
	game.addComponent<physic2D::component::Slow>(Ball8, 40);
	game.addComponent<ecs::component::Drawable>(Ball8, true, 10, GraphicalMethod::Sprite);

	ID Ball7 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball7);
	game.addComponent<physic2D::component::Pos>(Ball7, physic2D::Vec2(pos1.x - size * 2, pos1.y - size));
	game.addComponent<physic2D::component::Circle>(Ball7, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball7, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball7, std::string("assets/BOULES/b7.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball7, Ball7);
	game.addComponent<physic2D::component::Slow>(Ball7, 40);
	game.addComponent<ecs::component::Drawable>(Ball7, true, 10, GraphicalMethod::Sprite);

	ID Ball14 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball14);
	game.addComponent<physic2D::component::Pos>(Ball14, physic2D::Vec2(pos1.x - size * 2, pos1.y + size));
	game.addComponent<physic2D::component::Circle>(Ball14, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball14, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball14, std::string("assets/BOULES/b14.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball14, Ball14);
	game.addComponent<physic2D::component::Slow>(Ball14, 40);
	game.addComponent<ecs::component::Drawable>(Ball14, true, 10, GraphicalMethod::Sprite);

	ID Ball9 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball9);
	game.addComponent<physic2D::component::Pos>(Ball9, physic2D::Vec2(pos1.x + size * 2, pos1.y - size));
	game.addComponent<physic2D::component::Circle>(Ball9, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball9, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball9, std::string("assets/BOULES/b9.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball9, Ball9);
	game.addComponent<physic2D::component::Slow>(Ball9, 40);
	game.addComponent<ecs::component::Drawable>(Ball9, true, 10, GraphicalMethod::Sprite);

	ID Ball2 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball2);
	game.addComponent<physic2D::component::Pos>(Ball2, physic2D::Vec2(pos1.x + size * 2, pos1.y + size));
	game.addComponent<physic2D::component::Circle>(Ball2, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball2, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball2, std::string("assets/BOULES/b2.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball2, Ball2);
	game.addComponent<physic2D::component::Slow>(Ball2, 40);
	game.addComponent<ecs::component::Drawable>(Ball2, true, 10, GraphicalMethod::Sprite);

	ID Ball1 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball1);
	game.addComponent<physic2D::component::Pos>(Ball1, physic2D::Vec2(pos1.x + size * 4, pos1.y));
	game.addComponent<physic2D::component::Circle>(Ball1, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball1, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball1, std::string("assets/BOULES/b1.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball1, Ball1);
	game.addComponent<physic2D::component::Slow>(Ball1, 40);
	game.addComponent<ecs::component::Drawable>(Ball1, true, 10, GraphicalMethod::Sprite);

	ID Ball3 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball3);
	game.addComponent<physic2D::component::Pos>(Ball3, physic2D::Vec2(pos1.x, pos1.y + size * 2));
	game.addComponent<physic2D::component::Circle>(Ball3, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball3, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball3, std::string("assets/BOULES/b3.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball3, Ball3);
	game.addComponent<physic2D::component::Slow>(Ball3, 40);
	game.addComponent<ecs::component::Drawable>(Ball3, true, 10, GraphicalMethod::Sprite);

	ID Ball10 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball10);
	game.addComponent<physic2D::component::Pos>(Ball10, physic2D::Vec2(pos1.x, pos1.y - size * 2));
	game.addComponent<physic2D::component::Circle>(Ball10, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball10, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball10, std::string("assets/BOULES/b10.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball10, Ball10);
	game.addComponent<physic2D::component::Slow>(Ball10, 40);
	game.addComponent<ecs::component::Drawable>(Ball10, true, 10, GraphicalMethod::Sprite);

	ID Ball11 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball11);
	game.addComponent<physic2D::component::Pos>(Ball11, physic2D::Vec2(pos1.x - size * 2, pos1.y - size * 3));
	game.addComponent<physic2D::component::Circle>(Ball11, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball11, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball11, std::string("assets/BOULES/b11.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball11, Ball11);
	game.addComponent<physic2D::component::Slow>(Ball11, 40);
	game.addComponent<ecs::component::Drawable>(Ball11, true, 10, GraphicalMethod::Sprite);

	ID Ball4 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball4);
	game.addComponent<physic2D::component::Pos>(Ball4, physic2D::Vec2(pos1.x - size * 2, pos1.y + size * 3));
	game.addComponent<physic2D::component::Circle>(Ball4, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball4, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball4, std::string("assets/BOULES/b4.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball4, Ball4);
	game.addComponent<physic2D::component::Slow>(Ball4, 40);
	game.addComponent<ecs::component::Drawable>(Ball4, true, 10, GraphicalMethod::Sprite);

	ID Ball5 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball5);
	game.addComponent<physic2D::component::Pos>(Ball5, physic2D::Vec2(pos1.x - size * 4, pos1.y - size * 4));
	game.addComponent<physic2D::component::Circle>(Ball5, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball5, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball5, std::string("assets/BOULES/b5.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball5, Ball5);
	game.addComponent<physic2D::component::Slow>(Ball5, 40);
	game.addComponent<ecs::component::Drawable>(Ball5, true, 10, GraphicalMethod::Sprite);

	ID Ball13 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball13);
	game.addComponent<physic2D::component::Pos>(Ball13, physic2D::Vec2(pos1.x - size * 4, pos1.y - size * 2));
	game.addComponent<physic2D::component::Circle>(Ball13, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball13, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball13, std::string("assets/BOULES/b13.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball13, Ball13);
	game.addComponent<physic2D::component::Slow>(Ball13, 40);
	game.addComponent<ecs::component::Drawable>(Ball13, true, 10, GraphicalMethod::Sprite);

	ID Ball15 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball15);
	game.addComponent<physic2D::component::Pos>(Ball15, physic2D::Vec2(pos1.x - size * 4, pos1.y));
	game.addComponent<physic2D::component::Circle>(Ball15, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball15, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball15, std::string("assets/BOULES/b15.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball15, Ball15);
	game.addComponent<physic2D::component::Slow>(Ball15, 40);
	game.addComponent<ecs::component::Drawable>(Ball15, true, 10, GraphicalMethod::Sprite);

	ID Ball6 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball6);
	game.addComponent<physic2D::component::Pos>(Ball6, physic2D::Vec2(pos1.x - size * 4, pos1.y + size * 2));
	game.addComponent<physic2D::component::Circle>(Ball6, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball6, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball6, std::string("assets/BOULES/b6.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball6, Ball6);
	game.addComponent<physic2D::component::Slow>(Ball6, 40);
	game.addComponent<ecs::component::Drawable>(Ball6, true, 10, GraphicalMethod::Sprite);

	ID Ball12 = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(Ball12);
	game.addComponent<physic2D::component::Pos>(Ball12, physic2D::Vec2(pos1.x - size * 4, pos1.y + size * 4));
	game.addComponent<physic2D::component::Circle>(Ball12, size, false, true);
	game.addComponent<physic2D::component::Materials>(Ball12, "SuperBall");
	game.addComponent<ecs::component::Sprite>(Ball12, std::string("assets/BOULES/b12.png"), ecs::core::Vector2<unsigned int>(size * 2, size * 2));
	game.addComponent<physic2D::component::Mass>(Ball12, Ball12);
	game.addComponent<physic2D::component::Slow>(Ball12, 40);
	game.addComponent<ecs::component::Drawable>(Ball12, true, 10, GraphicalMethod::Sprite);
}

void Pool::Walls(float size, ID Blanche) {
	auto &game = ecs::Ecs::get();

	ID Wall = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Pos>(Wall, physic2D::Vec2(367.5, 35));
	game.addComponent<physic2D::component::Materials>(Wall, "SuperBall");
	game.addComponent<physic2D::component::Speed>(Wall);
	game.addComponent<physic2D::component::Mass>(Wall);
	game.addComponent<physic2D::component::AABB>(Wall, physic2D::Vec2(465, 100), false, true);

	Wall = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Pos>(Wall, physic2D::Vec2(911.5, 35));
	game.addComponent<physic2D::component::Materials>(Wall, "SuperBall");
	game.addComponent<physic2D::component::Speed>(Wall);
	game.addComponent<physic2D::component::Mass>(Wall);
	game.addComponent<physic2D::component::AABB>(Wall, physic2D::Vec2(465, 100), false, true);

	Wall = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Pos>(Wall, physic2D::Vec2(367.5, 684));
	game.addComponent<physic2D::component::Materials>(Wall, "SuperBall");
	game.addComponent<physic2D::component::Speed>(Wall);
	game.addComponent<physic2D::component::Mass>(Wall);
	game.addComponent<physic2D::component::AABB>(Wall, physic2D::Vec2(465, 100), false, true);

	Wall = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Pos>(Wall, physic2D::Vec2(911.5, 684));
	game.addComponent<physic2D::component::Materials>(Wall, "SuperBall");
	game.addComponent<physic2D::component::Speed>(Wall);
	game.addComponent<physic2D::component::Mass>(Wall);
	game.addComponent<physic2D::component::AABB>(Wall, physic2D::Vec2(465, 100), false, true);

	Wall = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Pos>(Wall, physic2D::Vec2(35, 360));
	game.addComponent<physic2D::component::Materials>(Wall, "SuperBall");
	game.addComponent<physic2D::component::Speed>(Wall);
	game.addComponent<physic2D::component::Mass>(Wall);
	game.addComponent<physic2D::component::AABB>(Wall, physic2D::Vec2(100, 460), false, true);

	Wall = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Pos>(Wall, physic2D::Vec2(1238, 360));
	game.addComponent<physic2D::component::Materials>(Wall, "SuperBall");
	game.addComponent<physic2D::component::Speed>(Wall);
	game.addComponent<physic2D::component::Mass>(Wall);
	game.addComponent<physic2D::component::AABB>(Wall, physic2D::Vec2(100, 460), false, true);

	ID hole = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(hole);
	game.addComponent<physic2D::component::Pos>(hole, physic2D::Vec2(640, 50));
	game.addComponent<physic2D::component::Circle>(hole, size, true, false);
	game.addComponent<physic2D::component::Materials>(hole, "SuperBall");
	game.addComponent<physic2D::component::Mass>(hole);
	game.addComponent<physic2D::component::Script>(hole, [&game, Blanche](ID other){
		if (other != Blanche) {
			game.addDeletionQueue(other);
		} else {
			game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x = 1000;
			game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y = 400;
			game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.x = 0;
			game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.y = 0;
		}
	});
	hole = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(hole);
	game.addComponent<physic2D::component::Pos>(hole, physic2D::Vec2(1192, 83));
	game.addComponent<physic2D::component::Circle>(hole, size, true, false);
	game.addComponent<physic2D::component::Materials>(hole, "SuperBall");
	game.addComponent<physic2D::component::Mass>(hole);
	game.addComponent<physic2D::component::Script>(hole, [&game, Blanche](ID other){
		if (other != Blanche) {
			game.addDeletionQueue(other);
		} else {
			game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x = 1000;
			game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y = 400;
			game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.x = 0;
			game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.y = 0;
		}
	});
	hole = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(hole);
	game.addComponent<physic2D::component::Pos>(hole, physic2D::Vec2(1192, 638));
	game.addComponent<physic2D::component::Circle>(hole, size, true, false);
	game.addComponent<physic2D::component::Materials>(hole, "SuperBall");
	game.addComponent<physic2D::component::Mass>(hole);
	game.addComponent<physic2D::component::Script>(hole, [&game, Blanche](ID other){
		if (other != Blanche) {
			game.addDeletionQueue(other);
		} else {
			game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x = 1000;
			game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y = 400;
			game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.x = 0;
			game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.y = 0;
		}
	});
	hole = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(hole);
	game.addComponent<physic2D::component::Pos>(hole, physic2D::Vec2(640, 672));
	game.addComponent<physic2D::component::Circle>(hole, size, true, false);
	game.addComponent<physic2D::component::Materials>(hole, "SuperBall");
	game.addComponent<physic2D::component::Mass>(hole);
	game.addComponent<physic2D::component::Script>(hole, [&game, Blanche](ID other){
		if (other != Blanche) {
			game.addDeletionQueue(other);
		} else {
			game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x = 1000;
			game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y = 400;
			game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.x = 0;
			game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.y = 0;
		}
	});
	hole = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(hole);
	game.addComponent<physic2D::component::Pos>(hole, physic2D::Vec2(88, 638));
	game.addComponent<physic2D::component::Circle>(hole, size, true, false);
	game.addComponent<physic2D::component::Materials>(hole, "SuperBall");
	game.addComponent<physic2D::component::Mass>(hole);
	game.addComponent<physic2D::component::Script>(hole, [&game, Blanche](ID other){
		if (other != Blanche) {
			game.addDeletionQueue(other);
		} else {
			game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x = 1000;
			game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y = 400;
			game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.x = 0;
			game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.y = 0;
		}
	});
	hole = ecs::entity::Entity::getId();
	game.addComponent<physic2D::component::Speed>(hole);
	game.addComponent<physic2D::component::Pos>(hole, physic2D::Vec2(88, 84));
	game.addComponent<physic2D::component::Circle>(hole, size, true, false);
	game.addComponent<physic2D::component::Materials>(hole, "SuperBall");
	game.addComponent<physic2D::component::Mass>(hole);
	game.addComponent<physic2D::component::Script>(hole, [&game, Blanche](ID other){
		if (other != Blanche) {
			game.addDeletionQueue(other);
		} else {
			game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.x = 1000;
			game.getComponentMap<physic2D::component::Pos>()[Blanche]._pos.y = 400;
			game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.x = 0;
			game.getComponentMap<physic2D::component::Speed>()[Blanche]._speed.y = 0;
		}
	});
}