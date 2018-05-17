//
// Created by Nicolas Guerin on 14/05/2018.
//

#pragma once

#include <string>
#include <array>

//Theses are the paths to loot meshs
static std::array<std::string, 4> const meshPaths {"BOMB PATH",
						   "FIRE PATH",
						   "SPEED PATH",
						   "WALL PATH"};
//What kind of loot it is
enum LootCategory {
	BOMB_UP,
	FIRE_UP,
	SPEED_UP,
	WALL_PASS
};


class Loot {
	public:
		Loot();
		~Loot();

		//Getters
		LootCategory getCategory() const noexcept { return _category; };
		std::string getPathToMesh() const noexcept { return _pathToMesh; };

	private:
		LootCategory _category;
		std::string _pathToMesh;

};
