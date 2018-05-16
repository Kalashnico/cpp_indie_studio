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

void Tile::addObject(std::unique_ptr<IObject> object) noexcept
{
	_objects.emplace_back(std::move(object));
}

void Tile::removeObject(std::unique_ptr<IObject> object) noexcept
{
	_objects.erase(std::remove(_objects.begin(), _objects.end(), object), _objects.end());
	_objects.shrink_to_fit();
}

}
