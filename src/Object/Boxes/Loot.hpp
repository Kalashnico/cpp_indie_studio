//
// Created by Nicolas Guerin on 14/05/2018.
//

#pragma once

#include <string>
#include <array>
#include "Irrlicht/irrlicht.h"
#include "AObject.hpp"
#include "Gfx.hpp"

namespace object {

//Theses are the paths to loot meshs
class Loot : public AObject {
	public:
		Loot(int posx, int posy, Gfx *gfx);
		~Loot();

		void display() noexcept;

		//Getters
		LootCategory getLootCategory() const noexcept { return _category; };

	private:
		LootCategory _category;
		std::string _modelPath;
		irr::core::vector3df _modelSize;

		int _posx;
		int _posy;
		Gfx *_gfx;
		irr::scene::IAnimatedMeshSceneNode *_node;

		//Member Function
		void setupLoot() noexcept;

};
}
