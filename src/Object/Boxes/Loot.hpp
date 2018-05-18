//
// Created by Nicolas Guerin on 14/05/2018.
//

#pragma once

#include <string>
#include <array>
#include "AObject.hpp"

namespace object {

//Theses are the paths to loot meshs
static std::array<std::string, 4> const meshPaths {"BOMB PATH",
						   "FIRE PATH",
						   "SPEED PATH",
						   "WALL PATH"};

class Loot : public AObject {
	public:
		Loot();
		~Loot();

		//Getters
		LootCategory getLootCategory() const noexcept { return _category; };

	private:
		LootCategory _category;

		//Member Function
		std::string setPathToMesh() noexcept;

};
}
