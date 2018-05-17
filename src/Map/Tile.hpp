/*
** EPITECH PROJECT, 2018
** Bomberman
** File description:
** Tile
*/

#pragma once

#include <algorithm>
#include <vector>
#include <memory>
#include "AObject.hpp"

namespace map {

class Tile {
	public:
		Tile(size_t x, size_t y);
		~Tile();

		size_t getX() const noexcept { return  _x; }
		size_t getY() const noexcept { return _y; }
		std::vector<std::unique_ptr<object::AObject>> &getObjects() noexcept { return _objects; }

		void addObject(std::unique_ptr<object::AObject>) noexcept;
		void removeObject(std::unique_ptr<object::AObject>) noexcept;

	private:
		size_t _x;
		size_t _y;

		std::vector<std::unique_ptr<object::AObject>> _objects;
};

}
