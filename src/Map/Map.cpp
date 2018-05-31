//
// Created by jdecombe on 22/05/18.
//

#include <exception>
#include <random>
#include <iostream>
#include "Map.hpp"
#include "Box.hpp"
#include "Wall.hpp"
#include "Fire.hpp"

namespace map {

	Map::Map(ISceneManager *sceneManager) : _sceneManager(sceneManager)
	{
		createMap();
		addBoxes();

		auto mesh = _sceneManager->getMesh("./media/map/map_indie.obj");
		if (!mesh)
			throw std::exception();
		_mapNode = _sceneManager->addOctreeSceneNode(mesh->getMesh(0),
			nullptr, 0);
		_mapNode->setScale(vector3df(2, 2, 2));
		if (!_mapNode)
			throw std::exception();
		_selector = _sceneManager->createOctreeTriangleSelector(
			_mapNode->getMesh(), _mapNode, 128);
	}

	Map::~Map() = default;

	ITriangleSelector *Map::getSelector() const
	{
		return _selector;
	}

	IMeshSceneNode *Map::getMapNode() const
	{
		return _mapNode;
	}

	/**
	 * END OF GRAPHIC MAP
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
					getTileAt(x, y)->addObject(
						std::move(wall));
					getTileAt(x, y)->setSetup(true);
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
			tile.get()->updateTile();
		}
	}

	bool Map::isCornerTile(size_t x, size_t y) const noexcept
	{
		return (x == 0 && y == 0) || (x == 0 && y == 1) ||
		(x == 1 && y == 0) || (x == 0 && y == MAP_SIZE - 1) ||
		(x == 0 && y == MAP_SIZE - 2) ||
		(x == 1 && y == MAP_SIZE - 1) ||
		(x == MAP_SIZE - 1 && y == 0) ||
		(x == MAP_SIZE - 2 && y == 0) ||
		(x == MAP_SIZE - 1 && y == 1) ||
		(x == MAP_SIZE - 1 && y == MAP_SIZE - 1) ||
		(x == MAP_SIZE - 1 && y == MAP_SIZE - 2) ||
		(x == MAP_SIZE - 2 && y == MAP_SIZE - 1);
	}

	/**
 	* Add boxes to fill the map (nearly ~90% of the map)
 	* @param map without boxes
 	* @return map done
 	*/

	void Map::addBoxes() noexcept
	{
		std::random_device randomDevice;                        // Random device
		std::mt19937 engine(randomDevice());                        // Seed
		std::uniform_int_distribution<> distribution(1, 10);        // Range

		for (int x = 0; x < MAP_SIZE; x++) {
			for (int y = 0; y < MAP_SIZE; y++) {
				if (isCornerTile(x, y)) {                // Player spawn check
					getTileAt(x, y)->setSetup(true);
					continue;
				}

				if (x % 2 == 1 && y % 2 == 1)                // Wall check
					continue;

				if (distribution(engine) < 9) {                // Generate random number - 8/10 chance to spawn box
					auto loot = std::make_unique<object::Loot>();
					std::unique_ptr<object::AObject> box = std::make_unique<object::Box>(std::move(loot));
					getTileAt(x, y)->addObject(std::move(box));
				}
				getTileAt(x, y)->setSetup(true);
			}
		}
	}

	void Map::addObjectToTile(size_t x, size_t y,
		std::unique_ptr<object::AObject> object
	) noexcept
	{
		getTileAt(x, y)->addObject(std::move(object));
	}

	void Map::removeObjectFromTile(size_t x, size_t y, Type objectType
	) noexcept
	{
		getTileAt(x, y)->removeObject(objectType);
	}

	void Map::movePlayer(Type type, size_t oldx, size_t oldy, size_t newx, size_t newy) noexcept
	{
		auto player = getTileAt(oldx, oldy)->removePlayer(type);

		if (player == nullptr)
			return;

		addObjectToTile(newx, newy, std::move(player));
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
			auto loot = getTileAt(x, y)->getObject(
				BOX)->getLoot();                                                // Remove loot from box

			removeObjectFromTile(x, y,
				BOX);                                                                        // Remove box
			addObjectToTile(x, y, std::move(
				std::unique_ptr<object::AObject>(
					new object::Fire(x, y,
						this))));        // Place fire

			if (loot.get()->getLootCategory() !=
				object::EMPTY)                                                                // Check empty loot
				addObjectToTile(x, y, std::move(
					loot));                                                                // Add loot to tile

			return false;
		}

		addObjectToTile(x, y, std::move(
			std::unique_ptr<object::AObject>(
				new object::Fire(x, y, this))));
		return true;
	}

	void Map::explodeBomb(size_t x, size_t y, size_t blastRadius) noexcept
	{
		removeObjectFromTile(x, y, BOMB);
		addObjectToTile(x, y, std::move(
			std::unique_ptr<object::AObject>(
				new object::Fire(x, y, this))));

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