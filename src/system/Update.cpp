//
// Created by seb on 09/01/19.
//

#include "component/graphical/AnimatedSprite.hpp"
#include "ecs/Graphic.hpp"
#include "component/graphical/Drawable.hpp"
#include "component/graphical/Sprite.hpp"
#include "physic2D/component/Pos.hpp"
#include "ecs/Ecs.hpp"
#include "Update.hpp"

namespace ecs {
	void Update::UpdateGraphical() {
		auto &ecs = ecs::Ecs::get();
		auto win = ecs::Graphic::getWindow();
		auto &pos = ecs.getComponentMap<physic2D::component::Pos>();
		auto &drawable = ecs.getComponentMap<ecs::component::Drawable>();

		auto &sprite = ecs.getComponentMap<ecs::component::Sprite>();
		auto &animatedSprite = ecs.getComponentMap<ecs::component::AnimatedSprite>();

		auto ids = ecs.filter<physic2D::component::Pos, ecs::component::Drawable>();
		for (auto it = ids.begin(); it != ids.end(); it++)
			if (!drawable[*it].drawable)
				ids.erase(it);
		std::sort (ids.begin(), ids.end(), [&drawable](ID i,ID j) {return (drawable[i].layer < drawable[j].layer);});

		long time;
		for (auto id : ids) {
			if (drawable[id].method == GraphicalMethod::Sprite){
				sprite[id].sprite->setPosition(pos[id]._pos.x, pos[id]._pos.y);
				sprite[id].sprite->setRotation(drawable[id].rotation);
				win->draw(*sprite[id].sprite);
			} else if (drawable[id].method == GraphicalMethod::AnimatedSprite) {
				time = ecs::Time::get(TimeUnit::MicroSeconds);
				auto &asp = animatedSprite[id];
				if (asp.last + asp.delta < time) {
					asp.pos = (asp.pos + 1) % asp.frame;
					asp.last = time;
				}
				auto sprt = asp.sprites[asp.pos].sprite;
				sprt->setPosition(pos[id]._pos.x, pos[id]._pos.y);
				sprt->setRotation(drawable[id].rotation);
				win->draw(*sprt);
			} else if (drawable[id].method == GraphicalMethod::None) {
				std::cout << "Undefinded GraphicalMethod for ID: " << id << ". Component won't be displayed." << std::endl;
			}
		}
	}
}