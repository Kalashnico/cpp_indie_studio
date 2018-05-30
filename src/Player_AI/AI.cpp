/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Created by tclemenceau,
*/

#include <random>
#include <vector>
#include <iostream>
#include "AI.hpp"

namespace object {

AI::AI(::map::Map *map, std::string mesh, Type type, Gfx *gfx, playerSprite_e playerType, float x,
	float y, float z, bool useController,
	unsigned long playerNb) : AObject(mesh, type), _player(map, mesh, type, gfx, playerType, x, y, z, useController, playerNb), _map(map), _to_go(NONE), _closest_player(-1, -1)
{
}

AI::~AI()
{
}

object::Player &AI::getPlayer()
{
	return _player;
}

void AI::update() noexcept
{
	if (_to_go == NONE) {
		this->find_closest_player();
		_past_co = _player.getPosition();
		set_direction();
		std::cout << _closest_player.X << " " << _closest_player.Y << std::endl;
	}
	this->moveCase(_to_go);
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
	auto myMap = &(_map->getMap());
	object::Player *tmp;
	int distance;
	int distance_tmp;

	for (auto &tile : *myMap) {
		for (auto &object : tile->getObjects())
			if ((object->getType() == PLAYER1 ||
				object->getType() == PLAYER2 ||
				object->getType() == PLAYER3 ||
				object->getType() == PLAYER4) && object->getType() !=
					_player.getType()) {
				tmp = dynamic_cast<object::Player*>(object.get());
				std::cout << "FUCK YOU" << std::endl;
				if (_closest_player.X == -1 || _closest_player.Y == -1) {
					_closest_player = tmp->getPosition();
					continue;
				}
				distance = abs(_closest_player.X - _player.getPosition().X) + abs(_closest_player.Y - _player.getPosition().Y);
				distance_tmp = abs(tmp->getPosition().X - _player.getPosition().X) + abs(tmp->getPosition().Y - _player.getPosition().Y);
				_closest_player = (distance_tmp <= distance) ? tmp->getPosition() : _closest_player;
		}
	}
}

void AI::set_direction()
{
	std::random_device randomDevice;
	std::mt19937 engine(randomDevice());
	std::uniform_int_distribution<> distribution(0, 1);
	vector2di tmp = _player.getPosition();
	bool done = false;

	while (!done) {
		if (distribution(engine) == 0)
			done = move_X(tmp);
		else
			done = move_Y(tmp);
	}
}

bool AI::move_X(vector2di tmp)
{
	if (tmp.X < _closest_player.X) {
		if (tmp.X + 1 <= MAP_SIZE && _map->getTileAt(static_cast<size_t>(tmp.X + 1),
			static_cast<size_t>(tmp.Y))->getObject(WALL) == nullptr) {
			_to_go = RIGHT;
			return true;
		} else {
			return false;
		}
	} else {
		if (tmp.X - 1 >= 0 && _map->getTileAt(static_cast<size_t>(tmp.X - 1),
			static_cast<size_t>(tmp.Y))->getObject(WALL) == nullptr) {
			_to_go = RIGHT;
			return true;
		} else {
			return false;
		}
	}
}

bool AI::move_Y(vector2di tmp)
{
	if (tmp.Y < _closest_player.Y) {
		if (tmp.Y + 1 <= MAP_SIZE && _map->getTileAt(static_cast<size_t>(tmp.X),
			static_cast<size_t>(tmp.Y + 1))->getObject(WALL) == nullptr) {
			_to_go = RIGHT;
			return true;
		} else {
			return false;
		}
	} else {
		if (tmp.Y - 1 >= 0 && _map->getTileAt(static_cast<size_t>(tmp.X),
			static_cast<size_t>(tmp.Y - 1))->getObject(WALL) == nullptr) {
			_to_go = RIGHT;
			return true;
		} else {
			return false;
		}
	}
}

}
