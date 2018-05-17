//
// Created by Nicolas Guerin on 17/05/2018.
//

#pragma once

#include <Map.hpp>
#include <thread>
#include "AObject.hpp"

namespace object {

class Bomb : public AObject {
	public:
		Bomb(int posx, int posy, int blast, map::Map *map);
		~Bomb();

		void detonate() noexcept { _detonate = true; }
		void  bombFuse() noexcept;

	private:

		int _posx;
		int _posy;
		int _blastSize;
		map::Map *_map;

		bool	_detonate;

};
}
