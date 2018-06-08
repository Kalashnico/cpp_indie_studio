//
// Created by Nicolas Guerin on 08/06/2018.
//

#include <iostream>
#include "SoundManager.hpp"

SoundManager SoundManager::_instance = SoundManager();

SoundManager::SoundManager()
{
	if (!_soundsList[LOOT].openFromFile("media/sound/loot.ogg"))
		throw std::invalid_argument("Sound media couldn't be found");

	if (!_soundsList[BOMB].openFromFile("media/sound/bomb.ogg"))
		throw std::invalid_argument("Sound media couldn't be found");
	if (!_soundsList[BACKGROUND].openFromFile("media/sound/background.ogg"))
		throw std::invalid_argument("Sound media couldn't be found");
	if (!_soundsList[CLICK].openFromFile("media/sound/loot.ogg"))
		throw std::invalid_argument("Sound media couldn't be found");
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

void SoundManager::playBackground() noexcept
{
	_soundsList[BACKGROUND].play();
}

void SoundManager::playClick() noexcept
{
	_soundsList[CLICK].play();
}