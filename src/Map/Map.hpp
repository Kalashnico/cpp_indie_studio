//
// Created by jdecombe on 22/05/18.
//

#ifndef IRRLICHTTESTS_MAP_HPP
#define IRRLICHTTESTS_MAP_HPP

#pragma once

#include <vector>
#include <memory>
#include <ctime>
#include "Tile.hpp"
#include "Irrlicht/irrlicht.h"
#include "Gfx.hpp"

using namespace irr;

using namespace irr::core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#define MAP_SIZE	13
#define INDEX(x, y)	(MAP_SIZE * x + y)
#define END_TIME	1.0

namespace map {

	class Map {

		private:
			//Private member Functions
			void createMap() noexcept;
			void addBoxes() noexcept;
			bool isCornerTile(size_t x, size_t y) const noexcept;

			bool placeFire(int i, int x, int y) noexcept;

			//Variable
			std::vector<std::unique_ptr<Tile>> _map;
			Gfx *_gfx;
			ISceneManager *_sceneManager;
			IMeshSceneNode *_mapNode;
			ITriangleSelector *_selector;

			bool _playersDead[4];
			bool _end;
			std::clock_t _endTimer;

		public:
			Map();
			Map(Gfx *gfx);

			void setGfx(Gfx *gfx);

			void generateMap();


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
			void movePlayer(Type type, size_t oldx, size_t oldy, size_t newx, size_t newy) noexcept;

			void explodeBomb(size_t x, size_t y, size_t blastRadius) noexcept;

			void playerDied(int playerNb) noexcept;

			bool shouldEndGame() noexcept;

			virtual ~Map();
	};
};

#endif //IRRLICHTTESTS_MAP_HPP
