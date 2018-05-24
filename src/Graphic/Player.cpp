//
// Created by jdecombe on 14/05/18.
//

#include <cmath>
#include <cstddef>
#include <string>
#include "CustomEventReceiver.hpp"
#include "Gfx.hpp"
#include <iostream>
#include <future>
#include "Player.hpp"

/*
 * Construction/Destructions
 */

static std::unordered_map<playerSprite_e, playerSpriteInfo_t> playersPossibilities =
{
	{POMMY, {"./media/models/pommy/pommyV3.obj", {2.f, 2.f, 2.f}} },
	{UNKNOWN, {"", {0, 0, 0}} }

};


Player::Player(Gfx *gfx, playerSprite_e playerType, float x, float y, float z,
		bool useController, unsigned long playerNb
	) : _gfx(gfx), _useController(useController), _playerNb(playerNb)
{

	auto modelInfo = playersPossibilities[playerType];
	this->_playerNode = this->_gfx->drawMesh(modelInfo.path, "", false,
		"Player" + this->_playerNb, {x, y, z});
	this->_playerNode->setScale(modelInfo.scale);
	this->_rotateStop = false;
	this->_movementStop = false;
}

Player::~Player()
{
	if (_movementThread.joinable())
		_movementThread.join();
	if (_rotationThread.joinable())
		_rotationThread.join();
	this->_gfx->deleteElement("Player" + this->_playerNb);
}

/*
 * Rotations
 */

// TODO : REMOVE DEBUG

void Player::rotateThreadHandler(float maxAngle, float curAngle,
	std::string name)
{

	curAngle = static_cast<float>(fmod(curAngle, 360));
	auto step = (maxAngle - curAngle) / abs(maxAngle - curAngle);


	while ((step > 0 && curAngle < maxAngle) ||
		(step < 0 && curAngle > maxAngle)) {
		if (_gfx->isKeyDown(KEY_KEY_L)) {
			std::cout << "-----------------" << std::endl;
			std::cout << "Angle\t\t: " << curAngle << std::endl;
			std::cout << "MaxAngle\t: " << maxAngle << std::endl;
			std::cout << "Step\t\t: " << step << std::endl;
		}
		if (_rotateStop) {
			_rotateStop = false;
			return;
		}
		curAngle += step;
		_gfx->rotateElement(name, {0, curAngle, 0});
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	_gfx->rotateElement(name, {0, maxAngle, 0});
}


void Player::setAbsoluteRotation(enum rotationDirection_e rotation)
{
	float angle = 0.f;

	switch (rotation) {
	case LEFT:
		angle = 90;
		break;
	case RIGHT:
		angle = -90;
		break;
	case FORWARD:
		angle = 0;
		break;
	case BACKWARD:
		angle = 180;
		break;
	default:
		break;
	}
	this->setAbsoluteRotation(angle);
}

void Player::setAbsoluteRotation(float maxAngle)
	{
		auto curAngle = this->_playerNode->getRotation().Y;
		auto name = std::string("Player") + std::to_string(_playerNb);

		if (_rotationThread.joinable()) {
			_rotateStop = true;
			_rotationThread.join();
		}
		_rotateStop = false;
		this->_rotationThread = std::thread(&Player::rotateThreadHandler, this,
			maxAngle, curAngle, "Player" + _playerNb);
	}

void Player::rotate(enum rotationDirection_e dir)
{
	auto dirAngle = (dir == LEFT) ? ROTATION_SPEED : -ROTATION_SPEED;
	auto angle = _playerNode->getRotation().Y + dirAngle;
	_gfx->rotateElement("Player" + this->_playerNb, {0, angle, 0});
}

/*
 * Movements
 */

void Player::moveForward(rotationDirection_e dir, float spd)
{
	if (dir == BACKWARD)
		spd *= -1;
	if (dir == LEFT || dir == RIGHT)
		return;
	auto rotation = this->_playerNode->getRotation();
	vector3df vector = {0, 0, 0};
	vector.X += spd * cos(rotation.Y * PI / 180);
	vector.Z -= spd * sin(rotation.Y * PI / 180);
	this->_gfx->moveElement("Player" + this->_playerNb, vector);
}

/*
 * Getters
 */

vector3df Player::getPosition()
{
	return this->_playerNode->getPosition();
}

IAnimatedMeshSceneNode *Player::getNode() const
{
	return _playerNode;
}
