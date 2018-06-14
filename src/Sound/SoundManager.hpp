//
// Created by Nicolas Guerin on 08/06/2018.
//

#pragma once

#include <map>
#include <string>
#include <SFML/Audio.hpp>

enum soundType {
	BACKGROUND,
	MENU,
	CLICK,
	BOMB,
	LOOT,
};


class SoundManager {
	public:
		static SoundManager &getInstance() noexcept { static SoundManager _instance; return _instance; };

		SoundManager(const SoundManager&) = delete;
		void operator=(const SoundManager&) = delete;

		void playBomb() noexcept;
		void playLoot() noexcept;
		void playBackground() noexcept;
		void playClick() noexcept;

	private:
		SoundManager();
		~SoundManager();

		std::map<soundType, sf::Music>	_soundsList;
};