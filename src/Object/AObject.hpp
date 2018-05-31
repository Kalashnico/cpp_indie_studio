//
// Created by Nicolas Guerin on 17/05/2018.
//

#pragma once

#include <string>
#include <memory>

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
		AObject(std::string path, Type type);
		std::string _pathToMesh;

	public:
		AObject() = delete;
		virtual ~AObject() = default;

		virtual void detonate() noexcept {}
		virtual std::unique_ptr<Loot> getLoot() noexcept;
		virtual LootCategory getLootCategory() const noexcept {}
		virtual void update() noexcept {}
		virtual void updatePosition(size_t oldx, size_t oldy) noexcept {}

		//Getter
		Type getType() const noexcept { return _type; }
		std::string getPathToMesh() const noexcept { return _pathToMesh; }

		bool toBeDestroyed() const noexcept { return _toBeDestroyed; }
		void destroy() noexcept { _toBeDestroyed = true; }

	private:
		Type 	_type;
		bool	_toBeDestroyed;
};
}
