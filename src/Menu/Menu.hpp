//
// Created by Nicolas Guerin on 31/05/2018.
//

#pragma once

#include <Irrlicht/irrlicht.h>
#include <Irrlicht/driverChoice.h>

enum	boutton
{
	QUIT,
	OPTION,
	FILE_OPEN,
	PLAY,
	GUI_ID_TRANSPARENCY_SCROLL_BAR
};

class Menu {
	public:
		Menu();
		~Menu() = default;

		void run();

	private:
		IrrlichtDevice *_device;
		video::IVideoDriver *_driver;
		IGUIEnvironment* _env;
		IGUISkin* _skin;
		IGUIFont* _font;
		MenuEventReceiver _receiver;

};