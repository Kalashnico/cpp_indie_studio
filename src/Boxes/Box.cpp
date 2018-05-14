//
// Created by Nicolas Guerin on 14/05/2018.
//

#include "Box.hpp"

/**
 * Constructor : Ready To use. Create a box with the loot appropriate (20% luck)
 * @param posx 
 * @param posy 
 * @param loot : if theres is no loot it is set to nullptr
 */
Box::Box(int posx, int posy, Loot loot) : _posx{posx}, _posy{posy}, _loot{loot}, _pathToMesh{"PATH BOXE"}, _destroy{false}
{

}

Box::~Box()
{

}
