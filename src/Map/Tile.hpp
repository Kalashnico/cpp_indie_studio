/*
** EPITECH PROJECT, 2018
** Bomberman
** File description:
** Tile
*/

#pragma once

#include <algorithm>
#include <vector>
#include "IObject.hpp"

namespace map {

class Tile {
	public:
		Tile(size_t x, size_t y);
		~Tile();

		size_t getX() const noexcept { return  _x; }
		size_t getY() const noexcept { return _y; }
		const std::vector<IObject> &getObjects() const noexcept { return _objects; }

		void addObject(const IObject &object) noexcept { _objects.emplace_back(object); }
		void removeObject(const IObject &object) noexcept { _objects.erase(std::remove(_objects.begin(), _objects.end(), object), _objects.end()); }

	private:
		size_t _x;
		size_t _y;

		std::vector<IObject> _objects;
};

}
