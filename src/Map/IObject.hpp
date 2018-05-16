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
	LOOT,
	BOMB,
	FIRE,
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4
};

namespace map {

class IObject {
	public:
		virtual ~IObject() = default;
		bool operator==(const IObject &rhs) { return _type == rhs._type; }

		Type getType() const noexcept { return _type; }

	protected:
		void setType(Type type) noexcept { _type = type; }

	private:
		Type _type;
};

}

