/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Created by tclemenceau,
*/

#include <vector>
#include <iostream>
#include "Bomb.hpp"
#include "AI.hpp"

namespace object {

	AI::AI(::map::Map *map, Type type, Gfx *gfx, playerSprite_e playerType,
		float x, float y, float z, bool useController,
		unsigned long playerNb
	) : AObject(type),
		_player(map, type, gfx, playerType, x, y, z, useController,
			playerNb), _map(map), _destinationDirection(NONE),
		_closestPlayer(-1, -1)
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
		if (_player.checkDeath()) {
			_player.die();
			return;
		}

		if (_destinationDirection == NONE) {
			this->findClosestPlayer();
			_destinationCoordinates = _player.getPositionFloat();
			setWayToPlayer();

			std::cout << "Destination before " << _destinationDirection << std::endl;

			move();

			if (!checkIfSafeDestination(_destinationDirection)) {
				setSafeDestination();
				_destinationCoordinates = _player.getPositionFloat();
				move();
			}

			std::cout << "Destination after " << _destinationDirection << std::endl;

			std::cout << "Destination coords x: " << _destinationCoordinates.X << " y: " << _destinationCoordinates.Y << std::endl;

			if (_destinationDirection == NONE)
				_player.placeBomb();
		}

		if (_destinationDirection != NONE)
			this->moveCase(_destinationDirection);
	}

	void AI::updatePosition(size_t oldx, size_t oldy) noexcept
	{
		auto position = _player.getPosition();

		if (position.X != oldx || position.Y != oldy)
			_map->movePlayer(getType(), oldx, oldy, position.X,
				position.Y);
	}

	bool AI::checkIfSafeDestination(rotationDirection_e dir)
	{
		auto pos = _player.getPositionFloat();
		auto x = static_cast<size_t>(pos.X);
		auto y = static_cast<size_t>(pos.Y);

		switch (dir) {
		case FORWARD:
			if (y <= 0)
				return false;
			y -= 1;
			break;
		case BACKWARD:
			if (y >= MAP_SIZE - 1)
				return false;
			y += 1;
			break;
		case LEFT:
			if (x <= 0)
				return false;
			x -= 1;
			break;
		case RIGHT:
			if (x >= MAP_SIZE - 1)
				return false;
			x += 1;
			break;
		case NONE:
			break;
		}

		std::cout << "x: " << x << " y: " << y << std::endl;

		if (_map->getTileAt(x, y)->containsObject(WALL)
			|| _map->getTileAt(x, y)->containsObject(BOX)) {
			std::cout << "Stuck" << std::endl;
			return false;
		}

		if (_map->getTileAt(x, y)->containsObject(BOMB)
			|| _map->getTileAt(x, y)->containsObject(FIRE)) {
			std::cout << "Danger" << std::endl;
			return false;
		}

		if ((y != 0 && !(_map->getTileAt(x, y - 1)->containsObject(WALL) || _map->getTileAt(x, y - 1)->containsObject(BOX)))
			|| (y != MAP_SIZE - 1 && !(_map->getTileAt(x, y + 1)->containsObject(WALL) || _map->getTileAt(x, y + 1)->containsObject(BOX)))) {
			for (size_t tmpY = 0; tmpY < MAP_SIZE - 1; ++tmpY) {
				std::cout << "Checking y: " << tmpY << " for bomb impacts" << std::endl;
				if (checkBombImpactAt(x, tmpY, x, y)) {
					std::cout << "DangerImpactY" << std::endl;
					return false;
				}
			}
		}

		if ((x != 0 && !(_map->getTileAt(x - 1, y)->containsObject(WALL) || _map->getTileAt(x - 1, y)->containsObject(BOX)))
			|| (x != MAP_SIZE - 1 && !(_map->getTileAt(x + 1, y)->containsObject(WALL) || _map->getTileAt(x + 1, y)->containsObject(BOX)))) {
			for (size_t tmpX = 0; tmpX < MAP_SIZE - 1; ++tmpX) {
				std::cout << "Checking x: " << tmpX << " for bomb impacts" << std::endl;
				if (checkBombImpactAt(tmpX, y, x, y)) {
					std::cout << "DangerImpactX" << std::endl;
					return false;
				}
			}
		}
		return true;
	}

	void AI::setSafeDestination()
	{
		std::mt19937 engine(_random());
		std::uniform_int_distribution<> distribution(0, 1);
		std::array<int, 2> tryRemainingY = {1, 1};
		std::array<int, 2> tryRemainingX = {1, 1};
		bool done = false;

		while (!done) {
			if (distribution(engine) == 0 && (tryRemainingY[0] != 0 || tryRemainingY[1] != 0)) {
				if (tryRemainingY[0] != 0 && (distribution(engine) == 0 || (tryRemainingY[1] == 0))) {
					done = checkIfSafeDestination(FORWARD);
					_destinationDirection = (done) ? FORWARD : _destinationDirection;
					tryRemainingY[0] = 0;
				} else if (tryRemainingY[1] != 0) {
					done = checkIfSafeDestination(BACKWARD);
					_destinationDirection = (done) ? BACKWARD : _destinationDirection;
					tryRemainingY[1] = 0;
				}
			} else if (!(tryRemainingX[0] == 0 && tryRemainingX[1] == 0)) {
				if (tryRemainingX[0] != 0 && (distribution(engine) == 0 || (tryRemainingX[1] == 0))) {
					done = checkIfSafeDestination(LEFT);
					_destinationDirection = (done) ? LEFT : _destinationDirection;
					tryRemainingX[0] = 0;
				} else if (tryRemainingX[1] != 0) {
					done = checkIfSafeDestination(RIGHT);
					_destinationDirection = (done) ? RIGHT : _destinationDirection;
					tryRemainingX[1] = 0;
				}
			}
			if (!done && (tryRemainingX[0] == 0 && tryRemainingX[1] == 0 && tryRemainingY[0] == 0 && tryRemainingY[1] == 0)) {
				done = true;
				_destinationDirection = NONE;
			}
		}
	}

	void AI::moveCase(rotationDirection_e dir, float spd)
	{
		const vector2df tmp = _player.getPositionFloat();

		switch (dir) {
		case BACKWARD:
			if (int(_destinationCoordinates.Y * 10) !=
				int(tmp.Y * 10))
				_player.move(dir, spd);
			else
				_destinationDirection = NONE;
			break;
		case FORWARD:
			if (int(_destinationCoordinates.Y * 10) !=
				int(tmp.Y * 10))
				_player.move(dir, spd);
			else
				_destinationDirection = NONE;
			break;
		case LEFT:
			if (int(_destinationCoordinates.X * 10) !=
				int(tmp.X * 10))
				_player.move(dir, spd);
			else
				_destinationDirection = NONE;
			break;
		case RIGHT:
			if (int(_destinationCoordinates.X * 10) !=
				int(tmp.X * 10))
				_player.move(dir, spd);
			else
				_destinationDirection = NONE;
			break;
		case NONE:
			break;
		}
	}


	void AI::findClosestPlayer()
	{
		auto myMap = &(_map->getMap());
		object::Player *tmp;
		int distance;
		int distance_tmp;

		_closestPlayer.X = -1;
		_closestPlayer.Y = -1;
		for (auto &tile : *myMap) {
			for (auto &object : tile->getObjects())
				if ((object->getType() == PLAYER1 ||
					object->getType() == PLAYER2 ||
					object->getType() == PLAYER3 ||
					object->getType() == PLAYER4) &&
					object->getType() != getType()) {
					if (_closestPlayer.X == -1 ||
						_closestPlayer.Y == -1) {
						_closestPlayer = object->getPosition();
						continue;
					}
					distance = abs(_closestPlayer.X -
						_player.getPosition().X) +
						abs(_closestPlayer.Y -
							_player.getPosition().Y);
					distance_tmp =
						abs(object->getPosition().X -
							_player.getPosition().X) +
							abs(object->getPosition().Y -
								_player.getPosition().Y);
					_closestPlayer =
						(distance_tmp <= distance) ?
							object->getPosition() :
							_closestPlayer;
				}
		}
	}

	void AI::setWayToPlayer()
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
			if ((distribution(engine) == 0 || tryRemainingY == 0) &&
				tryRemainingX != 0) {
				done = moveToXPlayer(tmp, invertX);
				tryRemainingX -= 1;
				invertX = true;
			} else if (tryRemainingY != 0) {
				done = moveToYPlayer(tmp, invertY);
				tryRemainingY -= 1;
				invertY = true;
			}
		}
	}

	bool AI::moveToXPlayer(vector2di tmp, bool invert)
	{
		if ((tmp.X < _closestPlayer.X && !invert) || invert) {
			if (tmp.X + 1 <= MAP_SIZE - 1 &&
				!_map->getTileAt(static_cast<size_t>(tmp.X + 1),
					static_cast<size_t>(tmp.Y))->containsSomethings()) {
				_destinationDirection = RIGHT;
				return true;
			} else {
				return false;
			}
		} else {
			if (tmp.X - 1 >= 0 &&
				!_map->getTileAt(static_cast<size_t>(tmp.X - 1),
					static_cast<size_t>(tmp.Y))->containsSomethings()) {
				_destinationDirection = LEFT;
				return true;
			} else {
				return false;
			}
		}
	}

	bool AI::moveToYPlayer(vector2di tmp, bool invert)
	{
		if ((tmp.Y < _closestPlayer.Y && !invert) || invert) {
			if (tmp.Y + 1 <= MAP_SIZE - 1 &&
				!_map->getTileAt(static_cast<size_t>(tmp.X),
					static_cast<size_t>(tmp.Y +
						1))->containsSomethings()) {
				_destinationDirection = BACKWARD;
				return true;
			} else {
				return false;
			}
		} else {
			if (tmp.Y - 1 >= 0 &&
				!_map->getTileAt(static_cast<size_t>(tmp.X),
					static_cast<size_t>(tmp.Y -
						1))->containsSomethings()) {
				_destinationDirection = FORWARD;
				return true;
			} else {
				return false;
			}
		}
	}

	void AI::move()
	{
		switch (_destinationDirection) {
		case BACKWARD:
			_destinationCoordinates.Y += 1;
			break;
		case FORWARD:
			_destinationCoordinates.Y -= 1;
			break;
		case LEFT:
			_destinationCoordinates.X -= 1;
			break;
		case RIGHT:
			_destinationCoordinates.X += 1;
			break;
		case NONE:
			break;
		}
	}

	bool AI::checkBombImpactAt(size_t x, size_t y, size_t xPlayer, size_t yPlayer) const
	{
		auto *tmp = dynamic_cast<object::Bomb*>(_map->getTileAt(x, y)->getObject(BOMB));

		if (tmp != nullptr) {
			if (abs(static_cast<int>(yPlayer - y)) <= tmp->getBlast())
				return true;
			if (abs(static_cast<int>(xPlayer - x)) <= tmp->getBlast())
				return true;
		}
		return false;
	}

}
