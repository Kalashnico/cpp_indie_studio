//
// Created by Nicolas Guerin on 17/05/2018.
//

#include "Bomb.hpp"

namespace object {

Bomb::Bomb(int posx, int posy, int blast, map::Map *map)
	: AObject("PATH BOMB MESH", BOMB),
	_posx{posx},
	_posy{posy},
	_blastSize{blast},
	_map{map},
	_detonate{false},
	_hasExploded{false}
{
	_begin = std::clock();
}

Bomb::~Bomb()
{}

void Bomb::update() noexcept
{
	if (toBeDestroyed())
		return;

	if (_detonate || ((std::clock() - _begin) / (double) CLOCKS_PER_SEC) >= LIFE) {
		explode();
		return;
	}

	if (((clock() - _begin) / (double) CLOCKS_PER_SEC) >= CYCLE)
		_pathToMesh = "PATH BOMB 2";
	else
		_pathToMesh = "PATH BOMB 1";
}

void Bomb::explode() noexcept
{
	if (_hasExploded)
		return;

	_hasExploded = true;

	_pathToMesh = "PATH BOMB EXPLOSION";

	_map->explodeBomb(_posx, _posy, _blastSize);
}

}
