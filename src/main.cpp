#include <iostream>
#include <AI.hpp>

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
	AI player2(&map, "", PLAYER2, &gfx, POMMY, 0, 0.1f, 0, false, 1);
	object::Player player1("", PLAYER1, &gfx, POMMY, 0, 0.1f, 5, false, 2);
	try {
		collisionsHandler.addObjectToCollisions(player2.getPlayer());
		collisionsHandler.addObjectToCollisions(player1);
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

	//player1.setAbsoluteRotation(180);
	while (gfx.isRunning()) {
		gfx.update();

		player2.update();
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

		if (gfx.isKeyDown(KEY_KEY_D))
			player.move(LEFT);
		if (gfx.isKeyDown(KEY_KEY_A))
			player.move(RIGHT);
		if (gfx.isKeyDown(KEY_KEY_W))
			player.move(FORWARD);
		if (gfx.isKeyDown(KEY_KEY_S))
			player.move(BACKWARD);

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