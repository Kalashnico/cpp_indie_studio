//
// Created by Nicolas Guerin on 17/05/2018.
//

#include <iostream>
#include "Bomb.hpp"

namespace object {

Bomb::Bomb(int posx, int posy, int blast, map::Map *map)
	: AObject("PATH BOMB MESH", BOMB),
	_posx{posx},
	_posy{posy},
	_blastSize{blast},
	_map{map},
	_detonate{false}
{}

Bomb::~Bomb()
{}

void Bomb::bombFuse() noexcept
{
	auto begin = std::clock();

	while (true) {
		if (this->_detonate || ((std::clock() - begin) / (double) CLOCKS_PER_SEC) >= 3.0)
			break;
		if (((clock() - begin) / (double) CLOCKS_PER_SEC) >= 0.5)
			_pathToMesh = "PATH BOMB 2";
		else
			_pathToMesh = "PATH BOMB 1";
	}
	_pathToMesh = "PATH BOMB EXPLOSION";

	_map->explodeBomb(_posx, _posy, _blastSize);
}

}
