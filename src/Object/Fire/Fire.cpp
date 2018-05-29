//
// Created by Nicolas Guerin on 17/05/2018.
//

#include "Fire.hpp"

namespace object {

Fire::Fire(size_t posx, size_t posy, ::map::Map *map)
	: AObject("BOMB PATH", FIRE),
	_posx{posx},
	_posy{posy},
	_map{map},
	_dissipated{false}
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
