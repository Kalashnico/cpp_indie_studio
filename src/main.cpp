//
// Created by gnicolas on 31/05/18.
//

#include <Irrlicht/irrlicht.h>
#include <Irrlicht/driverChoice.h>
#include "Menu/MenuEventReceiver.hpp"

int main(void)
{
    IrrlichtDevice * device = createDevice(E_DRIVER_TYPE::EDT_OPENGL, core::dimension2d<u32>(1280, 720));

    if (device == nullptr)
        return 1; // could not create selected driver.
    device->setWindowCaption(L"BomberMan");
    device->setResizable(false);

    video::IVideoDriver* driver = device->getVideoDriver();
    IGUIEnvironment* env = device->getGUIEnvironment();
    IGUISkin* skin = env->getSkin();
    IGUIFont* font = env->getFont("../../media/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);

    skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

    env->addButton(rect<s32>(10,240,110,240 + 32), 0, QUIT_BUTTON,
                   L"Quit", L"Exits Program");
    env->addButton(rect<s32>(10,280,110,280 + 32), 0, OPTION_BUTTON,
                   L"New Window", L"Launches a new Window");
    env->addButton(rect<s32>(10,320,110,320 + 32), 0, FILE_OPEN_BUTTON,
                   L"File Open", L"Opens a file");

    env->addStaticText(L"Transparent Control:", rect<s32>(150,20,350,40), true);
    IGUIScrollBar* scrollbar = env->addScrollBar(true,
                                                 rect<s32>(150, 45, 350, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
    scrollbar->setMax(255);
    scrollbar->setPos(255);
    setSkinTransparency( scrollbar->getPos(), env->getSkin());

    // set scrollbar position to alpha value of an arbitrary element
    scrollbar->setPos(env->getSkin()->getColor(EGDC_WINDOW).getAlpha());

    env->addStaticText(L"Logging ListBox:", rect<s32>(50,110,250,130), true);
    IGUIListBox * listbox = env->addListBox(rect<s32>(50, 140, 250, 210));
    env->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));

    // Store the appropriate data in a context structure.
    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.listbox = listbox;

    // Then create the event receiver, giving it that context structure.
    MenuEventReceiver receiver(context);

    // And tell the device to use our custom event receiver.
    device->setEventReceiver(&receiver);

    env->addImage(driver->getTexture("../../media/irrlichtlogo2.png"),
                  position2d<int>(10,10));

    while(device->run() && driver)
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, SColor(0,200,200,200));

            env->drawAll();

            driver->endScene();
        }

    device->drop();

    return 0;
}