//
// Created by Nicolas Guerin on 14/05/2018.
//

#include <random>
#include "Loot.hpp"

namespace object {

/**
 * Constructor : Ready to use. It create randomly the loot which will be stored in a box.
 */
Loot::Loot(int posx, int posy, Gfx *gfx)
	: AObject(LOOT), _posx(posx), _posy(posy), _gfx(gfx)
{
	setupLoot();
}

Loot::~Loot()
{
	_gfx->deleteElement("loot " + std::to_string(_posx) + " " + std::to_string(_posy));
}

void Loot::display() noexcept
{
	irr::core::vector3df pos = {(float)_posy, 0.f, (float)_posx};
	pos -= 6.f;
	pos *= 4.f;
	pos.Y = 1.5f;
	_node = _gfx->drawMesh(_modelPath, "", false, "loot " + std::to_string(_posx) + " " + std::to_string(_posy), pos);
	_node->setScale(_modelSize);
}

void Loot::setupLoot() noexcept
{
	std::random_device randomDevice;			// Random device
	std::mt19937 engine(randomDevice());			// Seed
	std::uniform_int_distribution<> distribution(1, 5);	// Range

	if (distribution(engine) < 0) {
		_category = EMPTY;
		return;
	}

	auto lootCategory = std::rand() % 13;

	if (lootCategory < 4)
		lootCategory = 0;
	else if (lootCategory < 8)
		lootCategory = 1;
	else if (lootCategory < 12)
		lootCategory = 2;
	else if (lootCategory == 12)
		lootCategory = 3;

	lootCategory = 2;

	switch (lootCategory) {
		case 0:
			_category = BOMB_UP;
			_modelPath = "./media/models/bomb/bomb.obj";
			_modelSize = {0.25f, 0.25f, 0.25f};
			break;
		case 1:
			_category = FIRE_UP;
			_modelPath = "./media/models/fire/WpnMetaridleyFireballS.obj";
			_modelSize = {0.15f, 0.15f, 0.15f};
			break;
		case 2:
			_category = SPEED_UP;
			_modelPath = "./media/models/speedup/speed_up_power_up.obj";
			_modelSize = {2.f, 2.f, 2.f};
			break;
		case 3:
			_category = WALL_PASS;
			_modelPath = "./media/models/box/ItmBox00.obj";
			_modelSize = {0.15f, 0.15f, 0.15f};
			break;
		default :
			_category = EMPTY;
			break;
	}
}

}
