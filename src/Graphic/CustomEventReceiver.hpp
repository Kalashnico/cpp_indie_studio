//
// Created by jdecombe on 09/05/18.
//

#pragma once

#include "Irrlicht/irrlicht.h"
#include "Gfx.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CustomEventReceiver : public IEventReceiver {
	private:
		bool _keyIsDown[KEY_KEY_CODES_COUNT];
		SEvent::SJoystickEvent _joystickStates[4];

	public:
		CustomEventReceiver();
		virtual ~CustomEventReceiver();
		bool OnEvent(const SEvent &event) override;
		bool isKeyDown(EKEY_CODE keyCode) const noexcept;
		bool isGamepadButtonDown(int joystick, GamepadButtons button) const noexcept;
};
