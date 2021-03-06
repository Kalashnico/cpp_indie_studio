//
// Created by Nicolas Guerin on 17/05/2018.
//

#pragma once

#include <ctime>
#include "AObject.hpp"
#include "Map.hpp"
#include "Gfx.hpp"

namespace object {

class Fire : public object::AObject {

	#define LIFE 0.4

	public:
		Fire(size_t posx, size_t posy, ::map::Map *map, Gfx *gfx);
		~Fire();

		void resetGfx() noexcept;

		void update() noexcept;
		irr::scene::IAnimatedMeshSceneNode *getNode() const { return _node; }

	private:
		void dissipate() noexcept;

		size_t _posx;
		size_t _posy;
		::map::Map *_map;
		Gfx *_gfx;
		irr::scene::IAnimatedMeshSceneNode *_node;

		bool _dissipated;
		std::clock_t _begin;
};

}
