//
// Created by jdecombe on 21/05/18.
//

#ifndef IRRLICHTTESTS_COLLIONSHANDLER_HPP
#define IRRLICHTTESTS_COLLIONSHANDLER_HPP

#include "Irrlicht/irrlicht.h"
#include "Gfx.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace map {
	class Map;
}

namespace object {
	class Player;
	class Box;
	class Bomb;
}

class CollisionsHandler {
		ISceneManager *_sceneManager;
		IMetaTriangleSelector *_metaTriangleSelector;

	public:
		explicit CollisionsHandler(Gfx const &gfx);
		virtual ~CollisionsHandler();

		void addObjectToCollisions(object::Player const &player);
		void addObjectToCollisions(IAnimatedMeshSceneNode *node,
			vector3df const &size
		);
		void addBombToCollisions(::object::Bomb const &bomb, vector3df const &size);
		void addBoxToCollisions(::object::Box *box, vector3df const &size);
		void addMapToCollision(::map::Map const &map);

		void removeCollisions(ITriangleSelector *selector);
};

#endif //IRRLICHTTESTS_COLLIONSHANDLER_HPP
