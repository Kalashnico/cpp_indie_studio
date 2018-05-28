/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Created by tclemenceau,
*/

#ifndef INDIESTUDIO_AI_HPP
#define INDIESTUDIO_AI_HPP

#include <bits/unique_ptr.h>
#include "Map.hpp"
#include "Player.hpp"
#include "Tile.hpp"

class AI {
	public:
		AI(map::Map *map, std::string mesh, Type type);
		~AI();
		void update();
		std::unique_ptr<object::Player> getPlayer();
	private:
		bool move();
		void find_closest_player();
		std::array<int, 2> _closest_player;
		std::unique_ptr<object::Player> _player;
		map::Map *_map;
};

#endif //INDIESTUDIO_AI_HPP
