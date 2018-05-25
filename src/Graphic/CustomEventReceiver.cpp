//
// Created by jdecombe on 09/05/18.
//

#include "CustomEventReceiver.hpp"

CustomEventReceiver::CustomEventReceiver()
{
	for (bool &i : this->_keyIsDown)
		i = false;
}

CustomEventReceiver::~CustomEventReceiver()
{
}

bool CustomEventReceiver::OnEvent(const SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		this->_keyIsDown[event.KeyInput.Key]
			= event.KeyInput.PressedDown;
	return false;
}

bool CustomEventReceiver::isKeyDown(EKEY_CODE keyCode) const
{
	return this->_keyIsDown[keyCode];
}
