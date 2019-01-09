//
// Created by seb on 09/01/19.
//

#pragma once

enum class GraphicalMethod {
	None,
	Sprite,
	AnimatedSprite,
	AnimatedSpriteList,
	AnimatedSpriteMap
};

namespace ecs { namespace component {
	struct Drawable {
		Drawable() {
			this->layer = -10;
			this->method = GraphicalMethod::None;
		}
		Drawable(bool drawable, int layer, GraphicalMethod method) {
			this->drawable = drawable;
			this->layer = -10;
			this->method = method;
		}
		bool		drawable;
		int 		layer;
		GraphicalMethod	method;
	};
}}