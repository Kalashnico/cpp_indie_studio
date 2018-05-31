//
// Created by gnicolas on 31/05/18.
//

#include "MenuEventReceiver.hpp"

MenuEventReceiver::MenuEventReceiver(SAppContext & context) : Context(context) 
{
}


bool MenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == EET_GUI_EVENT)
    {
        s32 id = event.GUIEvent.Caller->getID();
        IGUIEnvironment* env = Context.device->getGUIEnvironment();

        switch(event.GUIEvent.EventType)
        {
            case EGET_SCROLL_BAR_CHANGED:
                if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
                {
                    s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                    setSkinTransparency(pos, env->getSkin());
                }
                break;
            case EGET_BUTTON_CLICKED:
                switch(id)
                {
                    case QUIT_BUTTON:
                        Context.device->closeDevice();
                        return true;

                    case OPTION_BUTTON:
                    {
                        Context.listbox->addItem(L"Window created");
                        Context.counter += 30;
                        if (Context.counter > 200)
                            Context.counter = 0;

                        IGUIWindow* window = env->addWindow(
                                rect<s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter, 200 + Context.counter),
                                false, // modal?
                                L"Test window");

                        env->addStaticText(L"Please close me",
                                           rect<s32>(35,35,140,50),
                                           true, // border?
                                           false, // wordwrap?
                                           window);
                    }
                        return true;

                    case FILE_OPEN_BUTTON:
                        Context.listbox->addItem(L"File open");
                        env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
                        return true;

                    default:
                        return false;
                }
                break;

            case EGET_FILE_SELECTED:
            {
                IGUIFileOpenDialog* dialog = (IGUIFileOpenDialog*)event.GUIEvent.Caller;
                Context.listbox->addItem(dialog->getFileName());
            }
                break;

            default:
                break;
        }
    }

    return false;
}