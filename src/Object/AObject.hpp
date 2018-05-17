//
// Created by Nicolas Guerin on 17/05/2018.
//

#pragma once

#include <string>

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

class AObject {
	protected:
		AObject(std::string path, Type type);
		std::string _pathToMesh;

	public:
		AObject() = delete;
		virtual ~AObject() = default;

		virtual void detonate() noexcept {}

		//Getter
		Type getType() const noexcept { return _type; }
		std::string getPathToMesh() const noexcept { return _pathToMesh; }

	private:
		Type 	_type;
};
}
