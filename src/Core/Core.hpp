//
// Created by Nicolas Guerin on 24/05/2018.
//

#pragma once

#include <memory>
#include "Map.hpp"
#include "AI.hpp"

namespace core {

class Core {
	public:
		Core(int numPlayers);
		~Core();

		void run() noexcept;

	private:
		CustomEventReceiver _eventReceiver;
		Gfx _gfx;
		::map::Map _map;

		std::clock_t _begin;

		bool shouldEndGame() const noexcept;
		irr::core::vector3df tileToIrrlicht(irr::core::vector3df tilePos) noexcept;
};

}