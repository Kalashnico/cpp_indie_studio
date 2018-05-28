/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Created by tclemenceau,
*/

#include <vector>
#include "AI.hpp"

AI::AI(map::Map *map, std::string mesh, Type type) : _player(
	new object::Player(mesh, type)), _map(map)
{
}

AI::~AI()
{
}

std::unique_ptr<object::Player> AI::getPlayer()
{
	return _player;
}

void AI::update()
{
	this->find_closest_player();
}

bool AI::move()
{
}

void AI::find_closest_player()
{
	std::array<int, 2> xy{};
	std::vector<std::unique_ptr<map::Tile>> map;

	map = _map->getMap();
	for (auto &tile : map) {
		for (auto &object : tile.get()->getObjects())
			if ((object.get()->getType() == PLAYER1 ||
				object.get()->getType() == PLAYER2 ||
				object.get()->getType() == PLAYER3 ||
				object.get()->getType() == PLAYER4) &&
				object.get()->getType() !=
					_player.get()->getType())
				return;
	}
}
