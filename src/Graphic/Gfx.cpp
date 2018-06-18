//
// Created by jdecombe on 08/05/18.
//

#include <iostream>
#include <algorithm>
#include "Gfx.hpp"
#include "CustomEventReceiver.hpp"

static void updateFpsCount(irr::IrrlichtDevice *device, irr::video::IVideoDriver *videoDriver)
{
	auto fps = videoDriver->getFPS();
	irr::core::stringw str("Bomberman [FPS: ");
	str += fps;
	str += "]";
	device->setWindowCaption(str.c_str());
}

Gfx::Gfx()
	: _gamepadActive(false)
{
	this->_device = irr::createDevice(irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(WIN_WIDTH, WIN_HEIGHT), 32, false, false, true,
		nullptr);

	if (!this->_device)
		throw std::exception();

	this->_videoDriver = _device->getVideoDriver();
	_background = _videoDriver->getTexture ("./media/background/background.png");
	this->_sceneManager = _device->getSceneManager();
	this->_guiEnv = _device->getGUIEnvironment();
	this->_eventReceiver = nullptr;
}

Gfx::Gfx(irr::IEventReceiver &receiver)
	: _gamepadActive(false)
{
	this->_device = irr::createDevice(irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(WIN_WIDTH, WIN_HEIGHT), 32, false, false, true,
		&receiver);

	if (!this->_device)
		throw std::exception();

	this->_videoDriver = _device->getVideoDriver();
	this->_sceneManager = _device->getSceneManager();
	this->_guiEnv = _device->getGUIEnvironment();
	this->_eventReceiver = _device->getEventReceiver();

	setupGamepads();
}

Gfx::~Gfx()
{
	_device->drop();
	_nodeCache.clear();
}

void Gfx::setupGamepads() noexcept
{
	irr::core::array<irr::SJoystickInfo> joystickInfo;
	if(_device->activateJoysticks(joystickInfo)) {

		std::cout << "Joystick support is enabled and " << joystickInfo.size() << " joystick(s) are present." << std::endl;

		if (joystickInfo.size() > 0)
			_gamepadActive = true;

		for(irr::u32 joystick = 0; joystick < joystickInfo.size(); ++joystick) {
			std::cout << "Joystick " << joystick << ":" << std::endl;
			std::cout << "\tName: '" << joystickInfo[joystick].Name.c_str() << "'" << std::endl;
			std::cout << "\tAxes: " << joystickInfo[joystick].Axes << std::endl;
			std::cout << "\tButtons: " << joystickInfo[joystick].Buttons << std::endl;

			std::cout << "\tHat is: ";

			switch(joystickInfo[joystick].PovHat) {
				case irr::SJoystickInfo::POV_HAT_PRESENT:
					std::cout << "present" << std::endl;
					break;

				case irr::SJoystickInfo::POV_HAT_ABSENT:
					std::cout << "absent" << std::endl;
					break;

				case irr::SJoystickInfo::POV_HAT_UNKNOWN:
				default:
					std::cout << "unknown" << std::endl;
					break;
			}
		}
	} else
		std::cout << "Joystick support is not enabled." << std::endl;
}

void Gfx::update()
{
	if (!_device->isWindowActive()) {
		_device->yield();
		return;
	}
	this->_videoDriver->beginScene(true, true, irr::video::SColor(255, 100, 100, 140));
	updateFpsCount(_device, _videoDriver);
	_videoDriver->draw2DImage(_background,
		irr::core::position2d<irr::s32>(0,0),
		irr::core::rect<irr::s32>(0,0,1920,1080		),
		0,
		irr::video::SColor (255,255,255,255),
		true);
	this->_sceneManager->drawAll();
	this->_guiEnv->drawAll();

	this->_videoDriver->endScene();
}

bool Gfx::isRunning()
{
	return this->_device->run();
}

void Gfx::drawStaticText(irr::core::stringw const &str, irr::core::rect<irr::s32> const &pos)
{
	_guiEnv->addStaticText(str.c_str(), pos);
}

irr::scene::IAnimatedMeshSceneNode *Gfx::drawMesh(std::string const &path, std::string const &material,
	bool lighting, const std::string &name, const irr::core::vector3df &pos,
	const irr::core::vector3df &scale
)
{
	auto mesh = _sceneManager->getMesh(path.c_str());
	if (!mesh)
		throw std::exception();

	auto node = _sceneManager->addAnimatedMeshSceneNode(mesh);
	if (node) {
		node->setMaterialFlag(irr::video::EMF_LIGHTING, lighting);
		node->setMD2Animation(irr::scene::EMAT_RUN);
		node->setScale(scale);
		if (material != "")
			node->setMaterialTexture(0,
				_videoDriver->getTexture(material.c_str()));
		node->setPosition(pos);
		node->setName(name.c_str());
		this->_nodeCache[name] = node;
	}
	return node;
}

void Gfx::addCameraFPS()
{
	this->_sceneManager->addCameraSceneNode(0, {20, 50, 0}, {0, 0, 0});
}

void Gfx::setEventReceiver(irr::IEventReceiver &receiver)
{
	this->_device->setEventReceiver(&receiver);
	_eventReceiver = _device->getEventReceiver();
	setupGamepads();
}

bool Gfx::isGuiButtonPressed(int buttonId) noexcept
{
	buttonId -= 101;
	if (buttonId < 0)
		return false;

	auto eventReceiver = dynamic_cast<CustomEventReceiver *>(
		this->_eventReceiver);
	return eventReceiver->isGuiButtonPressed(buttonId);

}

bool Gfx::isKeyDown(irr::EKEY_CODE keyCode) const noexcept
{
	if (keyCode == -1)
		return false;

	auto eventReceiver = dynamic_cast<CustomEventReceiver *>(
		this->_eventReceiver);
	return eventReceiver->isKeyDown(keyCode);
}

irr::f32 Gfx::getXJoystickStatus(int playerNb) const noexcept
{
	if (this->_eventReceiver == nullptr)
		return (irr::f32)0;
	auto eventReceiver = dynamic_cast<CustomEventReceiver *>(
		this->_eventReceiver);
	if (eventReceiver == nullptr)
		return (irr::f32)0;

	if (_gamepadActive)
		return eventReceiver->getXJoystickStatus(playerNb - 1);

	if (eventReceiver->isKeyDown(irr::KEY_LEFT))
		return (irr::f32)-1.f;
	else if (eventReceiver->isKeyDown(irr::KEY_RIGHT))
		return (irr::f32)1.f;

	return (irr::f32)0;
}

irr::f32 Gfx::getYJoystickStatus(int playerNb) const noexcept
{
	if (this->_eventReceiver == nullptr)
		return (irr::f32)0;
	auto eventReceiver = dynamic_cast<CustomEventReceiver *>(
		this->_eventReceiver);
	if (eventReceiver == nullptr)
		return (irr::f32)0;

	if (_gamepadActive)
		return eventReceiver->getYJoystickStatus(playerNb - 1);

	if (eventReceiver->isKeyDown(irr::KEY_UP))
		return (irr::f32)-1.f;
	else if (eventReceiver->isKeyDown(irr::KEY_DOWN))
		return (irr::f32)1.f;

	return (irr::f32)0;
}

bool Gfx::isGamepadButtonDown(int playerNb, GamepadButtons button) const noexcept
{
	if (this->_eventReceiver == nullptr)
		return false;
	auto eventReceiver = dynamic_cast<CustomEventReceiver *>(
		this->_eventReceiver);
	if (eventReceiver == nullptr)
		return false;

	if (_gamepadActive)
		return eventReceiver->isGamepadButtonDown(playerNb - 1, button);
	return isKeyDown(translateButton(button));
}

irr::EKEY_CODE Gfx::translateButton(GamepadButtons button) const noexcept
{
	switch (button) {
		case GAMEPAD_A:
			return irr::KEY_SPACE;
		case GAMEPAD_START:
			return irr::KEY_KEY_P;
	}

	return (irr::EKEY_CODE)-1;
}

void Gfx::moveElement(std::string const &name, irr::core::vector3df const &vec, float speed
)
{
	auto node = this->_nodeCache[name];
	if (!node)
		node = this->_sceneManager->getSceneNodeFromName(name.c_str(),
			this->_sceneManager->getRootSceneNode());
	if (!node)
		throw std::exception();
	auto nodePosition = node->getPosition();
	nodePosition += vec * speed / 100;
	node->setPosition(nodePosition);
	this->_nodeCache[name] = node;
}

void Gfx::deleteElement(const std::string &name)
{
	auto node = this->_nodeCache[name];

	if (node)
		node->setVisible(false);
}

void Gfx::rotateElement(std::string const &name, irr::core::vector3df const &vec)
{
	auto node = this->_nodeCache[name];

	if (!node) {
		node = this->_sceneManager->getSceneNodeFromName(name.c_str(),
			this->_sceneManager->getRootSceneNode());
		this->_nodeCache[name] = node;
	}
	if (!node)
		throw std::exception();
	node->setRotation(vec);
}

void Gfx::addLight(irr::core::vector3df const &pos, irr::video::SColorf const &color, float radius)
{
	auto light = this->_sceneManager->addLightSceneNode(nullptr, pos, color,
		radius);
}

irr::scene::ISceneManager *Gfx::getSceneManager() const
{
	return _sceneManager;
}

