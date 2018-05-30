#include <memory>
#include <iostream>

#include "AI.hpp"
#include "Irrlicht/irrlicht.h"
#include "Graphic/CustomEventReceiver.hpp"
#include "Graphic/Gfx.hpp"
#include "Graphic/CollisionsHandler.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
	CustomEventReceiver eventReceiver;
	Gfx gfx(eventReceiver);
	CollisionsHandler collisionsHandler(gfx);
	::map::Map map(gfx.getSceneManager());
	auto player2 = std::make_unique<object::AI>(&map, "", PLAYER2, &gfx, POMMY, 0, 0.1f, 0, false, 2);
	auto player = std::make_unique<object::Player>(&map, "", PLAYER1, &gfx, POMMY, 0, 0.1f, 5, false, 1);
	auto tmp = player.get()->getPosition();
	auto tmp2 = player2.get()->getPlayer().getPosition();

	try {
		collisionsHandler.addObjectToCollisions(player2.get()->getPlayer());
		collisionsHandler.addObjectToCollisions(*player.get());
		collisionsHandler.addMapToCollision(map);
		gfx.addCameraFPS();
		gfx.addLight(vector3df(-30, 30, -30), SColorf(1.0f, 1.0f, 1.0f),
			20);
		gfx.addLight(vector3df(-30, 30, 30), SColorf(1.0f, 1.0f, 1.0f),
			20);
		gfx.addLight(vector3df(30, 30, -30), SColorf(1.0f, 1.0f, 1.0f),
			20);
		gfx.addLight(vector3df(30, 30, 30), SColorf(1.0f, 1.0f, 1.0f),
			20);
	} catch (...) {
		std::cerr << "An error occured >,<" << std::endl;
		return -1;
	}

	player.get()->setAbsoluteRotation(180);

	std::unique_ptr<object::AObject> playerObject = std::move(player);
	std::unique_ptr<object::AObject> player2Object = std::move(player2);
	map.addObjectToTile(static_cast<size_t>(tmp.X), static_cast<size_t>(tmp.Y), std::move(playerObject));
	map.addObjectToTile(static_cast<size_t>(tmp2.X), static_cast<size_t>(tmp2.Y), std::move(player2Object));
	while (gfx.isRunning()) {
		gfx.update();
		map.updateTileObjects();

		if (gfx.isKeyDown(KEY_ESCAPE))
			return 0;
		/*
		if (gfx.isKeyDown(KEY_F1))
			player2.setAbsoluteRotation(LEFT);
		if (gfx.isKeyDown(KEY_F2))
			player2.setAbsoluteRotation(RIGHT);
		if (gfx.isKeyDown(KEY_F3))
			player2.setAbsoluteRotation(FORWARD);
		if (gfx.isKeyDown(KEY_F4))
			player2.setAbsoluteRotation(BACKWARD);
		*/


		/*
		if (gfx.isKeyDown(KEY_KEY_D))
			player.move(LEFT);
		else if (gfx.isKeyDown(KEY_KEY_Q))
			player.move(RIGHT);
		else if (gfx.isKeyDown(KEY_KEY_Z))
			player.move(FORWARD);
		else if (gfx.isKeyDown(KEY_KEY_S))
			player.move(BACKWARD);
		*/

		/*
		if (gfx.isKeyDown(KEY_RIGHT))
			player2.moveCase(LEFT);
		if (gfx.isKeyDown(KEY_LEFT))
			player2.moveCase(RIGHT);
		if (gfx.isKeyDown(KEY_UP))
			player2.moveCase(FORWARD);
		if (gfx.isKeyDown(KEY_DOWN))
			player2.moveCase(BACKWARD);*/
	}
	return 0;
}