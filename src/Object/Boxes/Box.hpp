//
// Created by Nicolas Guerin on 14/05/2018.
//

#pragma once

#include "AObject.hpp"
#include "Loot.hpp"
#include "Gfx.hpp"

namespace map {
	class Map;
}

namespace object {

class Box : public AObject {
	public:
		Box(std::unique_ptr<Loot> loot, ::map::Map *map, Gfx *gfx, int posx, int posy);
		~Box() ;

		std::unique_ptr<Loot> getLoot() noexcept { return std::move(_loot); }
		irr::scene::IAnimatedMeshSceneNode *getNode() const { return _node; }

	private:
		std::unique_ptr<Loot> _loot;
		::map::Map *_map;
		Gfx *_gfx;
		irr::scene::IAnimatedMeshSceneNode *_node;

		int _posx;
		int _posy;
};
}
