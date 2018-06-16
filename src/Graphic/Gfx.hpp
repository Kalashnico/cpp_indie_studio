//
// Created by jdecombe on 08/05/18.
//

#pragma once

#include <string>
#include <unordered_map>
#include "Irrlicht/irrlicht.h"

#define WIN_WIDTH	1920
#define WIN_HEIGHT	1080

enum GamepadButtons {
	GAMEPAD_A = 0,
	GAMEPAD_START =  7
};

class Gfx {
	private:
		irr::IrrlichtDevice *_device;
		irr::video::IVideoDriver *_videoDriver;
		irr::gui::IGUIEnvironment *_guiEnv;
		irr::scene::ISceneManager *_sceneManager;
		irr::IEventReceiver *_eventReceiver;
		std::unordered_map<std::string, irr::scene::ISceneNode *> _nodeCache;

		bool _gamepadActive;

		irr::EKEY_CODE translateButton(GamepadButtons button) const noexcept;

		void setupGamepads() noexcept;

	public:
		Gfx();

		explicit Gfx(irr::IEventReceiver &receiver);

		virtual ~Gfx();

		void update();

		bool isRunning();

		void drawStaticText(irr::core::stringw const &str, irr::core::rect<irr::s32> const &pos);

		irr::scene::ISceneManager *getSceneManager() const;

		irr::video::IVideoDriver *getDriver() const noexcept { return _videoDriver; }
		irr::IrrlichtDevice *getDevice() const noexcept { return _device; }

		irr::scene::IAnimatedMeshSceneNode *drawMesh(std::string const &path,
			std::string const &material, bool lighting,
			const std::string &name,
			const irr::core::vector3df &pos = {0.0f, 0.0f, 0.0f},
			const irr::core::vector3df &scale = {1.0f, 1.0f, 1.0f}
		);

		void addCameraFPS();

		void setEventReceiver(irr::IEventReceiver &receiver);

		bool isGuiButtonPressed(int buttonId) noexcept;

		bool isKeyDown(irr::EKEY_CODE keyCode) const noexcept;

		irr::f32 getXJoystickStatus(int playerNb) const noexcept;

		irr::f32 getYJoystickStatus(int playerNb) const noexcept;

		bool isGamepadButtonDown(int playerNb, GamepadButtons button) const noexcept;

		bool isGamepadActive() const noexcept { return _gamepadActive; }

		void moveElement(std::string const &name, irr::core::vector3df const &vec,
			float speed = 100.0
		);

		void rotateElement(std::string const &name, irr::core::vector3df const &vec
		);

		void deleteElement(std::string const &name);

		void addLight(irr::core::vector3df const &pos, irr::video::SColorf const &color,
			float radius = 1000.0f
		);


};
