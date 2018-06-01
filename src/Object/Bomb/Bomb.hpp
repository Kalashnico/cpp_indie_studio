//
// Created by Nicolas Guerin on 17/05/2018.
//

#pragma once

#include <ctime>
#include "AObject.hpp"
#include "Map.hpp"
#include "Gfx.hpp"

namespace object {

class Bomb : public AObject {

	#define LIFE 3.0
	#define CYCLE 0.5

	public:
		Bomb(int posx, int posy, int blast, ::map::Map *map, Gfx *gfx);
		~Bomb();

		IAnimatedMeshSceneNode *getNode() const { return _node; }

		void detonate() noexcept { _detonate = true; }
		void update() noexcept;

	private:
		void explode() noexcept;

		int _posx;
		int _posy;
		int _blastSize;
		::map::Map *_map;
		Gfx *_gfx;
		IAnimatedMeshSceneNode *_node;

		std::clock_t _begin;

		bool _detonate;
		bool _hasExploded;

};
}
