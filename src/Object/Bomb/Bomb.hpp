//
// Created by Nicolas Guerin on 17/05/2018.
//

#pragma once

#include <ctime>
#include "AObject.hpp"
#include "Map.hpp"

namespace object {

class Bomb : public AObject {

	#define LIFE 3.0
	#define CYCLE 0.5

	public:
		Bomb(int posx, int posy, int blast, ::map::Map *map);
		~Bomb();

		void detonate() noexcept { _detonate = true; }
		void update() noexcept;

	private:
		void explode() noexcept;

		int _posx;
		int _posy;
		int _blastSize;
		::map::Map *_map;
		std::clock_t _begin;

		bool _detonate;
		bool _hasExploded;

};
}
