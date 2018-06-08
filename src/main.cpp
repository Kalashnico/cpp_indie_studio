//
// Created by gnicolas on 31/05/18.
//

#include "Sound/SoundManager.hpp"

int main()
{
	SoundManager	&soundManager = SoundManager::getInstance();

	soundManager.playBackground();

	while(1);

	return 0;

}