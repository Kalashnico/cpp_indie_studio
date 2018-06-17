//
// Created by jdecombe on 14/05/18.
//

#pragma once

#include <string>
#include <thread>
#include <unordered_map>
#include "Irrlicht/irrlicht.h"
#include "CustomEventReceiver.hpp"
#include "Gfx.hpp"
#include "AObject.hpp"
#include "Map.hpp"

enum rotationDirection_e {
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD,
	NONE
};

struct playerSpriteInfo_s {
	std::string path;
	irr::core::vector3df scale;
};

using playerSpriteInfo_t = playerSpriteInfo_s;

enum playerSprite_e {
	POMMY = 1 << 0,
	UNKNOWN = 1 << 1,
		RED_POMMY = 1 << 2,
			BLUE_POMMY = 1 << 3,
				PURPLE_POMMY = 1 << 4
};

#define MOVEMENT_SPEED 0.2

namespace object {

	class Player : public AObject {
		private:
			::map::Map *_map;
			Gfx *_gfx;
			bool _useController;
			size_t _playerNb;
			irr::scene::IAnimatedMeshSceneNode *_playerNode;

			// Rotation
			std::thread _rotationThread;
			bool _rotateStop;

			void rotateThreadHandler(float maxAngle, float curAngle,
				std::string name
			);

			std::clock_t _placementCooldownClock;
			float _placementCooldown = 0.25f;

			int _placedBombs = 0;
			int _maxBombs = 1;
			int _blastRadius = 1;
			float _speedBonus = 0.f;
			bool _walkThroughBoxes = false;

			bool _dead;

		public:

			Player(::map::Map *map, Type type, Gfx *gfx, playerSprite_e playerType, float x,
				float y, float z, bool useController,
				unsigned long playerNb
			);

			virtual ~Player();

			void update() noexcept;
			void updatePosition(size_t oldx, size_t oldy) noexcept;

			void pickupLoot(irr::core::vector2di tilePos) noexcept;

			void bombExploaded() noexcept;
			void placeBomb() noexcept;

			irr::core::vector2di getPosition() noexcept;
			irr::core::vector2df getPositionFloat();

			bool canWalkThroughBoxes() const noexcept { return _walkThroughBoxes; }

			bool hasCollided(irr::core::vector2di tilePos) noexcept;
			void move(enum rotationDirection_e dir = FORWARD,
				float spd = MOVEMENT_SPEED
			);

			void setAbsoluteRotation(float maxAngle);

			void setAbsoluteRotation(
				enum rotationDirection_e rotation
			);
			int getBlastRadius() noexcept;
			bool checkDeath() noexcept;
			void die() noexcept;

			irr::scene::IAnimatedMeshSceneNode *getNode() const;
	};
};
