/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Created by tclemenceau,
*/

#ifndef INDIESTUDIO_AI_HPP
#define INDIESTUDIO_AI_HPP

#include <random>
#include "Map.hpp"
#include "Player.hpp"

namespace object {

class AI : public AObject {
	public:
		AI(::map::Map *map, Type type, Gfx *gfx, playerSprite_e playerType, float x,
			float y, float z, bool useController,
			unsigned long playerNb);
		~AI();
		void update() noexcept;
		void updatePosition(size_t oldx, size_t oldy) noexcept;
		object::Player &getPlayer();
		vector2di getPosition() noexcept { return _player.getPosition(); }
	private:
		void moveCase(rotationDirection_e dir, float spd = MOVEMENT_SPEED);
		void find_closest_player();
		void set_direction();
		bool move_X(vector2di tmp, bool invert);
		bool move_Y(vector2di tmp, bool invert);
		vector2di _closest_player;
		object::Player _player;
		::map::Map *_map;
		rotationDirection_e _to_go;
		vector2df _co_to_go;
		std::random_device _random;
};

}

#endif //INDIESTUDIO_AI_HPP
