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
		AI(::map::Map *map, std::string mesh, Type type, Gfx *gfx, playerSprite_e playerType, float x,
			float y, float z, bool useController,
			unsigned long playerNb);
		~AI();
		void update();
		object::Player &getPlayer();
	private:
		void moveCase(rotationDirection_e dir, float spd = MOVEMENT_SPEED);
		void find_closest_player();
		std::array<int, 2> _closest_player;
		object::Player _player;
		::map::Map *_map;
		rotationDirection_e _to_go;
		vector2di _past_co;
};

#endif //INDIESTUDIO_AI_HPP
