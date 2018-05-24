//
// Created by jdecombe on 21/05/18.
//

#include "CollisionsHandler.hpp"

CollisionsHandler::CollisionsHandler(Gfx const &gfx)
{
	_sceneManager = gfx.getSceneManager();
	_metaTriangleSelector = _sceneManager->createMetaTriangleSelector();
}

CollisionsHandler::~CollisionsHandler()
{
	_metaTriangleSelector->drop();
}

void CollisionsHandler::addObjectToCollisions(Player const &player)
{
	this->addObjectToCollisions(player.getNode(), vector3df(1.f, 1.f, 1.f));
}

void CollisionsHandler::addObjectToCollisions(IAnimatedMeshSceneNode *node,
	vector3df const &size
)
{
	auto selector = this->_sceneManager->createTriangleSelector(node);
	_metaTriangleSelector->addTriangleSelector(selector);

	auto anim = _sceneManager->createCollisionResponseAnimator(
		_metaTriangleSelector, node, size, vector3df(0, 0, 0));
	node->addAnimator(anim);
	anim->drop();
	selector->drop();
}

void CollisionsHandler::addMapToCollision(Map const &map)
{
	auto selector = map.getSelector();
	_metaTriangleSelector->addTriangleSelector(selector);
}

