//
// Created by Nicolas Guerin on 17/05/2018.
//

#include "Fire.hpp"

namespace object {

Fire::Fire(size_t posx, size_t posy, ::map::Map *map, Gfx *gfx)
	: AObject("BOMB PATH", FIRE),
	_posx{posx},
	_posy{posy},
	_map{map},
	_gfx{gfx},
	_node{nullptr},
	_dissipated{false}
{
	auto modelPath = "./media/models/fire/WpnMetaridleyFireballS.obj";
	vector3df modelSize = {0.25f, 0.25f, 0.25f};
	vector3df pos = {(float)posy, 0.f, (float)posx};
	pos -= 6.f;
	pos *= 4.f;
	pos.Y = 0.1f;
	_node = _gfx->drawMesh(modelPath, "", false, "fire " + std::to_string(_posx) + " " + std::to_string(_posy), pos);
	_node->setScale(modelSize);

	_begin = std::clock();
}

Fire::~Fire()
{
	_gfx->deleteElement("fire " + std::to_string(_posx) + " " + std::to_string(_posy));
}

void Fire::resetGfx() noexcept
{
	_begin = std::clock();
}

void Fire::update() noexcept
{
	if (toBeDestroyed())
		return;

	if (((std::clock() - _begin) / (double) CLOCKS_PER_SEC) >= LIFE) {
		dissipate();
		return;
	}
}

void Fire::dissipate() noexcept
{
	if (_dissipated)
		return;

	_dissipated = true;

	_map->removeObjectFromTile(_posx, _posy, FIRE);
}

}
