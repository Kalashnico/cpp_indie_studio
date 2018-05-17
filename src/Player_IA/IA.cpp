/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Created by tclemenceau,
*/

#include <vector>
#include "IA.hpp"

IA::IA() :
	_player(new Player)
{
}

IA::~IA()
{
}

std::unique_ptr<Player> IA::getPlayer()
{
	return _player;
}

void IA::update(std::vector)
{

}

bool IA::move()
{

}

void IA::find_closest_player()
{
	std::array<int, 2> _xy;


}
