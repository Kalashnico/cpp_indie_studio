//
// Created by jdecombe on 22/05/18.
//

#include "Map.hpp"

#include <exception>

Map::Map(ISceneManager *sceneManager) : _sceneManager(sceneManager)
{
	auto mesh = _sceneManager->getMesh("./media/map/map_indie.obj");
	if (!mesh)
		throw std::exception();
	_mapNode = _sceneManager->addOctreeSceneNode(mesh->getMesh(0), nullptr,
		0);
	_mapNode->setScale(vector3df(2, 2, 2));
	if (!_mapNode)
		throw std::exception();
	_selector = _sceneManager->createOctreeTriangleSelector(
		_mapNode->getMesh(), _mapNode, 128);
}

Map::~Map() = default;

ITriangleSelector *Map::getSelector() const
{
	return _selector;
}

IMeshSceneNode *Map::getMapNode() const
{
	return _mapNode;
}
