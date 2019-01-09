#pragma once

#include "../Vec2/vec2.hpp"
#include <string>
#include <unordered_map>

namespace physic2D { 
	std::unordered_map<std::string, std::pair<float, float>> Mat = {
		{ "Rock", {0.6, 0.1} },
		{ "Wood", {0.3, 0.2} },
		{ "Metal", {1.2, 0.05} },
		{ "BouncyBall", {0.3, 0.8} },
		{ "SuperBall", {0.3, 0.95} },
		{ "Pillow", {0.1, 0.2} },
		{ "Static", {0.0, 0.4} },
	};
	namespace component {

		struct Materials {
			Materials() {
				_name = "Rock";
			}

			Materials(std::string name) {
				_name = name;
			}

			std::string _name;
		};
	}
}