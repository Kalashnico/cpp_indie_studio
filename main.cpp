#include <iostream>
#include "src/Map/Map.hpp"

void mapTest()
{
	map::Map *bomberMap = new map::Map();

	std::cout << "Map size: " << bomberMap->getMap().size() << std::endl;

	std::cout << "Listing tiles: " << std::endl;
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			std::cout << "x: " << bomberMap->getTileAt(x, y)->getX() << " y: " << bomberMap->getTileAt(x, y)->getY() << " Objects: " << bomberMap->getTileAt(x, y)->getObjects().size() << std::endl;
			if (bomberMap->getTileAt(x, y)->getObjects().size() > 0) {
				std::cout << "Tile contains: " << std::endl;
				for (auto &object : bomberMap->getTileAt(x, y)->getObjects())
					std::cout << object->getType() << std::endl;
			}
		}
	}

	delete bomberMap;
}

int main()
{
	mapTest();
	return (0);
}