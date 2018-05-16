//
// Created by Nicolas Guerin on 14/05/2018.
//

#include <vector>
#include <array>
#include <cstdlib>
#include "Map.hpp"

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
std::array<std::array<int, MAP_SIZE>, MAP_SIZE> Map::createMap() const noexcept
{
	std::array<std::array<int, MAP_SIZE>, MAP_SIZE> map{};

	for (auto count = 0; count < MAP_SIZE; ++count) {
		if (count == 0 || count == MAP_SIZE - 1) {
			map.at(count).fill(0);
			continue;
		}
		map.at(count).fill(1);
		for (auto itr = 0; itr < MAP_SIZE; ++itr) {
			if (itr == 0 || itr == MAP_SIZE - 1) {
				map.at(count).at(itr) = 0;
				continue;
			}
			if (count % 2 == 0) {
				if (itr % 2 == 0)
					map.at(count).at(itr) = 0;
			}
		}
	}
	return map;
}

/**
 * Add boxes to fill the map (nearly ~90% of the map)
 * @param map without boxes
 * @return map done
 */
std::array<std::array<int, MAP_SIZE>, MAP_SIZE> Map::addBoxes(std::array<std::array<int, MAP_SIZE>, MAP_SIZE> map) const noexcept
{
	for (auto countBoxes = 0; countBoxes <= 75;) {
		auto posx = std::rand() % (MAP_SIZE - 2) + 1;
		auto posy = std::rand() % (MAP_SIZE - 2) + 1;

		if (map.at(posx).at(posy) == 1) {
			map.at(posx).at(posy) = 2;
			++countBoxes;
		}
	}

	map.at(1).at(1) = 1;
	map.at(13).at(13) = 1;
	map.at(1).at(13) = 1;
	map.at(13).at(1) = 1;
	return map;
}
