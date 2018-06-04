/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Created by tclemenceau,
*/

#include <vector>
#include <iostream>
#include "AI.hpp"

namespace object {

AI::AI(::map::Map *map, Type type, Gfx *gfx, playerSprite_e playerType, float x,
	float y, float z, bool useController,
	unsigned long playerNb) : AObject(type), _player(map, type, gfx, playerType, x, y, z, useController, playerNb), _map(map), _to_go(NONE), _closest_player(-1, -1)
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
		_co_to_go = _player.getPositionFloat();
		set_direction();
		std::cout << _closest_player.X << " " << _closest_player.Y << std::endl;
	}
	this->moveCase(_to_go);
}

void AI::updatePosition(size_t oldx, size_t oldy) noexcept
{
	auto position = _player.getPosition();

	if (position.X != oldx || position.Y != oldy)
		_map->movePlayer(getType(), oldx, oldy, position.X, position.Y);
}

void AI::moveCase(rotationDirection_e dir, float spd)
{
	const vector2df tmp = _player.getPositionFloat();

	std::cout << _co_to_go.X << " " << _co_to_go.Y << " " << tmp.X << " " << tmp.Y << std::endl;

	switch (dir) {
	case BACKWARD:
		if (int(_co_to_go.Y * 10) != int(tmp.Y * 10))
			_player.move(dir, spd);
		else
			_to_go = NONE;
		break;
	case FORWARD:
		if (int(_co_to_go.Y * 10) != int(tmp.Y * 10))
			_player.move(dir, spd);
		else
			_to_go = NONE;
		break;
	case LEFT:
		if (int(_co_to_go.X * 10) != int(tmp.X * 10))
			_player.move(dir, spd);
		else
			_to_go = NONE;
		break;
	case RIGHT:
		if (int(_co_to_go.X * 10) != int(tmp.X * 10))
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

	_closest_player.X = -1;
	_closest_player.Y = -1;
	for (auto &tile : *myMap) {
		for (auto &object : tile->getObjects())
			if ((object->getType() == PLAYER1 ||
				object->getType() == PLAYER2 ||
				object->getType() == PLAYER3 ||
				object->getType() == PLAYER4) && object->getType() !=
					_player.getType()) {
				tmp = dynamic_cast<object::Player*>(object.get());
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
	std::mt19937 engine(_random());
	std::uniform_int_distribution<> distribution(0, 1);
	vector2di tmp = _player.getPosition();
	int tryRemainingX = 2;
	int tryRemainingY = 2;
	bool invertX = false;
	bool invertY = false;
	bool done = false;

	while (!done && tryRemainingX != 0 && tryRemainingY != 0) {
		if ((distribution(engine) == 0 || tryRemainingY == 0) && tryRemainingX != 0) {
			done = move_X(tmp, invertX);
			tryRemainingX -= 1;
			invertX = true;
		} else if (tryRemainingY != 0) {
			done = move_Y(tmp, invertY);
			tryRemainingY -= 1;
			invertY = true;
		}
	}
}

bool AI::move_X(vector2di tmp, bool invert)
{
	if ((tmp.X < _closest_player.X && !invert) || invert) {
		if (tmp.X + 1 <= MAP_SIZE - 1 && !_map->getTileAt(static_cast<size_t>(tmp.X + 1),
			static_cast<size_t>(tmp.Y))->containsSomethings()) {
			_to_go = LEFT;
			_co_to_go.X += 1;
			return true;
		} else {
			return false;
		}
	} else {
		if (tmp.X - 1 >= 0 && !_map->getTileAt(static_cast<size_t>(tmp.X - 1),
			static_cast<size_t>(tmp.Y))->containsSomethings()) {
			_to_go = RIGHT;
			_co_to_go.X -= 1;
			return true;
		} else {
			return false;
		}
	}
}

bool AI::move_Y(vector2di tmp, bool invert)
{
	if ((tmp.Y < _closest_player.Y && !invert) || invert) {
		if (tmp.Y + 1 <= MAP_SIZE - 1 && !_map->getTileAt(static_cast<size_t>(tmp.X),
			static_cast<size_t>(tmp.Y + 1))->containsSomethings()) {
			_to_go = BACKWARD;
			_co_to_go.Y += 1;
			return true;
		} else {
			return false;
		}
	} else {
		if (tmp.Y - 1 >= 0 && !_map->getTileAt(static_cast<size_t>(tmp.X),
			static_cast<size_t>(tmp.Y - 1))->containsSomethings()) {
			_to_go = FORWARD;
			_co_to_go.Y -= 1;
			return true;
		} else {
			return false;
		}
	}
}

}
