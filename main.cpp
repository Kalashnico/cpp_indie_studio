#include <iostream>
#include <memory>
#include <atomic>
#include "Map.hpp"
#include "Bomb.hpp"

std::atomic<bool> _bombPlaced = false;

void createBomb(map::Map *bomberMap)
{
	bomberMap->addObjectToTile(0, 0, std::move(std::unique_ptr<object::AObject>(new object::Bomb(0, 0, 2, bomberMap))));
	_bombPlaced = true;
	bomberMap->getTileAt(0, 0)->getObject(BOMB)->bombFuse();
}

void bombTest(map::Map *bomberMap)
{
	std::cout << "Starting bomb test" << std::endl;

	std::thread bomb(&createBomb, bomberMap);

	std::cout << "Waiting for thread to place bomb" << std::endl;

	while (!_bombPlaced);

	std::cout << "Bomb placed" << std::endl << "Waiting for bomb to explode" << std::endl;

	while (bomberMap->getTileAt(0, 0)->containsObject(BOMB));

	std::cout << "Bomb has exploded" << std::endl << "Checking for fire on affected tiles... ";

	if (bomberMap->getTileAt(0, 0)->containsObject(FIRE)
		&& bomberMap->getTileAt(0, 1)->containsObject(FIRE)
		&& bomberMap->getTileAt(0, 2)->containsObject(FIRE)
		&& bomberMap->getTileAt(1, 0)->containsObject(FIRE)
		&& bomberMap->getTileAt(2, 0)->containsObject(FIRE))
		std::cout << "Test passed" << std::endl;
	else
		std::cout << "Test failed" << std::endl;

	std::cout << "End of bomb test" << std::endl;
	bomb.join();
}

void mapTest()
{
	map::Map *bomberMap = new map::Map();

	std::cout << "Map size: " << bomberMap->getMap().size() << " Listing tiles: " << std::endl;
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			std::cout << "x: " << bomberMap->getTileAt(x, y)->getX() << " y: " << bomberMap->getTileAt(x, y)->getY() << " Objects: " << bomberMap->getTileAt(x, y)->getObjects().size();
			if (bomberMap->getTileAt(x, y)->getObjects().size() > 0) {
				std::cout << " Tile contains: ";
				for (auto &object : bomberMap->getTileAt(x, y)->getObjects())
					std::cout << object->getType() << " ";
			}
			std::cout << std::endl;
		}
	}

	bombTest(bomberMap);
	delete bomberMap;
}

int main()
{
	mapTest();
	return (0);
}