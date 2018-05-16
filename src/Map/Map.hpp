//
// Created by Nicolas Guerin on 16/05/2018.
//

#pragma once

#include <vector>
#include "Tile.hpp"

#define MAP_SIZE	15
#define BOX_COUNT	75
#define INDEX(x, y)	(MAP_SIZE * x + y)

namespace map {

class Map {
	public:
		Map();
		~Map();

		//Getter
		std::vector<Tile> &getMap() noexcept { return _map; };
		Tile &getTileAt(size_t x, size_t y) noexcept { return _map[INDEX(x, y)]; }
		size_t getTileIndex(size_t x, size_t y) const noexcept { return INDEX(x, y); }

	private:
		//Private member Functions
		std::vector<Tile> createMap() const noexcept;
		std::vector<Tile> addBoxes(std::vector<Tile> map) const noexcept;

		//Variable
		std::vector<Tile> _map;

};

}
