//
// Created by Nicolas Guerin on 14/05/2018.
//

#include <vector>
#include <random>
#include "Map.hpp"
#include "Box.hpp"
#include "Wall.hpp"

namespace map {

/**
 * Constructor : Ready To Use.
 */
Map::Map()
{
	createMap();
	addBoxes();
}

Map::~Map()
{}

/**
 * Create the initial map
 * @return map without boxes
 */

void Map::createMap() noexcept
{
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			_map.emplace_back(std::make_unique<Tile>(x, y));
			if (x % 2 == 1 && y % 2 == 1) {
				std::unique_ptr<object::AObject> wall = std::make_unique<object::Wall>();
				getTileAt(x, y)->addObject(std::move(wall));
			}
		}
	}
}

bool Map::isCornerTile(size_t x, size_t y) const noexcept
{
	return (x == 0 && y == 0) || (x == 0 && y == 1) || (x == 1 && y == 0)
		|| (x == 0 && y == MAP_SIZE - 1) || (x == 0 && y == MAP_SIZE - 2) || (x == 1 && y == MAP_SIZE - 1)
		|| (x == MAP_SIZE - 1 && y == 0) || (x == MAP_SIZE - 2 && y == 0) || (x == MAP_SIZE - 1 && y == 1)
		|| (x == MAP_SIZE - 1 && y == MAP_SIZE - 1) || (x == MAP_SIZE - 1 && y == MAP_SIZE - 2) || (x == MAP_SIZE - 2 && y == MAP_SIZE - 1);
}

/**
 * Add boxes to fill the map (nearly ~90% of the map)
 * @param map without boxes
 * @return map done
 */
void Map::addBoxes() noexcept
{
	std::random_device randomDevice;						// Random device
	std::mt19937 engine(randomDevice());						// Seed
	std::uniform_int_distribution<> distribution(1, 10);				// Range

	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			if (isCornerTile(x, y))						// Player spawn check
				continue;

			if (x % 2 == 1 && y % 2 == 1)					// Wall check
				continue;

			if (distribution(engine) < 9) {					// Generate random number - 8/10 chance to spawn box
				std::unique_ptr<object::AObject> box = std::make_unique<object::Box>(object::Loot{});
				getTileAt(x, y)->addObject(std::move(box));
			}
		}
	}
}

}
