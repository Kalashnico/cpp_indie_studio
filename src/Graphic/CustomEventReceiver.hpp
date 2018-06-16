//
// Created by jdecombe on 09/05/18.
//

#pragma once

#include "Irrlicht/irrlicht.h"
#include "Gfx.hpp"

#define DEAD_ZONE 0.70

class CustomEventReceiver : public irr::IEventReceiver {
	private:
		bool _keyIsDown[irr::KEY_KEY_CODES_COUNT];
		irr::SEvent::SJoystickEvent _joystickStates[4];
		bool _isGuiButtonClicked[4];

	public:
		CustomEventReceiver();
		virtual ~CustomEventReceiver();
		bool OnEvent(const irr::SEvent &event) override;
		bool isGuiButtonPressed(int buttonId) noexcept;
		bool isKeyDown(irr::EKEY_CODE keyCode) const noexcept;
		irr::f32 getXJoystickStatus(int joystick) const noexcept;
		irr::f32 getYJoystickStatus(int joystick) const noexcept;
		bool isGamepadButtonDown(int joystick, GamepadButtons button) const noexcept;
};
