//
// Created by Nicolas Guerin on 24/05/2018.
//

#include <iostream>
#include "Core.hpp"
#include "SoundManager.hpp"

namespace core {

Core::Core(int numPlayers)
{

	_gfx.setEventReceiver(_eventReceiver);
	_map.setGfx(&_gfx);

	vector3df tilePos1 = {0.f, 0.f, 0.f};
	vector3df tilePos2 = {0.f, 0.f, MAP_SIZE - 1.f};
	vector3df tilePos3 = {MAP_SIZE - 1.f, 0.f, 0.f};
	vector3df tilePos4 = {MAP_SIZE - 1.f, 0.f, MAP_SIZE - 1.f};
	auto iPos1 = tileToIrrlicht(tilePos1);
	auto iPos2 = tileToIrrlicht(tilePos2);
	auto iPos3 = tileToIrrlicht(tilePos3);
	auto iPos4 = tileToIrrlicht(tilePos4);

	std::unique_ptr<object::AObject> player1;
	std::unique_ptr<object::AObject> player2;
	std::unique_ptr<object::AObject> player3;
	std::unique_ptr<object::AObject> player4;

	(numPlayers > 0) ? player1 = std::make_unique<object::Player>(&_map, PLAYER1, &_gfx, POMMY, iPos1.X, iPos1.Y, iPos1.Z, false, 1)
			: player1 = std::make_unique<object::AI>(&_map, PLAYER1, &_gfx, POMMY, iPos1.X, iPos1.Y, iPos1.Z, false, 1);

	numPlayers--;

	(numPlayers > 0) ? player2 = std::make_unique<object::Player>(&_map, PLAYER2, &_gfx, POMMY, iPos2.X, iPos2.Y, iPos2.Z, false, 2)
			: player2 = std::make_unique<object::AI>(&_map, PLAYER2, &_gfx, POMMY, iPos2.X, iPos2.Y, iPos2.Z, false, 2);

	numPlayers--;

	(numPlayers > 0) ? player3 = std::make_unique<object::Player>(&_map, PLAYER3, &_gfx, POMMY, iPos3.X, iPos3.Y, iPos3.Z, false, 3)
			: player3 = std::make_unique<object::AI>(&_map, PLAYER3, &_gfx, POMMY, iPos3.X, iPos3.Y, iPos3.Z, false, 3);

	numPlayers--;

	(numPlayers > 0) ? player4 = std::make_unique<object::Player>(&_map, PLAYER4, &_gfx, POMMY, iPos4.X, iPos4.Y, iPos4.Z, false, 4)
			: player4 = std::make_unique<object::AI>(&_map, PLAYER4, &_gfx, POMMY, iPos4.X, iPos4.Y, iPos4.Z, false, 4);

	try {
		_gfx.addCameraFPS();
		_gfx.addLight(vector3df(-30, 30, -30), SColorf(1.0f, 1.0f, 1.0f), 20);
		_gfx.addLight(vector3df(-30, 30, 30), SColorf(1.0f, 1.0f, 1.0f), 20);
		_gfx.addLight(vector3df(30, 30, -30), SColorf(1.0f, 1.0f, 1.0f), 20);
		_gfx.addLight(vector3df(30, 30, 30), SColorf(1.0f, 1.0f, 1.0f), 20);
	} catch (...) {
		std::cerr << "Something went wrong" << std::endl;
		return;
	}

	_map.addObjectToTile(static_cast<size_t>(tilePos1.X), static_cast<size_t>(tilePos1.Y), std::move(player1));
	_map.addObjectToTile(static_cast<size_t>(tilePos2.X), static_cast<size_t>(tilePos2.Y), std::move(player2));
	_map.addObjectToTile(static_cast<size_t>(tilePos3.X), static_cast<size_t>(tilePos3.Y), std::move(player3));
	_map.addObjectToTile(static_cast<size_t>(tilePos4.X), static_cast<size_t>(tilePos4.Y), std::move(player4));
}

Core::~Core()
{}

void Core::run() noexcept
{

	sound::SoundManager::getInstance().playBackground();

	_begin = std::clock();

	while (_gfx.isRunning() && !_map.shouldEndGame()) {

		if (_gfx.isKeyDown(KEY_ESCAPE))
			return;

		if (((std::clock() - _begin) / (double) CLOCKS_PER_SEC) < (1.0 / 60.0))
			continue;

		_begin = std::clock();

		_gfx.update();
		_map.updateTileObjects();
	}
}

vector3df Core::tileToIrrlicht(vector3df tilePos) noexcept
{
	auto pos = tilePos;
	pos -= 6.f;
	pos *= 4.f;
	pos.Y = 0.1f;
	return pos;
}

}