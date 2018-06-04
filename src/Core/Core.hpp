//
// Created by Nicolas Guerin on 24/05/2018.
//

#pragma once

#include <memory>
#include "Map.hpp"

namespace core {

class Core {
	public:
		Core(size_t numPlayers);
		~Core();

		void run() noexcept;

	private:
		std::unique_ptr<map::Map> _map;
		std::unique_ptr<object::AObject> _player1;
		std::unique_ptr<object::AObject> _player2;
		std::unique_ptr<object::AObject> _player3;
		std::unique_ptr<object::AObject> _player4;
};

}