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
Box::Box(Loot loot) : AObject("PATH BOXE", BOX), _loot{loot}, _destroy{false}
{

}

Box::~Box()
{

}
}
