//
// Created by Nicolas Guerin on 14/05/2018.
//

#include "Box.hpp"

namespace object {

/**
 * Constructor : Ready To use. Create a box with the loot appropriate (20% luck)
 * @param posx
 * @param posy
 * @param loot : if theres is no loot it is set to nullptr
 */
Box::Box(std::unique_ptr<Loot> loot)
	: AObject("PATH BOXE", BOX),
	_loot{std::move(loot)}
{}

Box::~Box()
{}

}
