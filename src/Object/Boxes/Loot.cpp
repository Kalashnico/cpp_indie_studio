//
// Created by Nicolas Guerin on 14/05/2018.
//

#include "Loot.hpp"

namespace object {

/**
 * Constructor : Ready to use. It create randomly the loot which will be stored in a box.
 */
Loot::Loot() : AObject(setPathToMesh(), LOOT)
{

}

Loot::~Loot()
{

}

std::string Loot::setPathToMesh() noexcept
{
	auto lootCategory = std::rand() % 4;

	switch (lootCategory) {
		case 0:
			_category = BOMB_UP;
			break;
		case 1:
			_category = FIRE_UP;
			break;
		case 2:
			_category = SPEED_UP;
			break;
		case 3:
			_category = WALL_PASS;
			break;
		default :
			break;
	}
	return meshPaths[_category];
}
}
