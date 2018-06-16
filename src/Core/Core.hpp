//
// Created by Nicolas Guerin on 24/05/2018.
//

#pragma once

#include <memory>
#include "Map.hpp"
#include "AI.hpp"


namespace core {

enum guiElements {
	TITLE = 100,
	PLAY_BUTTON = 101,
	QUIT_BUTTON = 102,
	ADD_PLAYER_BUTTON = 103,
	REMOVE_PLAYER_BUTTON = 104
};

class Core {
	public:
		Core();
		~Core();

		void run() noexcept;

	private:
		int _numPlayers;
		int _playerWon;
		bool _playerWonTextSetup;

		std::vector<irr::gui::IGUIElement *> _elements;

		CustomEventReceiver _eventReceiver;
		Gfx _gfx;
		irr::gui::IGUIEnvironment *_env;

		std::clock_t _begin;

		void menu() noexcept;
		void game() noexcept;
		irr::core::vector3df tileToIrrlicht(irr::core::vector3df tilePos) noexcept;
};

}