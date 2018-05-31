//
// Created by gnicolas on 31/05/18.
//

#pragma once

#include "Irrlicht/irrlicht.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

void setSkinTransparency(s32 alpha, irr::gui::IGUISkin * skin)
{
    for (s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
    {
        video::SColor col = skin->getColor((EGUI_DEFAULT_COLOR)i);
        col.setAlpha(alpha);
        skin->setColor((EGUI_DEFAULT_COLOR)i, col);
    }
}

class MenuEventReceiver : public IEventReceiver
    {
    public:
        explicit MenuEventReceiver(SAppContext & context);
        ~MenuEventReceiver() = default;

        virtual bool OnEvent(const SEvent& event);

    private:
        SAppContext &Context;
};