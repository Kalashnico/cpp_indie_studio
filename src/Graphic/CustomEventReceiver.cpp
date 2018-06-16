//
// Created by jdecombe on 09/05/18.
//

#include <iostream>
#include "Core.hpp"
#include "CustomEventReceiver.hpp"

CustomEventReceiver::CustomEventReceiver()
{
	for (auto &value : _keyIsDown)
		value = false;

	for (auto &value : _isGuiButtonClicked)
		value = false;
}

CustomEventReceiver::~CustomEventReceiver()
{
}

bool CustomEventReceiver::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		_keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		return true;
	}

	if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT) {
		if (event.JoystickEvent.Joystick == 0)
			_joystickStates[0] = event.JoystickEvent;
		else if (event.JoystickEvent.Joystick == 1)
			_joystickStates[1] = event.JoystickEvent;
		else if (event.JoystickEvent.Joystick == 2)
			_joystickStates[2] = event.JoystickEvent;
		else if (event.JoystickEvent.Joystick == 3)
			_joystickStates[3] = event.JoystickEvent;
		return true;
	}

	if (event.EventType == irr::EET_GUI_EVENT) {
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
			irr::s32 id = event.GUIEvent.Caller->getID();
			switch (id) {
				case core::PLAY_BUTTON:
					_isGuiButtonClicked[id - core::PLAY_BUTTON] = true;
					return true;
				case core::QUIT_BUTTON:
					_isGuiButtonClicked[id - core::PLAY_BUTTON] = true;
					return true;
				case core::ADD_PLAYER_BUTTON:
					_isGuiButtonClicked[id - core::PLAY_BUTTON] = true;
					return true;
				case core::REMOVE_PLAYER_BUTTON:
					_isGuiButtonClicked[id - core::PLAY_BUTTON] = true;
					return true;
				default:
					break;
			}
		}
	}

	return false;
}

bool CustomEventReceiver::isGuiButtonPressed(int buttonId) noexcept
{
	bool value = _isGuiButtonClicked[buttonId];
	if (value)
		_isGuiButtonClicked[buttonId] = false;
	return value;
}

bool CustomEventReceiver::isKeyDown(irr::EKEY_CODE keyCode) const noexcept
{
	return _keyIsDown[keyCode];
}

irr::f32 CustomEventReceiver::getXJoystickStatus(int joystick) const noexcept
{
	irr::f32 value = (irr::f32)_joystickStates[joystick].Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f;

	if (fabs(value) < (irr::f32)DEAD_ZONE)
		value = 0.f;
	return value;
}

irr::f32 CustomEventReceiver::getYJoystickStatus(int joystick) const noexcept
{
	irr::f32 value = (irr::f32)_joystickStates[joystick].Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / 32767.f;

	if (fabs(value) < (irr::f32)DEAD_ZONE)
		value = 0.f;
	return value;
}

bool CustomEventReceiver::isGamepadButtonDown(int joystick, GamepadButtons button) const noexcept
{
	return _joystickStates[joystick].IsButtonPressed(button);
}
