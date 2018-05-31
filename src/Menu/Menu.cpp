//
// Created by Nicolas Guerin on 31/05/2018.
//

#include "Menu.hpp"


Menu::Menu() {
	_device = createDevice(E_DRIVER_TYPE::EDT_OPENGL, core::dimension2d<u32>(1280, 720));

	if (device == nullptr)
		throw std::exception("Canno't create device.");

	_device->setWindowCaption(L"Bomberman");
	_device->setResizable(false);

	_driver = device->getVideoDriver();
	_env = device->getGUIEnvironment();
	_skin = env->getSkin();
	//TODO LOAD A FONT IN ASSETS/
	_font = env->getFont("../../media/fonthaettenschweiler.bmp");

	if (font)
		_skin->setFont(font);

	_skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

	_env->addButton(rect<s32>(10,240,110,240 + 32), 0, boutton::QUIT, L"Quit", L"Exits Program");
	_env->addButton(rect<s32>(10,280,110,280 + 32), 0, boutton::OPTION, L"New Window", L"Launches a new Window");
	_env->addButton(rect<s32>(10,320,110,320 + 32), 0, boutton::FILE_OPEN, L"File Open", L"Opens a file");
	_env->addButton(rect<s32>(10,360,110,360 + 32), 0, boutton::PLAY, L"Play", L"Exits Program");

	_env->addStaticText(L"Volume control:", rect<s32>(150,20,350,40), true);
	IGUIScrollBar* scrollbar = env->addScrollBar(true, rect<s32>(150, 45, 350, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
	scrollbar->setMax(255);
	scrollbar->setPos(255);
	setSkinTransparency( scrollbar->getPos(), env->getSkin());

	// set scrollbar position to alpha value of an arbitrary element
	scrollbar->setPos(env->getSkin()->getColor(EGDC_WINDOW).getAlpha());

	_env->addStaticText(L"Logging ListBox:", rect<s32>(50,110,250,130), true);
	IGUIListBox * listbox = env->addListBox(rect<s32>(50, 140, 250, 210));
	_env->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));

	// Store the appropriate data in a context structure.
	SAppContext context;
	context.device = device;
	context.counter = 0;
	context.listbox = listbox;

	// Then create the event receiver, giving it that context structure.
	MenuEventReceiver receiver(context);

	_receiver = std::move(receiver);
	// And tell the device to use our custom event receiver.
	_device->setEventReceiver(&receiver);

	_env->addImage(driver->getTexture(""), position2d<int>(10,10));


};

void Menu::run() {
	while (_device->run() && driver) {
		if (_device->isWindowActive()) {
			_driver->beginScene(true, true, SColor(0, 200, 200, 200));
			_env->drawAll();
			_driver->endScene();
		}
	}
	_device->drop();
}