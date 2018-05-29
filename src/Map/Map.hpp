//
// Created by jdecombe on 22/05/18.
//

#ifndef IRRLICHTTESTS_MAP_HPP
#define IRRLICHTTESTS_MAP_HPP

#pragma once

#include <vector>
#include <memory>
#include "Tile.hpp"
#include "Irrlicht/irrlicht.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#define MAP_SIZE	15
#define INDEX(x, y)	(MAP_SIZE * x + y)

namespace map {

	class Map {

		private:
			//Private member Functions
			void createMap() noexcept;
			void addBoxes() noexcept;
			bool isCornerTile(size_t x, size_t y) const noexcept;

			bool placeFire(int i, size_t x, size_t y) noexcept;

			//Variable
			std::vector<std::unique_ptr<Tile>> _map;
			ISceneManager *_sceneManager;
			IMeshSceneNode *_mapNode;
			ITriangleSelector *_selector;

		public:

			Map(ISceneManager *sceneManager);


			//Getter

			IMeshSceneNode *getMapNode() const;
			ITriangleSelector *getSelector() const;
			std::vector<std::unique_ptr<Tile>> &getMap() noexcept { return _map; };
			Tile *getTileAt(size_t x, size_t y) noexcept { return _map[INDEX(x, y)].get(); }
			size_t getTileIndex(size_t x, size_t y) const noexcept { return INDEX(x, y); }

			//Other functions

			void addObjectToTile(size_t x, size_t y, std::unique_ptr<object::AObject>) noexcept;
			void updateTileObjects() noexcept;
			void removeObjectFromTile(size_t x, size_t y, Type objectType) noexcept;

			void explodeBomb(size_t x, size_t y, size_t blastRadius) noexcept;

			virtual ~Map();
	};
};

#endif //IRRLICHTTESTS_MAP_HPP
