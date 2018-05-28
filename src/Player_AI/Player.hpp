/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Created by tclemenceau,
*/

#ifndef INDIESTUDIO_PLAYER_HPP
#define INDIESTUDIO_PLAYER_HPP

#include "AObject.hpp"

namespace object {
	class Player : public AObject {
		public:
			Player(std::string path, Type type);
			~Player();

		private:
	};
}

#endif //INDIESTUDIO_PLAYER_HPP
