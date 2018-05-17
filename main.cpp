#include <iostream>
#include <memory>
#include "Map.hpp"
#include "Bomb.hpp"

void fireTestLogic(map::Map *bomberMap)
{
	while (bomberMap->getTileAt(0, 0)->containsObject(FIRE))		// Test conditon
		bomberMap->updateTileObjects();
}

bool fireTest(map::Map *bomberMap)
{
	std::cout << std::endl << "Starting fire test" << std::endl << "Checking existing fire... ";

	if (bomberMap->getTileAt(0, 0)->containsObject(FIRE))
		std::cout << "found" << std::endl;
	else {
		std::cout << "not found" << std::endl << "Test failed" << std::endl;
		return false;
	}

	std::cout << "Starting fire test logic" << std::endl;

	fireTestLogic(bomberMap);

	std::cout << "Fire dissipated" << std::endl << "Test passed" << std::endl;

	return true;
}

void bombTestlogic(map::Map *bomberMap)
{
	while (bomberMap->getTileAt(0, 0)->containsObject(BOMB))		// Test conditon
		bomberMap->updateTileObjects();
}

bool bombTest(map::Map *bomberMap)
{
	std::cout << std::endl << "Starting bomb test" << std::endl;

	bomberMap->addObjectToTile(0, 0, std::move(std::unique_ptr<object::AObject>(new object::Bomb(0, 0, 2, bomberMap))));

	std::cout << "Bomb placed" << std::endl << "Starting bomb test logic loop" << std::endl;

	bombTestlogic(bomberMap);

	std::cout << "Bomb has exploded" << std::endl << "Ending bomb test logic loop" << std::endl << "Checking for fire on affected tiles... ";

	if (bomberMap->getTileAt(0, 0)->containsObject(FIRE)
		&& bomberMap->getTileAt(0, 1)->containsObject(FIRE)
		&& bomberMap->getTileAt(0, 2)->containsObject(FIRE)
		&& bomberMap->getTileAt(1, 0)->containsObject(FIRE)
		&& bomberMap->getTileAt(2, 0)->containsObject(FIRE))
		std::cout << "Test passed" << std::endl;
	else {
		std::cout << "Test failed" << std::endl;
		return false;
	}

	return true;
}

bool mapTest(map::Map *bomberMap, bool verbose)
{
	std::cout << std::endl << "Starting map test - verbose: ";
	(verbose) ? std::cout << "true" : std::cout << "false";
	std::cout << std::endl;

	if (verbose) {
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
	}

	std::cout << "Test passed" << std::endl;
	return true;
}

int main()
{
	size_t totalTests = 3;
	size_t passedTests = 0;
	map::Map *bomberMap = new map::Map();

	std::cout << "Starting " << std::to_string(totalTests) << " tests" << std::endl;

	passedTests += mapTest(bomberMap, false);
	passedTests +=bombTest(bomberMap);
	passedTests +=fireTest(bomberMap);

	std::cout << std::endl << "Finished tests" << std::endl << "Tests passed " << std::to_string(passedTests) << "/" << std::to_string(totalTests) << std::endl;

	delete bomberMap;
	return (0);
}