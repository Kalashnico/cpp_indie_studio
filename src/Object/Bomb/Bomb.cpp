//
// Created by Nicolas Guerin on 17/05/2018.
//

#include <iostream>
#include "Bomb.hpp"
#include "SoundManager.hpp"

namespace object {

Bomb::Bomb(int posx, int posy, int blast, ::map::Map *map, Gfx *gfx, Player *parent)
	: AObject(BOMB),
	_posx{posx},
	_posy{posy},
	_blastSize{blast},
	_map{map},
	_gfx{gfx},
	_parent{parent},
	_node{nullptr},
	_detonate{false},
	_hasExploded{false}
{
	auto modelPath = "./media/models/bomb/bomb.obj";
	irr::core::vector3df modelSize = {0.5f, 0.5f, 0.5f};
	irr::core::vector3df pos = {(float)posy, 0.f, (float)posx};
	pos -= 6.f;
	pos *= 4.f;
	pos.Y = 0.1f;
	_node = _gfx->drawMesh(modelPath, "", false, "bomb " + std::to_string(_posx) + " " + std::to_string(_posy), pos);
	_node->setScale(modelSize);

	_begin = std::clock();
}

Bomb::~Bomb()
{
	_gfx->deleteElement("bomb " + std::to_string(_posx) + " " + std::to_string(_posy));
}

void Bomb::update() noexcept
{
	if (toBeDestroyed())
		return;

	if (_detonate || ((std::clock() - _begin) / (double) CLOCKS_PER_SEC) >= LIFE) {
		explode();
		return;
	}
}

void Bomb::explode() noexcept
{
	if (_hasExploded)
		return;

	_hasExploded = true;

	sound::SoundManager::getInstance().playBomb();
	_parent->bombExploaded();
	_map->explodeBomb(_posx, _posy, _blastSize);
}

	int Bomb::getBlast() noexcept
	{
		return _blastSize;
	}
}
