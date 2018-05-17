#include <iostream>
#include <memory>
#include "Map.hpp"
#include "Bomb.hpp"

#define LOGIC_TIMEOUT_SECONDS 10

std::clock_t begin;

bool fireTestLogic(map::Map *bomberMap)
{
	begin = std::clock();

	while (bomberMap->getTileAt(0, 0)->containsObject(FIRE)) {		// Test conditon
		if (((std::clock() - begin) / (double) CLOCKS_PER_SEC) >= LOGIC_TIMEOUT_SECONDS)
			return false;
		bomberMap->updateTileObjects();
	}
	return true;
}

bool fireTest(map::Map *bomberMap)
{
	std::cout << std::endl << "Starting fire test" << std::endl << "Checking for existing fire... ";

	if (bomberMap->getTileAt(0, 0)->containsObject(FIRE))
		std::cout << "found" << std::endl;
	else {
		std::cout << "not found" << std::endl << "Force detonating bomb" << std::endl;

		bomberMap->addObjectToTile(0, 0, std::move(std::unique_ptr<object::AObject>(new object::Bomb(0, 0, 2, bomberMap))));
		bomberMap->getTileAt(0, 0)->getObject(BOMB)->detonate();
		bomberMap->getTileAt(0, 0)->getObject(BOMB)->update();

		std::cout << "Checking for fire... ";

		if (bomberMap->getTileAt(0, 0)->containsObject(FIRE))
			std::cout << "found" << std::endl;
		else {
			std::cout << "not found" << std::endl << "Test failed - please check bombs" << std::endl;
			return false;
		}
	}


	std::cout << "Starting fire test logic" << std::endl;

	if (!fireTestLogic(bomberMap)) {
		std::cout << "Fire test logic timed out" << std::endl << "Test failed" << std::endl;
		return false;
	}

	std::cout << "Fire dissipated" << std::endl << "Test passed" << std::endl;

	return true;
}

bool bombTestlogic(map::Map *bomberMap)
{
	begin = std::clock();

	while (bomberMap->getTileAt(0, 0)->containsObject(BOMB)) {		// Test conditon
		if (((std::clock() - begin) / (double) CLOCKS_PER_SEC) >= LOGIC_TIMEOUT_SECONDS)
			return false;
		bomberMap->updateTileObjects();
	}
	return true;
}

bool bombTest(map::Map *bomberMap)
{
	std::cout << std::endl << "Starting bomb test" << std::endl;

	std::cout << "Placing bomb" << std::endl;

	bomberMap->addObjectToTile(0, 0, std::move(std::unique_ptr<object::AObject>(new object::Bomb(0, 0, 2, bomberMap))));

	std::cout << "Checking for bomb... ";

	if (bomberMap->getTileAt(0, 0)->containsObject(BOMB))
			std::cout << "found" << std::endl;
	else {
		std::cout << "not found" << std::endl << "Test failed" << std::endl;
		return false;
	}

	std::cout << "Starting bomb test logic" << std::endl;

	if (!bombTestlogic(bomberMap)) {
		std::cout << "Bomb test logic timed out" << std::endl << "Test failed" << std::endl;
		return false;
	}

	std::cout << "Bomb exploded" << std::endl << "Checking for fire on affected tiles... ";

	if (bomberMap->getTileAt(0, 0)->containsObject(FIRE)
		&& bomberMap->getTileAt(0, 1)->containsObject(FIRE)
		&& bomberMap->getTileAt(0, 2)->containsObject(FIRE)
		&& bomberMap->getTileAt(1, 0)->containsObject(FIRE)
		&& bomberMap->getTileAt(2, 0)->containsObject(FIRE))
		std::cout << "found" << std::endl << "Test passed" << std::endl;
	else {
		std::cout << "not found" << std::endl << "Test failed" << std::endl;
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