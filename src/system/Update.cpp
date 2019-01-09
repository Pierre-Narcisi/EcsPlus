//
// Created by seb on 09/01/19.
//

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

		auto ids = ecs.filter<physic2D::component::Pos, ecs::component::Drawable>();
		for (auto it = ids.begin(); it != ids.end(); it++)
			if (!drawable[*it].drawable)
				ids.erase(it);
		std::sort (ids.begin(), ids.end(), [&drawable](ID i,ID j) {return (drawable[i].layer < drawable[j].layer);});

		for (auto id : ids) {
			switch (drawable[id].method){
				case GraphicalMethod::Sprite :
					sprite[id].sprite->setPosition(pos[id]._pos.getX(), pos[id]._pos.getY());
					win->draw(sprite[id].sprite);
				case GraphicalMethod::None :
					std::cout << "Undefinded GraphicalMethod for ID: " << id << ". Component won't be displayed." << std::endl;
			}
		}
	}
}