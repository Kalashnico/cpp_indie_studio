#include <iostream>

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
	Player player(&gfx, POMMY, 0, 0.1f, 0, false, 1);
	Player player2(&gfx, POMMY, 0, 0.1f, 5, false, 2);
	Map map(gfx.getSceneManager());
	try {
		collisionsHandler.addObjectToCollisions(player);
		collisionsHandler.addObjectToCollisions(player2);
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

	player.setAbsoluteRotation(180);
	while (gfx.isRunning()) {
		gfx.update();
		if (gfx.isKeyDown(KEY_ESCAPE))
			return 0;
		if (gfx.isKeyDown(KEY_F1))
			player.setAbsoluteRotation(LEFT);
		if (gfx.isKeyDown(KEY_F2))
			player.setAbsoluteRotation(RIGHT);
		if (gfx.isKeyDown(KEY_F3))
			player.setAbsoluteRotation(FORWARD);
		if (gfx.isKeyDown(KEY_F4))
			player.setAbsoluteRotation(BACKWARD);


		if (gfx.isKeyDown(KEY_KEY_D))
			player.rotate(LEFT);
		if (gfx.isKeyDown(KEY_KEY_A))
			player.rotate(RIGHT);
		if (gfx.isKeyDown(KEY_KEY_W))
			player.moveForward();
		if (gfx.isKeyDown(KEY_KEY_S))
			player.moveForward(BACKWARD);

		if (gfx.isKeyDown(KEY_RIGHT))
			player2.rotate(LEFT);
		if (gfx.isKeyDown(KEY_LEFT))
			player2.rotate(RIGHT);
		if (gfx.isKeyDown(KEY_UP))
			player2.moveForward();
		if (gfx.isKeyDown(KEY_DOWN))
			player2.moveForward(BACKWARD);
	}
	return 0;
}