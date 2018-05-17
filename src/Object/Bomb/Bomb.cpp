//
// Created by Nicolas Guerin on 17/05/2018.
//

#include "Bomb.hpp"

namespace object {

Bomb::Bomb(int blast) : AObject("PATH BOMB MESH", BOMB), _blastSize{blast}
{
}

Bomb::~Bomb()
{

}
}
