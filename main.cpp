#include <iostream>
#include <memory>
#include "Map.hpp"
#include "Bomb.hpp"
#include "Box.hpp"

#define LOGIC_TIMEOUT_SECONDS 10

std::clock_t begin;

bool lootTest(map::Map *bomberMap)
{
	std::cout << std::endl << "Starting loot test" << std::endl << "Spawning for box... ";
	std::cout.flush();

	auto loot = std::make_unique<object::Loot>();
	bomberMap->addObjectToTile(1, 0, std::move(std::unique_ptr<object::AObject>(new object::Box(std::move(loot)))));
	if (bomberMap->getTileAt(1, 0)->containsObject(BOX))
		std::cout << "passed" << std::endl;
	else {
		std::cout << "failed" << std::endl << "Test failed" << std::endl;
		return false;
	}

	std::cout << "Force detonating a bomb... ";
	std::cout.flush();

	bomberMap->addObjectToTile(0, 0, std::move(std::unique_ptr<object::AObject>(new object::Bomb(0, 0, 2, bomberMap))));
	bomberMap->getTileAt(0, 0)->getObject(BOMB)->detonate();
	bomberMap->getTileAt(0, 0)->getObject(BOMB)->update();

	if (bomberMap->getTileAt(0, 0)->containsObject(FIRE))
		std::cout << "passed" << std::endl;
	else {
		std::cout << "failed" << std::endl << "Test failed - please check bombs" << std::endl;
		return false;
	}

	std::cout << "Checking for destroyed box... ";
	std::cout.flush();

	if (!bomberMap->getTileAt(1, 0)->containsObject(BOX))
		std::cout << "passed" << std::endl;
	else {
		std::cout << "failed" << std::endl << "Test failed - please check bombs" << std::endl;
		return false;
	}

	std::cout << "Checking for loot... ";
	std::cout.flush();

	if (bomberMap->getTileAt(1, 0)->containsObject(LOOT))
		std::cout << "found" << std::endl;
	else
		std::cout << "not found - box was probably empty" << std::endl;

	return true;
}

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
	std::cout.flush();

	if (bomberMap->getTileAt(0, 0)->containsObject(FIRE))
		std::cout << "passed" << std::endl;
	else {
		std::cout << "failed" << std::endl << "Force detonating bomb" << std::endl;

		bomberMap->addObjectToTile(0, 0, std::move(std::unique_ptr<object::AObject>(new object::Bomb(0, 0, 2, bomberMap))));
		bomberMap->getTileAt(0, 0)->getObject(BOMB)->detonate();
		bomberMap->getTileAt(0, 0)->getObject(BOMB)->update();

		std::cout << "Checking for fire... ";
		std::cout.flush();

		if (bomberMap->getTileAt(0, 0)->containsObject(FIRE))
			std::cout << "passed" << std::endl;
		else {
			std::cout << "failed" << std::endl << "Test failed - please check bombs" << std::endl;
			return false;
		}
	}


	std::cout << "Waiting for fire to dissipate... ";
	std::cout.flush();

	if (!fireTestLogic(bomberMap)) {
		std::cout << "time out" << std::endl << "Test failed" << std::endl;
		return false;
	}

	std::cout << "passed" << std::endl << "Test passed" << std::endl;

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
	std::cout << std::endl << "Starting bomb test" << std::endl << "Checking for bomb... ";
	std::cout.flush();

	bomberMap->addObjectToTile(0, 0, std::move(std::unique_ptr<object::AObject>(new object::Bomb(0, 0, 2, bomberMap))));

	if (bomberMap->getTileAt(0, 0)->containsObject(BOMB))
			std::cout << "passed" << std::endl;
	else {
		std::cout << "failed" << std::endl << "Test failed" << std::endl;
		return false;
	}

	std::cout << "Checking for bomb explosion... ";
	std::cout.flush();

	if (!bombTestlogic(bomberMap)) {
		std::cout << "time out" << std::endl << "Test failed" << std::endl;
		return false;
	}

	std::cout << "passed" << std::endl << "Checking for fire on affected tiles... ";
	std::cout.flush();

	if (bomberMap->getTileAt(0, 0)->containsObject(FIRE)
		&& bomberMap->getTileAt(0, 1)->containsObject(FIRE)
		&& bomberMap->getTileAt(0, 2)->containsObject(FIRE)
		&& bomberMap->getTileAt(1, 0)->containsObject(FIRE)
		&& bomberMap->getTileAt(2, 0)->containsObject(FIRE))
		std::cout << "passed" << std::endl << "Test passed" << std::endl;
	else {
		std::cout << "failed" << std::endl << "Test failed" << std::endl;
		return false;
	}

	return true;
}

bool mapTestLogic(map::Map *bomberMap, Type objectType)
{
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			if (bomberMap->getTileAt(x, y)->getObjects().size() > 0) {
				for (auto &object : bomberMap->getTileAt(x, y)->getObjects()) {
					if (object.get()->getType() == objectType)
						return true;
				}
			}
		}
	}
	return false;
}

bool mapTest(map::Map *bomberMap)
{
	std::cout << std::endl << "Starting map test" << std::endl << "Checking for empty tile... ";
	std::cout.flush();

	bool breakEmptyTileLoop = false;

	for (int x = 0; x < MAP_SIZE; x++) {
		if (breakEmptyTileLoop)
			break;
		for (int y = 0; y < MAP_SIZE; y++) {
			if (bomberMap->getTileAt(x, y)->getObjects().size() > 0) {
				std::cout << "passed" << std::endl;
				breakEmptyTileLoop = true;
				break;
			}
		}
	}

	if (!breakEmptyTileLoop) {
		std::cout << "failed" << std::endl << "Test failed" << std::endl;
		return false;
	}

	std::cout << "Checking for tile with a wall... ";
	std::cout.flush();

	if (mapTestLogic(bomberMap, WALL))
		std::cout << "passed" << std::endl;
	else {
		std::cout << "failed" << std::endl << "Test failed" << std::endl;
		return false;
	}

	std::cout << "Checking for tile with a box... ";
	std::cout.flush();

	if (mapTestLogic(bomberMap, BOX))
		std::cout << "passed" << std::endl;
	else {
		std::cout << "failed" << std::endl << "Test failed" << std::endl;
		return false;
	}

	std::cout << "Test passed" << std::endl;
	return true;
}

int main()
{
	size_t totalTests = 4;
	size_t passedTests = 0;
	map::Map *bomberMap = new map::Map();

	std::cout << "Starting " << std::to_string(totalTests) << " tests" << std::endl;

	passedTests += mapTest(bomberMap);

	if (passedTests != 0) {
		passedTests += bombTest(bomberMap);
		passedTests += fireTest(bomberMap);
		passedTests += lootTest(bomberMap);
	}

	std::cout << std::endl << "Finished tests" << std::endl << "Tests passed " << std::to_string(passedTests) << "/" << std::to_string(totalTests) << std::endl;

	delete bomberMap;
	return (0);
}