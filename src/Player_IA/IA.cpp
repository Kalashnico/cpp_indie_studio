/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Created by tclemenceau,
*/

#include <vector>
#include "IA.hpp"

IA::IA(map::Map *map) : _player(new Player), _map(map)
{
}

IA::~IA()
{
}

std::unique_ptr<Player> IA::getPlayer()
{
	return _player;
}

void IA::update()
{
	this->find_closest_player();
}

bool IA::move()
{
}

void IA::find_closest_player()
{
	std::array<int, 2> xy{};
	std::vector<std::unique_ptr<map::Tile>> map;

	map = _map->getMap();
	for (auto &tile : map) {
		for (auto &object : tile.get()->getObjects())
			if ((object.get()->getType() == PLAYER1 ||
				object.get()->getType() == PLAYER2 ||
				object.get()->getType() == PLAYER3 ||
				object.get()->getType() == PLAYER4))
	}
}
