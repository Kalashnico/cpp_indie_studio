//
// Created by jdecombe on 09/05/18.
//

#include <iostream>
#include "CustomEventReceiver.hpp"

CustomEventReceiver::CustomEventReceiver()
{
	for (auto &value : _keyIsDown)
		value = false;
}

CustomEventReceiver::~CustomEventReceiver()
{
}

bool CustomEventReceiver::OnEvent(const SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		_keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

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
	return _keyIsDown[keyCode];
}

f32 CustomEventReceiver::getXJoystickStatus(int joystick) const noexcept
{
	f32 value = (f32)_joystickStates[joystick].Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;

	if (fabs(value) < (f32)DEAD_ZONE)
		value = 0.f;
	return value;
}

f32 CustomEventReceiver::getYJoystickStatus(int joystick) const noexcept
{
	f32 value = (f32)_joystickStates[joystick].Axis[SEvent::SJoystickEvent::AXIS_Y] / 32767.f;

	if (fabs(value) < (f32)DEAD_ZONE)
		value = 0.f;
	return value;
}

bool CustomEventReceiver::isGamepadButtonDown(int joystick, GamepadButtons button) const noexcept
{
	return _joystickStates[joystick].IsButtonPressed(button);
}
