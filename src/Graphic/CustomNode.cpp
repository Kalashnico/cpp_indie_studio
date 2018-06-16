//
// Created by jdecombe on 08/05/18.
//

#include <iostream>
#include "CustomNode.hpp"

CustomNode::CustomNode(ISceneNode *parent, irr::scene::ISceneManager *mgr, irr::s32 id)
	: ISceneNode(parent, mgr, id)
{
	this->_material.Wireframe = false;
	this->_material.Lighting = false;

	this->_vertices[0] = irr::video::S3DVertex(0, 0, 10, 0, 0, 0,
		irr::video::SColor(255, 0, 255, 255), 0, 0);
	this->_vertices[1] = irr::video::S3DVertex(10, 0, -10, 0, 0, 0,
		irr::video::SColor(255, 255, 0, 255), 0, 0);
	this->_vertices[2] = irr::video::S3DVertex(0, 20, 0, 0, 0, 0,
		irr::video::SColor(255, 255, 255, 0), 0, 0);
	this->_vertices[3] = irr::video::S3DVertex(-10, 0, -10, 0, 0, 0,
		irr::video::SColor(255, 0, 255, 0), 0, 0);

	this->_box.reset(this->_vertices[0].Pos);
	for (auto i = 1; i < 4; i++)
		this->_box.addInternalPoint(this->_vertices[i].Pos);
}

CustomNode::CustomNode(ISceneNode *parent, irr::scene::ISceneManager *mgr, irr::s32 id,
	const irr::core::vector3df &position, const irr::core::vector3df &rotation,
	const irr::core::vector3df &scale
) : ISceneNode(parent, mgr, id, position, rotation, scale)
{
	this->_material.Wireframe = false;
	this->_material.Lighting = false;

	this->_vertices[0] = irr::video::S3DVertex(0, 0, 10, 0, 0, 0,
		irr::video::SColor(255, 0, 255, 255), 0, 1);
	this->_vertices[1] = irr::video::S3DVertex(10, 0, -10, 0, 0, 0,
		irr::video::SColor(255, 255, 0, 255), 1, 1);
	this->_vertices[2] = irr::video::S3DVertex(0, 20, 0, 0, 0, 0,
		irr::video::SColor(255, 255, 255, 0), 1, 0);
	this->_vertices[3] = irr::video::S3DVertex(-10, 0, -10, 0, 0, 0,
		irr::video::SColor(255, 0, 255, 0), 0, 0);

	this->_box.reset(this->_vertices[0].Pos);
	for (auto i = 1; i < 4; i++)
		this->_box.addInternalPoint(this->_vertices[i].Pos);
}

void CustomNode::OnRegisterSceneNode()
{
	if (this->IsVisible)
		this->SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void CustomNode::render()
{
	irr::u16 indices[] = {0, 2, 3, 2, 1, 3, 1, 0, 3, 2, 0, 1};
	auto driver = this->SceneManager->getVideoDriver();

	driver->setMaterial(this->_material);
	driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);
	driver->drawVertexPrimitiveList(&this->_vertices[0], 4, &indices[0], 4,
		irr::video::EVT_STANDARD, irr::scene::EPT_TRIANGLES, irr::video::EIT_16BIT);
}

const irr::core::aabbox3d<irr::f32> &CustomNode::getBoundingBox() const
{
	return this->_box;
}

irr::u32 CustomNode::getMaterialCount() const
{
	return 1;
}

irr::video::SMaterial &CustomNode::getMaterial(irr::u32 num)
{
	return this->_material;
}
