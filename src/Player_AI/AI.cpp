/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Created by tclemenceau,
*/

#include <vector>
#include <iostream>
#include "AI.hpp"

AI::AI(::map::Map *map, std::string mesh, Type type, Gfx *gfx, playerSprite_e playerType, float x,
	float y, float z, bool useController,
	unsigned long playerNb) : _player(mesh, type, gfx, playerType, x, y, z, useController, playerNb), _map(map), _to_go(NONE)
{
}

AI::~AI()
{
}

object::Player &AI::getPlayer()
{
	return _player;
}

void AI::update()
{
	if (_to_go == NONE) {
		_past_co = _player.getPosition();
		_to_go = FORWARD;
	} else {
		this->moveCase(_to_go);
	}
//	this->find_closest_player();
}

void AI::moveCase(rotationDirection_e dir, float spd)
{
	const vector2di tmp = _player.getPosition();

	switch (dir) {
	case BACKWARD:
		if (_past_co.Y - tmp.Y != -1)
			_player.move(dir, spd);
		else
			_to_go = NONE;
		break;
	case FORWARD:
		if (_past_co.Y - tmp.Y != 1)
			_player.move(dir, spd);
		else
			_to_go = NONE;
		break;
	case LEFT:
		if (_past_co.X - tmp.X != 1)
			_player.move(dir, spd);
		else
			_to_go = NONE;
		break;
	case RIGHT:
		if (_past_co.X - tmp.X != -1)
			_player.move(dir, spd);
		else
			_to_go = NONE;
		break;
	default:
		break;
	}
}

void AI::find_closest_player()
{
	/*std::array<int, 2> xy{};
	std::vector<std::unique_ptr<map::Tile>> map;

	map = _map->getMap();
	for (auto &tile : map) {
		for (auto &object : tile.get()->getObjects())
			if ((object.get()->getType() == PLAYER1 ||
				object.get()->getType() == PLAYER2 ||
				object.get()->getType() == PLAYER3 ||
				object.get()->getType() == PLAYER4) &&
				object.get()->getType() !=
					_player.getType())
				return;
	}*/
}
