//
// Created by Nicolas Guerin on 14/05/2018.
//

#include "Box.hpp"
#include "Map.hpp"

namespace object {

/**
 * Constructor : Ready To use. Create a box with the loot appropriate (20% luck)
 * @param posx
 * @param posy
 * @param loot : if theres is no loot it is set to nullptr
 */
Box::Box(std::unique_ptr<Loot> loot, ::map::Map *map, Gfx *gfx, int posx, int posy)
	: AObject(BOX),
	_loot{std::move(loot)},
	_map{map},
	_gfx{gfx},
	_node{nullptr},
	_posx{posx},
	_posy{posy}
{
	auto modelPath = "./media/models/box/ItmBox00.obj";
	vector3df modelSize = {0.25f, 0.25f, 0.25f};
	vector3df pos = {(float)posy, 0.f, (float)posx};
	pos -= 6.f;
	pos *= 4.f;
	pos.Y = 2.f;
	_node = _gfx->drawMesh(modelPath, "", false, "box " + std::to_string(_posx) + " " + std::to_string(_posy), pos);
	_node->setScale(modelSize);
}

Box::~Box()
{
	_gfx->deleteElement("box " + std::to_string(_posx) + " " + std::to_string(_posy));
}

}
