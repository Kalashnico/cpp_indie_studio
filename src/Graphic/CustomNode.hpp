//
// Created by jdecombe on 08/05/18.
//

#ifndef IRRLICHTTESTS_CUSTOMNODE_HPP
#define IRRLICHTTESTS_CUSTOMNODE_HPP

#include "Irrlicht/irrlicht.h"

class CustomNode : public irr::scene::ISceneNode {

	private:
		irr::core::aabbox3df	_box;
		irr::video::S3DVertex	_vertices[4];
		irr::video::SMaterial	_material;

	public:
		CustomNode(ISceneNode *parent, irr::scene::ISceneManager *mgr, irr::s32 id);

		CustomNode(ISceneNode *parent, irr::scene::ISceneManager *mgr, irr::s32 id,
			const irr::core::vector3df &position, const irr::core::vector3df &rotation,
			const irr::core::vector3df &scale
		);

		void OnRegisterSceneNode() override;

		void render() override;

		const irr::core::aabbox3d<irr::f32> &getBoundingBox() const override;

		irr::u32 getMaterialCount() const override;

		irr::video::SMaterial &getMaterial(irr::u32 num) override;
};

#endif //IRRLICHTTESTS_CUSTOMNODE_HPP
