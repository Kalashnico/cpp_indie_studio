//
// Created by Nicolas Guerin on 14/05/2018.
//

#include <vector>
#include "Map.hpp"

namespace map {

/**
 * Constructor : Ready To Use.
 */
Map::Map()
{
	auto map = createMap();
	map = addBoxes(map);
	_map = map;
}

Map::~Map()
{

}

/**
 * Create the initial map
 * @return map without boxes
 */

std::vector<Tile> Map::createMap() const noexcept
{
	std::vector<Tile> map{};

	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			map.emplace_back(Tile(x, y));
			//if (x % 2 == 1 && y % 2 == 1)
				//map.back().addObject(); // TODO: Add wall?
		}
	}

	return map;
}

/**
 * Add boxes to fill the map (nearly ~90% of the map)
 * @param map without boxes
 * @return map done
 */
std::vector<Tile> Map::addBoxes(std::vector<Tile> map) const noexcept
{
	// TODO
	return map;
}

}
