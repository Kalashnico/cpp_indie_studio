//
// Created by Nicolas Guerin on 08/06/2018.
//

#include <iostream>
#include "SoundManager.hpp"

namespace sound {

SoundManager::SoundManager()
{
	if (!_soundsList[DEATH].openFromFile("media/sound/death.ogg"))
		throw std::invalid_argument("Sound media couldn't be found");

	if (!_soundsList[LOOT].openFromFile("media/sound/loot.ogg"))
		throw std::invalid_argument("Sound media couldn't be found");

	if (!_soundsList[BOMB].openFromFile("media/sound/bomb.ogg"))
		throw std::invalid_argument("Sound media couldn't be found");

	if (!_soundsList[BACKGROUND].openFromFile("media/sound/background.ogg"))
		throw std::invalid_argument("Sound media couldn't be found");

	if (!_soundsList[CLICK].openFromFile("media/sound/loot.ogg"))
		throw std::invalid_argument("Sound media couldn't be found");

	_soundsList[BOMB].setVolume(20);
	_soundsList[LOOT].setVolume(70);
	_soundsList[DEATH].setVolume(50);
}

SoundManager::~SoundManager()
{
}

void SoundManager::playBomb() noexcept
{
	_soundsList[BOMB].play();
}

void SoundManager::playLoot() noexcept
{
	_soundsList[LOOT].play();
}

void SoundManager::playDeath() noexcept
{
	_soundsList[DEATH].play();
}

void SoundManager::playBackground() noexcept
{
	_soundsList[BACKGROUND].setLoop(true);
	_soundsList[BACKGROUND].play();
}

void SoundManager::playClick() noexcept
{
	_soundsList[CLICK].play();
}

}
