/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Created by tclemenceau,
*/

#ifndef INDIESTUDIO_IA_HPP
#define INDIESTUDIO_IA_HPP

#include <bits/unique_ptr.h>
#include "Map.hpp"
#include "Player.hpp"

class IA {
	public:
		IA();
		~IA();
		void update(std::vector );
		std::unique_ptr<Player> getPlayer();
	private:
		bool move();
		void find_closest_player();
		std::array<int, 2> _closest_player;
		std::unique_ptr<Player> _player;
		std::array<std::array<int, 15>, 15> *_map;
};

#endif //INDIESTUDIO_IA_HPP
