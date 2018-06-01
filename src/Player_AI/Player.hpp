//
// Created by jdecombe on 14/05/18.
//

#ifndef IRRLICHTTESTS_PLAYER_HPP
#define IRRLICHTTESTS_PLAYER_HPP

#include <string>
#include <thread>
#include <unordered_map>
#include "Irrlicht/irrlicht.h"
#include "CustomEventReceiver.hpp"
#include "Gfx.hpp"
#include "AObject.hpp"
#include "Map.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

enum rotationDirection_e {
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD,
	NONE
};

struct playerSpriteInfo_s {
	std::string path;
	vector3df scale;
};

using playerSpriteInfo_t = playerSpriteInfo_s;

enum playerSprite_e {
	POMMY = 1 << 0,
	UNKNOWN = 1 << 1
};

#define MOVEMENT_SPEED 0.2

namespace object {

	class Player : public AObject {
		private:
			::map::Map *_map;
			Gfx *_gfx;
			bool _useController;
			size_t _playerNb;
			IAnimatedMeshSceneNode *_playerNode;

			// Rotation
			std::thread _rotationThread;
			bool _rotateStop;

			void rotateThreadHandler(float maxAngle, float curAngle,
				std::string name
			);

			int _placedBombs = 0;
			int _maxBombs = 1;
			int _blastRadius = 2;

		public:

			Player(::map::Map *map, std::string path, Type type, Gfx *gfx, playerSprite_e playerType, float x,
				float y, float z, bool useController,
				unsigned long playerNb
			);

			virtual ~Player();

			void update() noexcept;
			void updatePosition(size_t oldx, size_t oldy) noexcept;

			void placeBomb() noexcept;

			vector2di getPosition();

			void move(enum rotationDirection_e dir = FORWARD,
				float spd = MOVEMENT_SPEED
			);

			void setAbsoluteRotation(float maxAngle);

			void setAbsoluteRotation(
				enum rotationDirection_e rotation
			);

			IAnimatedMeshSceneNode *getNode() const;
	};
};

#endif //IRRLICHTTESTS_PLAYER_HPP
