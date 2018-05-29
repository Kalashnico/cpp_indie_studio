//
// Created by jdecombe on 21/05/18.
//

#ifndef IRRLICHTTESTS_COLLIONSHANDLER_HPP
#define IRRLICHTTESTS_COLLIONSHANDLER_HPP

#include "Irrlicht/irrlicht.h"
#include "../Player_AI/Player.hpp"
#include "../Map/Map.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CollisionsHandler {
		ISceneManager *_sceneManager;
		IMetaTriangleSelector *_metaTriangleSelector;

	public:
		explicit CollisionsHandler(Gfx const &gfx);
		virtual ~CollisionsHandler();

		void addObjectToCollisions(Player const &player);
		void addObjectToCollisions(IAnimatedMeshSceneNode *node,
			vector3df const &size
		);
		void addMapToCollision(Map const &map);
};

#endif //IRRLICHTTESTS_COLLIONSHANDLER_HPP
