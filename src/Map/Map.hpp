//
// Created by Nicolas Guerin on 16/05/2018.
//

#pragma once

#include <vector>
#include <memory>
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

	private:
		//Private member Functions
		void createMap() noexcept;
		void addBoxes() noexcept;
		bool isCornerTile(size_t x, size_t y) const noexcept;

		//Variable
		std::vector<std::unique_ptr<Tile>> _map;

};

}
