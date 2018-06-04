//
// Created by Nicolas Guerin on 14/05/2018.
//

#include <iostream>
#include <random>
#include "Loot.hpp"

namespace object {

/**
 * Constructor : Ready to use. It create randomly the loot which will be stored in a box.
 */
Loot::Loot() : AObject(LOOT)
{
	setupLoot();
}

Loot::~Loot()
{}

void Loot::setupLoot() noexcept
{
	std::random_device randomDevice;			// Random device
	std::mt19937 engine(randomDevice());			// Seed
	std::uniform_int_distribution<> distribution(1, 3);	// Range

	if (distribution(engine) < 3) {
		_category = EMPTY;
		return;
	}

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
			_category = EMPTY;
			break;
	}
}
}
