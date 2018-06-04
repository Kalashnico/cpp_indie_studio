//
// Created by jdecombe on 09/05/18.
//

#include <iostream>
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

	if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT) {
		if (event.JoystickEvent.Joystick == 0)
			_joystickStates[0] = event.JoystickEvent;
		else if (event.JoystickEvent.Joystick == 1)
			_joystickStates[1] = event.JoystickEvent;
		else if (event.JoystickEvent.Joystick == 2)
			_joystickStates[2] = event.JoystickEvent;
		else if (event.JoystickEvent.Joystick == 3)
			_joystickStates[3] = event.JoystickEvent;
	}
	return false;
}

bool CustomEventReceiver::isKeyDown(EKEY_CODE keyCode) const noexcept
{
	return this->_keyIsDown[keyCode];
}

bool CustomEventReceiver::isGamepadButtonDown(int joystick, GamepadButtons button) const noexcept
{
	return _joystickStates[joystick].IsButtonPressed(button);
}
