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
	::map::Map map(&gfx, &collisionsHandler);
	vector3df pos = {0.f, 0.f, 0.f};
	pos -= 6.f;
	pos *= 4.f;
	pos.Y = 0.1f;
	auto player = std::make_unique<object::Player>(&map, "", PLAYER1, &gfx, POMMY, pos.X, pos.Y, pos.Z, false, 1);
	vector3df pos2 = {0.f, 0.f, MAP_SIZE - 1.f};
	pos2 -= 6.f;
	pos2 *= 4.f;
	pos2.Y = 0.1f;
	auto player2 = std::make_unique<object::AI>(&map, "", PLAYER2, &gfx, POMMY, pos2.X, pos2.Y, pos2.Z, false, 2);
	auto tmp = player.get()->getPosition();
	auto tmp2 = player2.get()->getPlayer().getPosition();

	try {
		collisionsHandler.addObjectToCollisions(*player.get());
		collisionsHandler.addObjectToCollisions(player2.get()->getPlayer());
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

	map.addObjectToTile(static_cast<size_t>(tmp.X), static_cast<size_t>(tmp.Y), std::move(player));
	map.addObjectToTile(static_cast<size_t>(tmp2.X), static_cast<size_t>(tmp2.Y), std::move(player2));

	auto begin = std::clock();

	while (gfx.isRunning()) {

		if (gfx.isKeyDown(KEY_ESCAPE))
			return 0;

		if (((std::clock() - begin) / (double) CLOCKS_PER_SEC) < (1.0 / 60.0))
			continue;

		begin = std::clock();

		gfx.update();
		map.updateTileObjects();
	}
	return 0;
}