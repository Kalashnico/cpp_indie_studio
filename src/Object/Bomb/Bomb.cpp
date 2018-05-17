//
// Created by Nicolas Guerin on 17/05/2018.
//

#include "Bomb.hpp"

namespace object {

Bomb::Bomb(int posx, int posy, int blast, map::Map &map) : AObject("PATH BOMB MESH", BOMB),
							   _posx{posx},
							   _posy{posy},
							   _blastSize{blast},
							   _map{map},
							   _detonate{false}
{
	_thread = std::thread(&bombFuse, this);
}

Bomb::~Bomb()
{
	_thread.join();
}

void Bomb::bombFuse()
{
	auto begin = std::clock();

	while (true) {
		if (this->_detonate || ((std::clock() - begin) / CLOCKS_PER_SEC) >= 3)
			break;
		if (((clock() - begin) / CLOCKS_PER_SEC) >= 0.5)
			_pathToMesh = "PATH BOMB 2";
		else
			_pathToMesh = "PATH BOMB 1";

	}
	_pathToMesh = "PATH BOMB EXPLOSION";

	//TODO CALL MAP FUNC TO DESTROY BOMB
}
}
