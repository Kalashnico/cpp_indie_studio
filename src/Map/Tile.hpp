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

		void setSetup(bool value) noexcept { _setup = value; }

		std::vector<std::unique_ptr<object::AObject>> &getObjects() noexcept { return _objects; }
		object::AObject *getObject(Type objectType) noexcept;

		void updateTile() noexcept;
		void addObject(std::unique_ptr<object::AObject>) noexcept;
		void removeObject(Type objectType) noexcept;
		std::unique_ptr<object::AObject> removePlayer(Type objectType) noexcept;
		bool containsObject(Type objectType) noexcept;
		bool containsSomethings() noexcept;

	private:
		size_t _x;
		size_t _y;
		bool _setup;

		std::vector<std::unique_ptr<object::AObject>> _objectsToBeAdded;
		std::vector<std::unique_ptr<object::AObject>> _objects;

		void addToBeAdded() noexcept;
		void removeDestroyed() noexcept;
		void updatePlayerPositions() noexcept;
};

}
