/*
** EPITECH PROJECT, 2018
** Bomberman
** File description:
** Map object
*/

#pragma once

enum Type {
	WALL,
	BOX,
	PLAYER,
	LOOT,
	BOMB,
	FIRE
};

namespace map {

class IObject {
	public:
		virtual ~IObject() = default;

		bool operator==(const IObject &rhs) { return _type == rhs._type; }

	private:
		Type _type;
};

}

