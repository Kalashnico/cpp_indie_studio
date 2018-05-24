//
// Created by jdecombe on 08/05/18.
//

#ifndef IRRLICHTTESTS_CUSTOMNODE_HPP
#define IRRLICHTTESTS_CUSTOMNODE_HPP

#include "Irrlicht/irrlicht.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class CustomNode : public ISceneNode {

	private:
		aabbox3df	_box;
		S3DVertex	_vertices[4];
		SMaterial	_material;

	public:
		CustomNode(ISceneNode *parent, ISceneManager *mgr, s32 id);

		CustomNode(ISceneNode *parent, ISceneManager *mgr, s32 id,
			const vector3df &position, const vector3df &rotation,
			const vector3df &scale
		);

		void OnRegisterSceneNode() override;

		void render() override;

		const aabbox3d<f32> &getBoundingBox() const override;

		u32 getMaterialCount() const override;

		SMaterial &getMaterial(u32 num) override;
};

#endif //IRRLICHTTESTS_CUSTOMNODE_HPP
