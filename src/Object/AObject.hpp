//
// Created by Nicolas Guerin on 17/05/2018.
//

#pragma once

#include <string>
#include <memory>
#include "Irrlicht/irrlicht.h"

enum Type {
	WALL,
	BOX,
	LOOT,
	BOMB,
	FIRE,
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4
};

namespace object {

enum LootCategory {
	EMPTY,
	BOMB_UP,
	FIRE_UP,
	SPEED_UP,
	WALL_PASS
};

class Loot;

class AObject {
	protected:
		AObject(Type type);

	public:
		AObject() = delete;
		virtual ~AObject() = default;

		virtual void resetGfx() noexcept {}

		virtual void detonate() noexcept {}
		virtual std::unique_ptr<Loot> getLoot() noexcept;
		virtual LootCategory getLootCategory() const noexcept {}

		virtual void update() noexcept {}
		virtual void updatePosition(size_t oldx, size_t oldy) noexcept {}

		virtual irr::core::vector2di getPosition() noexcept { return {0, 0}; }

		//Getter
		Type getType() const noexcept { return _type; }

		bool toBeDestroyed() const noexcept { return _toBeDestroyed; }
		void destroy() noexcept { _toBeDestroyed = true; }

	private:
		Type 	_type;
		bool	_toBeDestroyed;
};
}
