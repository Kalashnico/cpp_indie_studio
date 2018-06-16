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
		auto pos = _player.getPosition();

		if (_player.checkDeath()) {
			_player.die();
			return;
		}

		if (_destinationDirection == NONE) {
			this->findClosestPlayer();
			_destinationCoordinates = _player.getPositionFloat();
			setWayToPlayer();

			move();

			if (!checkIfSafeDestination(_destinationDirection)) {
				setSafeDestination(pos.X, pos.Y);
				_destinationCoordinates = _player.getPositionFloat();
				move();
			}

			if (isSafe(pos.X, pos.Y) && (_destinationDirection == NONE || (isBoxNearby(pos.X, pos.Y, _player.getBlastRadius()) && !_player.canWalkThroughBoxes()))) {
				_destinationDirection = NONE;
				_player.placeBomb();
			}
		}

		if (_destinationDirection != NONE)
			this->moveCase(_destinationDirection);
	}

	void AI::updatePosition(size_t oldx, size_t oldy) noexcept
	{
		auto position = _player.getPosition();

		if (position.X != oldx || position.Y != oldy) {
			_map->movePlayer(getType(), oldx, oldy, position.X, position.Y);
			if (_map->getTileAt(position.X, position.Y)->containsObject(LOOT))
				_player.pickupLoot(position);
		}
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

		if (_map->getTileAt(x, y)->containsObject(WALL)
			|| (_map->getTileAt(x, y)->containsObject(BOX) && !_player.canWalkThroughBoxes())
			|| (_map->getTileAt(x, y)->containsObject(PLAYER1) && getType() != PLAYER1)
			|| (_map->getTileAt(x, y)->containsObject(PLAYER2) && getType() != PLAYER2)
			|| (_map->getTileAt(x, y)->containsObject(PLAYER3) && getType() != PLAYER3)
			|| (_map->getTileAt(x, y)->containsObject(PLAYER4) && getType() != PLAYER4)) {
			return false;
		}

		if (_map->getTileAt(x, y)->containsObject(BOMB)
			|| _map->getTileAt(x, y)->containsObject(FIRE)) {
			return false;
		}

		return !checkBombDanger(x, y);
	}

	bool AI::checkBombDanger(size_t x, size_t y, rotationDirection_e dir)
	{
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

		for (size_t tmpY = 0; tmpY < MAP_SIZE - 1; ++tmpY) {
			if (checkBombImpactAt(x, tmpY, x, y))
				return true;
		}

		for (size_t tmpX = 0; tmpX < MAP_SIZE - 1; ++tmpX) {
			if (checkBombImpactAt(tmpX, y, x, y))
				return true;
		}

		return false;
	}

	void AI::setSafeDestination(size_t x, size_t y)
	{
		rotationDirection_e dir = LEFT;
		rotationDirection_e firstDir = LEFT;
		rotationDirection_e prevDir = NONE;

		auto tmpX = x;
		auto tmpY = y;

		bool hasMoved = false;

		if (!checkBombDanger(x, y)) {
			_destinationDirection = NONE;
			return;
		}

		while (true) {
			if (checkMoveToTile(tmpX, tmpY, dir) && dir != prevDir) {
				if (!checkBombDanger(tmpX, tmpY, dir)) {
					_destinationDirection = firstDir;
					return;
				} else {
					switch (dir) {
					case FORWARD:
						prevDir = BACKWARD;
						tmpY -= 1;
						break;
					case BACKWARD:
						prevDir = FORWARD;
						tmpY += 1;
						break;
					case LEFT:
						prevDir = RIGHT;
						tmpX -= 1;
						break;
					case RIGHT:
						prevDir = LEFT;
						tmpX += 1;
						break;
					}

					dir = LEFT;
					hasMoved = true;
				}
			} else {
				if (hasMoved) {
					dir = (rotationDirection_e)((size_t)dir + 1);
					if (dir == NONE) {
						tmpX = x;
						tmpY = y;
						hasMoved = false;
						prevDir = NONE;
						dir = firstDir = (rotationDirection_e)((size_t)firstDir + 1);
						if (firstDir == NONE) {
							_destinationDirection = firstDir;
							return;
						}
					}
				} else {
					prevDir = NONE;
					dir = firstDir = (rotationDirection_e)((size_t)firstDir + 1);
					if (firstDir == NONE) {
						_destinationDirection = firstDir;
						return;
					}
				}
			}
		}
	}

	bool AI::isSafe(size_t x, size_t y)
	{
		if (checkBombDanger(x, y)
			|| (x < MAP_SIZE - 1 && checkBombDanger(x + 1, y))
			|| (x > 0 && checkBombDanger(x - 1, y))
			|| (y < MAP_SIZE - 1 && checkBombDanger(x, y)
			|| (y > 0 && checkBombDanger(x, y))))
			return false;

		return !((x < MAP_SIZE - 1 && _map->getTileAt(x + 1, y)->containsObject(FIRE))
		|| ((x > 0 && _map->getTileAt(x - 1, y)->containsObject(FIRE)))
		|| (y < MAP_SIZE - 1 && _map->getTileAt(x, y + 1)->containsObject(FIRE))
		|| (y > 0 && _map->getTileAt(x, y - 1)->containsObject(FIRE)));
	}

	void AI::moveCase(rotationDirection_e dir, float spd)
	{
		const irr::core::vector2df tmp = _player.getPositionFloat();

		auto sX = static_cast<size_t>(_destinationCoordinates.X);
		auto sY = static_cast<size_t>(_destinationCoordinates.Y);


		if ((_map->getTileAt(sX, sY)->containsObject(BOX) && !_player.canWalkThroughBoxes())
			|| _map->getTileAt(sX, sY)->containsObject(BOMB)
			|| _map->getTileAt(sX, sY)->containsObject(FIRE)
			|| (_map->getTileAt(sX, sY)->containsObject(PLAYER1) && getType() != PLAYER1)
			|| (_map->getTileAt(sX, sY)->containsObject(PLAYER2) && getType() != PLAYER2)
			|| (_map->getTileAt(sX, sY)->containsObject(PLAYER3) && getType() != PLAYER3)
			|| (_map->getTileAt(sX, sY)->containsObject(PLAYER4) && getType() != PLAYER4)) {

			switch(_destinationDirection) {
				case FORWARD:
					_destinationDirection = BACKWARD;
					break;
				case BACKWARD:
					_destinationDirection = FORWARD;
					break;
				case LEFT:
					_destinationDirection = RIGHT;
					break;
				case RIGHT:
					_destinationDirection = LEFT;
					break;
			}
			move();
		}

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
		irr::core::vector2di tmp = _player.getPosition();
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

	bool AI::checkMoveToTile(size_t x, size_t y, rotationDirection_e dir)
	{
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

		return !(_map->getTileAt(x, y)->containsObject(WALL)
		|| (_map->getTileAt(x, y)->containsObject(BOX) && !_player.canWalkThroughBoxes())
		|| _map->getTileAt(x, y)->containsObject(BOMB)
		|| _map->getTileAt(x, y)->containsObject(FIRE)
		|| (_map->getTileAt(x, y)->containsObject(PLAYER1) && getType() != PLAYER1)
		|| (_map->getTileAt(x, y)->containsObject(PLAYER2) && getType() != PLAYER2)
		|| (_map->getTileAt(x, y)->containsObject(PLAYER3) && getType() != PLAYER3)
		|| (_map->getTileAt(x, y)->containsObject(PLAYER4) && getType() != PLAYER4));
	}

	bool AI::moveToXPlayer(irr::core::vector2di tmp, bool invert)
	{
		auto x = static_cast<size_t>(tmp.X);
		auto y = static_cast<size_t>(tmp.Y);

		if ((x < static_cast<size_t>(_closestPlayer.X) && !invert) || invert) {
			if (x + 1 <= MAP_SIZE - 1 && checkMoveToTile(x + 1, y)) {
				_destinationDirection = RIGHT;
				return true;
			} else
				return false;
		} else {
			if (x > 0 && checkMoveToTile(x - 1, y)) {
				_destinationDirection = LEFT;
				return true;
			} else
				return false;
		}
	}

	bool AI::moveToYPlayer(irr::core::vector2di tmp, bool invert)
	{
		auto x = static_cast<size_t>(tmp.X);
		auto y = static_cast<size_t>(tmp.Y);

		if ((y < static_cast<size_t>(_closestPlayer.Y) && !invert) || invert) {
			if (y + 1 <= MAP_SIZE - 1 && checkMoveToTile(x, y + 1)) {
				_destinationDirection = BACKWARD;
				return true;
			} else
				return false;
		} else {
			if (y > 0 && checkMoveToTile(x, y - 1)) {
				_destinationDirection = FORWARD;
				return true;
			} else
				return false;
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
		if (x > MAP_SIZE - 1 || x < 0 || y > MAP_SIZE - 1 || y < 0)
			return false;

		auto *tmp = dynamic_cast<object::Bomb*>(_map->getTileAt(x, y)->getObject(BOMB));

		if (tmp != nullptr) {
			if (abs(static_cast<int>(yPlayer - y)) <= tmp->getBlast() && abs(static_cast<int>(xPlayer - x)) <= tmp->getBlast()) {
				if (y > yPlayer) {
					for (size_t i = yPlayer + 1; i < y; i++) {
						if (_map->getTileAt(xPlayer, i)->containsObject(BOX) || _map->getTileAt(xPlayer, i)->containsObject(WALL))
							return false;
					}
				} else if (y < yPlayer) {
					for (size_t i = y + 1; i < yPlayer; i++) {
						if (_map->getTileAt(xPlayer, i)->containsObject(BOX) || _map->getTileAt(xPlayer, i)->containsObject(WALL))
							return false;
					}
				}

				if (x > xPlayer) {
					for (size_t i = xPlayer + 1; i < x; i++) {
						if (_map->getTileAt(i, yPlayer)->containsObject(BOX) || _map->getTileAt(i, yPlayer)->containsObject(WALL))
							return false;
					}
				} else if (x < xPlayer) {
					for (size_t i = x + 1; i < xPlayer; i++) {
						if (_map->getTileAt(i, yPlayer)->containsObject(BOX) || _map->getTileAt(i, yPlayer)->containsObject(WALL))
							return false;
					}
				}
				return true;
			}
		}
		return false;
	}

	bool AI::isBoxNearby(int x, int y, int bombSize)
	{
		for (int i = 0 ; i < bombSize ; i++) {
			if (x - i > 0 &&
				_map->getTileAt(x - (i + 1), y)->containsObject(BOX))
				return true;
			else if (x + i < MAP_SIZE - 1 &&
				_map->getTileAt(x + (i + 1), y)->containsObject(BOX))
				return true;
			else if (y - i > 0 &&
				_map->getTileAt(x, y - (i + 1))->containsObject(BOX))
				return true;
			else if (y + i < MAP_SIZE - 1 &&
				_map->getTileAt(x, y + (i + 1))->containsObject(BOX))
				return true;
		}
		return false;
	}
}
