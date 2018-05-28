//
// Created by jdecombe on 08/05/18.
//

#include <iostream>
#include <algorithm>
#include "Gfx.hpp"
#include "CustomEventReceiver.hpp"

static void updateFpsCount(IrrlichtDevice *device, IVideoDriver *videoDriver)
{
	auto fps = videoDriver->getFPS();
	core::stringw str("Render ? [FPS: ");
	str += fps;
	str += "]";
	device->setWindowCaption(str.c_str());
}

Gfx::Gfx()
{
	this->_device = irr::createDevice(irr::video::EDT_OPENGL,
		dimension2d<u32>(WIN_WIDTH, WIN_HEIGHT), 32, false, false, true,
		nullptr);

	if (!this->_device)
		throw std::exception();

	this->_videoDriver = _device->getVideoDriver();
	this->_sceneManager = _device->getSceneManager();
	this->_guiEnv = _device->getGUIEnvironment();
	this->_device->getCursorControl()->setVisible(false);
	this->_eventReceiver = nullptr;
}

Gfx::Gfx(IEventReceiver &receiver)
{
	this->_device = irr::createDevice(irr::video::EDT_OPENGL,
		dimension2d<u32>(WIN_WIDTH, WIN_HEIGHT), 32, false, false, true,
		&receiver);

	if (!this->_device)
		throw std::exception();

	this->_videoDriver = _device->getVideoDriver();
	this->_sceneManager = _device->getSceneManager();
	this->_guiEnv = _device->getGUIEnvironment();
	this->_device->getCursorControl()->setVisible(false);
	this->_eventReceiver = _device->getEventReceiver();
}

Gfx::~Gfx()
{
	_device->drop();
	_nodeCache.clear();
}

void Gfx::update()
{
	if (!_device->isWindowActive()) {
		_device->yield();
		return;
	}
	this->_videoDriver->beginScene(true, true, SColor(255, 100, 100, 140));
	updateFpsCount(_device, _videoDriver);

	this->_sceneManager->drawAll();
	this->_guiEnv->drawAll();

	this->_videoDriver->endScene();
}

bool Gfx::isRunning()
{
	return this->_device->run();
}

void Gfx::drawStaticText(stringw const &str, rect<s32> const &pos)
{
	_guiEnv->addStaticText(str.c_str(), pos);
}

IAnimatedMeshSceneNode *Gfx::drawMesh(std::string const &path, std::string const &material,
	bool lighting, const std::string &name, const vector3df &pos,
	const vector3df &scale
)
{
	auto mesh = _sceneManager->getMesh(path.c_str());
	if (!mesh)
		throw std::exception();

	auto node = _sceneManager->addAnimatedMeshSceneNode(mesh);
	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, lighting);
		node->setMD2Animation(scene::EMAT_RUN);
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
	this->_sceneManager->addCameraSceneNode(0, {30, 50, 0}, {0, 0, 0});
}

void Gfx::setEventReceiver(IEventReceiver &receiver)
{
	this->_device->setEventReceiver(&receiver);
}

bool Gfx::isKeyDown(EKEY_CODE keyCode) const
{
	if (this->_eventReceiver == nullptr)
		throw std::exception();
	auto eventReceiver = dynamic_cast<CustomEventReceiver *>(
		this->_eventReceiver);
	if (eventReceiver == nullptr)
		throw std::exception();
	return eventReceiver->isKeyDown(keyCode);
}

void Gfx::moveElement(std::string const &name, vector3df const &vec, float speed
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

void Gfx::rotateElement(std::string const &name, vector3df const &vec)
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

void Gfx::addLight(vector3df const &pos, SColorf const &color, float radius)
{
	auto light = this->_sceneManager->addLightSceneNode(nullptr, pos, color,
		radius);
}

ISceneManager *Gfx::getSceneManager() const
{
	return _sceneManager;
}
