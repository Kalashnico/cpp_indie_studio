//
// Created by Nicolas Guerin on 14/05/2018.
//

#include <random>
#include "Map.hpp"
#include "Box.hpp"
#include "Wall.hpp"
#include "Fire.hpp"

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

void Map::updateTileObjects() noexcept
{
	for (auto &tile : _map) {
		for (auto &object : tile.get()->getObjects()) {
			object.get()->update();
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
	std::random_device randomDevice;			// Random device
	std::mt19937 engine(randomDevice());			// Seed
	std::uniform_int_distribution<> distribution(1, 10);	// Range

	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			if (isCornerTile(x, y))			// Player spawn check
				continue;

			if (x % 2 == 1 && y % 2 == 1)		// Wall check
				continue;

			if (distribution(engine) < 9) {		// Generate random number - 8/10 chance to spawn box
				std::unique_ptr<object::AObject> box = std::make_unique<object::Box>(object::Loot{});
				getTileAt(x, y)->addObject(std::move(box));
			}
		}
	}
}

void Map::addObjectToTile(size_t x, size_t y, std::unique_ptr<object::AObject> object) noexcept
{
	getTileAt(x, y)->addObject(std::move(object));
}

void Map::removeObjectFromTile(size_t x, size_t y, Type objectType) noexcept
{
	getTileAt(x, y)->removeObject(objectType);
}

bool Map::placeFire(int i, size_t x, size_t y) noexcept
{
	if (i < 0 || getTileAt(x, y)->containsObject(WALL))
		return false;

	if (getTileAt(x, y)->containsObject(FIRE))
		removeObjectFromTile(x, y, FIRE);

	if (getTileAt(x, y)->containsObject(BOMB)) {
		auto bomb = getTileAt(x, y)->getObject(BOMB);
		if (bomb != nullptr)
			bomb->detonate();
	}

	if (getTileAt(x, y)->containsObject(BOX)) {
		removeObjectFromTile(x, y, BOX);
		addObjectToTile(x, y, std::move(std::unique_ptr<object::AObject>(new object::Fire(x, y, this))));
		return false;
	}

	addObjectToTile(x, y, std::move(std::unique_ptr<object::AObject>(new object::Fire(x, y, this))));
	return true;
}

void Map::explodeBomb(size_t x, size_t y, size_t blastRadius) noexcept
{
	removeObjectFromTile(x, y, BOMB);
	addObjectToTile(x, y, std::move(std::unique_ptr<object::AObject>(new object::Fire(x, y, this))));

	for (int i = x - 1; i >= x - blastRadius; i--)
		if (!placeFire(i, i, y))
			break;

	for (int i = x + 1; i <= x + blastRadius; i++)
		if (!placeFire(i, i, y))
			break;

	for (int i = y - 1; i >= y - blastRadius; i--)
		if (!placeFire(i, x, i))
			break;

	for (int i = y + 1; i <= y + blastRadius; i++)
		if (!placeFire(i, x, i))
			break;
}

}
