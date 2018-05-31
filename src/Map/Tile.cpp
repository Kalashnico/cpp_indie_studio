/*
** EPITECH PROJECT, 2018
** Bomberman
** File description:
** Tiles
*/

#include <iostream>
#include "Tile.hpp"

namespace map {

Tile::Tile(size_t x, size_t y)
	: _x(x), _y(y), _setup(false)
{}

Tile::~Tile()
{}

object::AObject *Tile::getObject(Type objectType) noexcept
{
	for (auto &object : _objects) {
		if (object.get()->getType() == objectType && !object.get()->toBeDestroyed())
			return object.get();
	}
	return nullptr;
}

void Tile::updateTile() noexcept
{
	removeDestroyed();
	updatePlayerPositions();
	addToBeAdded();
}

void Tile::addObject(std::unique_ptr<object::AObject> object) noexcept
{
	if (!_setup)
		_objects.emplace_back(std::move(object));
	else
		_objectsToBeAdded.emplace_back(std::move(object));
}

void Tile::removeObject(Type objectType) noexcept
{
	for (auto &object : _objects) {
		if (object.get()->getType() == objectType)
			object.get()->destroy();
	}
}

void Tile::updatePlayerPositions() noexcept
{
	if (containsObject(PLAYER1))
		getObject(PLAYER1)->updatePosition(_x, _y);

	if (containsObject(PLAYER2))
		getObject(PLAYER2)->updatePosition(_x, _y);

	if (containsObject(PLAYER3))
		getObject(PLAYER3)->updatePosition(_x, _y);

	if (containsObject(PLAYER4))
		getObject(PLAYER4)->updatePosition(_x, _y);
}

std::unique_ptr<object::AObject> Tile::removePlayer(Type objectType) noexcept
{
	if (objectType != PLAYER1 && objectType != PLAYER2 && objectType != PLAYER3 && objectType != PLAYER4)
		return nullptr;

	if (!containsObject(objectType))
		return nullptr;

	auto playerIt = std::find_if(_objects.begin(), _objects.end(),
					[objectType](std::unique_ptr<object::AObject> &object)
					{
						return object.get()->getType() == objectType;
					});

	if (playerIt != _objects.end()) {
		auto player = std::move(*playerIt);
		_objects.erase(playerIt);
		_objects.shrink_to_fit();
		return std::move(player);
	}

	return nullptr;
}

void Tile::addToBeAdded() noexcept
{
	for (auto &object : _objectsToBeAdded)
		_objects.emplace_back(std::move(object));

	_objectsToBeAdded.clear();
	_objectsToBeAdded.shrink_to_fit();
}

void Tile::removeDestroyed() noexcept
{
	auto toRemove = std::remove_if(_objects.begin(), _objects.end(),
					[](std::unique_ptr<object::AObject> &object)
					{
						return object.get()->toBeDestroyed();
					});

	_objects.erase(toRemove, _objects.end());
	_objects.shrink_to_fit();
}

bool Tile::containsObject(Type objectType) noexcept
{
	for (auto &object : _objects) {
		if (object.get()->getType() == objectType && !object.get()->toBeDestroyed())
			return true;
	}
	return false;
}

}
