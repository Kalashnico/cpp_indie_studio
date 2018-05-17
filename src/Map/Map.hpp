//
// Created by Nicolas Guerin on 16/05/2018.
//

#pragma once

#include <vector>
#include <memory>
#include <mutex>
#include "Tile.hpp"

#define MAP_SIZE	15
#define INDEX(x, y)	(MAP_SIZE * x + y)

namespace map {

class Map {
	public:
		Map();
		~Map();

		//Getter
		const std::vector<std::unique_ptr<Tile>> &getMap() noexcept { return _map; };
		Tile *getTileAt(size_t x, size_t y) noexcept { return _map[INDEX(x, y)].get(); }
		size_t getTileIndex(size_t x, size_t y) const noexcept { return INDEX(x, y); }

		//Other functions
		void addObjectToTile(size_t x, size_t y, std::unique_ptr<object::AObject>) noexcept;
		void removeObjectFromTile(size_t x, size_t y, Type objectType) noexcept;

		void explodeBomb(size_t x, size_t y, size_t blastRadius) noexcept;

	private:
		//Private member Functions
		void createMap() noexcept;
		void addBoxes() noexcept;
		bool isCornerTile(size_t x, size_t y) const noexcept;

		bool placeFire(int i, size_t x, size_t y) noexcept;

		//Variable
		std::vector<std::unique_ptr<Tile>> _map;

		//Mutex
		std::mutex mapMutex;

};

}
