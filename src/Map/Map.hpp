//
// Created by jdecombe on 22/05/18.
//

#ifndef IRRLICHTTESTS_MAP_HPP
#define IRRLICHTTESTS_MAP_HPP

#include "Irrlicht/irrlicht.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Map {

	private:
		ISceneManager		*_sceneManager;
		IMeshSceneNode		*_mapNode;
		ITriangleSelector	*_selector;


	public:
		IMeshSceneNode *getMapNode() const;

		Map(ISceneManager *sceneManager);

		ITriangleSelector *getSelector() const;

		virtual ~Map();
};

#endif //IRRLICHTTESTS_MAP_HPP
