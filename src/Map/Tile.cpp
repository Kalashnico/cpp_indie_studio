/*
** EPITECH PROJECT, 2018
** Bomberman
** File description:
** Tiles
*/

#include "Tile.hpp"

namespace map {

Tile::Tile(size_t x, size_t y)
	: _x(x), _y(y)
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

void Tile::addObject(std::unique_ptr<object::AObject> object) noexcept
{
	_objects.emplace_back(std::move(object));
}

void Tile::removeObject(Type objectType) noexcept
{
	for (auto &object : _objects) {
		if (object.get()->getType() == objectType)
			object.get()->destroy();
	}
}

void Tile::removedDestroyed() noexcept
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
