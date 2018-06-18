//
// Created by Nicolas Guerin on 24/05/2018.
//

#include <iostream>
#include "Core.hpp"
#include "SoundManager.hpp"

namespace core {

Core::Core()
{
	sound::SoundManager::getInstance().playBackground();

	_numPlayers = 1;
	_playerWon = -1;
	_playerWonTextSetup = true;
	_gfx.setEventReceiver(_eventReceiver);

	try {
		_gfx.addCameraFPS();
		_gfx.addLight(irr::core::vector3df(-30, 30, -30), irr::video::SColorf(1.0f, 1.0f, 1.0f), 20);
		_gfx.addLight(irr::core::vector3df(-30, 30, 30), irr::video::SColorf(1.0f, 1.0f, 1.0f), 20);
		_gfx.addLight(irr::core::vector3df(30, 30, -30), irr::video::SColorf(1.0f, 1.0f, 1.0f), 20);
		_gfx.addLight(irr::core::vector3df(30, 30, 30), irr::video::SColorf(1.0f, 1.0f, 1.0f), 20);
	} catch (...) {
		std::cerr << "Something went wrong" << std::endl;
		return;
	}
}

Core::~Core()
{}

void Core::run() noexcept
{
	menu();
}

void Core::menu() noexcept
{
	_gfx.getDevice()->getCursorControl()->setVisible(true);

	_env = _gfx.getDevice()->getGUIEnvironment();
	_env->getSkin()->setFont(_env->getFont("./media/fonts/OpenSans-Bold.png"));

	_elements.emplace_back(_env->addImage(_gfx.getDriver()->getTexture("./media/menu/title.png"), irr::core::position2d<int>(WIN_WIDTH / 6.5f, 10)));
	_elements.emplace_back(_env->addButton(irr::core::rect<irr::s32>(WIN_WIDTH / 2 - 52, 340, WIN_WIDTH / 2 + 52, 340 + 60), 0, PLAY_BUTTON, L"Play", L""));
	_elements.emplace_back(_env->addButton(irr::core::rect<irr::s32>(WIN_WIDTH / 2 - 52, 420, WIN_WIDTH / 2 + 52, 420 + 60), 0, QUIT_BUTTON, L"Quit", L""));
	_elements.emplace_back(_env->addButton(irr::core::rect<irr::s32>(WIN_WIDTH / 2 + 52, 580, WIN_WIDTH / 2 + 104, 580 + 60), 0, ADD_PLAYER_BUTTON, L">", L""));
	_elements.emplace_back(_env->addButton(irr::core::rect<irr::s32>(WIN_WIDTH / 2 - 104, 580, WIN_WIDTH / 2 - 52, 580 + 60), 0, REMOVE_PLAYER_BUTTON, L"<", L""));

	irr::core::stringw numPlayers = L"Number of players: ";
	numPlayers += _numPlayers;

	_elements.emplace_back(_env->addStaticText(numPlayers.c_str(), irr::core::rect<irr::s32>(WIN_WIDTH / 2 - 220, 500, WIN_WIDTH / 2 + 220, 500 + 60), false, false, 0, -1, false));
	auto playerNumElement = _elements.back();

	irr::core::stringw lastWinner = L"Player ";
	lastWinner += _playerWon;
	lastWinner += L" won!";

	if (_playerWon == 0)
		lastWinner = L"        Draw!";

	_elements.emplace_back(_env->addStaticText(lastWinner.c_str(), irr::core::rect<irr::s32>(WIN_WIDTH / 2 - 135, 660, WIN_WIDTH / 2 + 135, 660 + 60), false, false, 0, -1, false));
	auto playerWonElement = _elements.back();

	if (_playerWon == -1 && playerWonElement->isVisible())
		playerWonElement->setVisible(false);

	while (_gfx.isRunning()) {
		if (_gfx.isGuiButtonPressed(QUIT_BUTTON))
			return;

		if (_gfx.isGuiButtonPressed(PLAY_BUTTON))
			game();

		if (_gfx.isGuiButtonPressed(ADD_PLAYER_BUTTON)) {
			_numPlayers++;
			if (_numPlayers > 4)
				_numPlayers = 4;
		}

		if (_gfx.isGuiButtonPressed(REMOVE_PLAYER_BUTTON)) {
			_numPlayers--;
			if (_numPlayers < 0)
				_numPlayers = 0;
		}

		numPlayers = L"Number of players: ";
		numPlayers += _numPlayers;
		playerNumElement->setText(numPlayers.c_str());

		if (!_playerWonTextSetup) {
			irr::core::stringw lastWinner = L"Player ";
			lastWinner += _playerWon;
			lastWinner += L" won!";

			if (_playerWon == 0)
				lastWinner = L"        Draw!";

			playerWonElement->setText(lastWinner.c_str());

			if (_playerWon == -1)
				playerWonElement->setVisible(false);

			_playerWonTextSetup = true;
		}

		_gfx.update();
	}
}

void Core::game() noexcept
{
	for (auto _element : _elements)
		_element->setVisible(false);

	auto _map = std::make_unique<map::Map>(&_gfx);

	irr::core::vector3df tilePos1 = {0.f, 0.f, 0.f};
	irr::core::vector3df tilePos2 = {0.f, 0.f, MAP_SIZE - 1.f};
	irr::core::vector3df tilePos3 = {MAP_SIZE - 1.f, 0.f, 0.f};
	irr::core::vector3df tilePos4 = {MAP_SIZE - 1.f, 0.f, MAP_SIZE - 1.f};
	auto iPos1 = tileToIrrlicht(tilePos1);
	auto iPos2 = tileToIrrlicht(tilePos2);
	auto iPos3 = tileToIrrlicht(tilePos3);
	auto iPos4 = tileToIrrlicht(tilePos4);

	std::unique_ptr<object::AObject> player1;
	std::unique_ptr<object::AObject> player2;
	std::unique_ptr<object::AObject> player3;
	std::unique_ptr<object::AObject> player4;

	auto numPlayers = _numPlayers;

	(numPlayers > 0) ? player1 = std::make_unique<object::Player>(_map.get(), PLAYER1, &_gfx, POMMY, iPos1.X, iPos1.Y, iPos1.Z, false, 1)
			: player1 = std::make_unique<object::AI>(_map.get(), PLAYER1, &_gfx, POMMY, iPos1.X, iPos1.Y, iPos1.Z, false, 1);

	numPlayers--;

	(numPlayers > 0) ? player2 = std::make_unique<object::Player>(_map.get(), PLAYER2, &_gfx, RED_POMMY, iPos2.X, iPos2.Y, iPos2.Z, false, 2)
			: player2 = std::make_unique<object::AI>(_map.get(), PLAYER2, &_gfx, RED_POMMY, iPos2.X, iPos2.Y, iPos2.Z, false, 2);

	numPlayers--;

	(numPlayers > 0) ? player3 = std::make_unique<object::Player>(_map.get(), PLAYER3, &_gfx, PURPLE_POMMY, iPos3.X, iPos3.Y, iPos3.Z, false, 3)
			: player3 = std::make_unique<object::AI>(_map.get(), PLAYER3, &_gfx, PURPLE_POMMY, iPos3.X, iPos3.Y, iPos3.Z, false, 3);

	numPlayers--;

	(numPlayers > 0) ? player4 = std::make_unique<object::Player>(_map.get(), PLAYER4, &_gfx, BLUE_POMMY, iPos4.X, iPos4.Y, iPos4.Z, false, 4)
			: player4 = std::make_unique<object::AI>(_map.get(), PLAYER4, &_gfx, BLUE_POMMY, iPos4.X, iPos4.Y, iPos4.Z, false, 4);


	_map.get()->addObjectToTile(static_cast<size_t>(tilePos1.X), static_cast<size_t>(tilePos1.Y), std::move(player1));
	_map.get()->addObjectToTile(static_cast<size_t>(tilePos2.X), static_cast<size_t>(tilePos2.Y), std::move(player2));
	_map.get()->addObjectToTile(static_cast<size_t>(tilePos3.X), static_cast<size_t>(tilePos3.Y), std::move(player3));
	_map.get()->addObjectToTile(static_cast<size_t>(tilePos4.X), static_cast<size_t>(tilePos4.Y), std::move(player4));

	_gfx.getDevice()->getCursorControl()->setVisible(false);

	_begin = std::clock();

	while (_gfx.isRunning() && !_map.get()->shouldEndGame()) {

		if (_gfx.isKeyDown(irr::KEY_ESCAPE)) {
			_playerWon = -1;
			_playerWonTextSetup = false;
			_gfx.getDevice()->getCursorControl()->setVisible(true);
			for (auto _element : _elements)
				_element->setVisible(true);
			return;
		}

		if (((std::clock() - _begin) / (double) CLOCKS_PER_SEC) < (1.0 / 60.0))
			continue;

		_begin = std::clock();

		_gfx.update();
		_map.get()->updateTileObjects();
	}

	sound::SoundManager::getInstance().playWin();
	_playerWon = _map.get()->getWinner();

	_playerWonTextSetup = false;

	_gfx.getDevice()->getCursorControl()->setVisible(true);

	for (auto _element : _elements)
		_element->setVisible(true);
}

irr::core::vector3df Core::tileToIrrlicht(irr::core::vector3df tilePos) noexcept
{
	auto pos = tilePos;
	pos -= 6.f;
	pos *= 4.f;
	pos.Y = 0.1f;
	return pos;
}

}