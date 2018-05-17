//
// Created by Nicolas Guerin on 17/05/2018.
//

#include "AObject.hpp"

#include <utility>

namespace object {

AObject::AObject(std::string path, Type type) : _pathToMesh{std::move(path)}, _type{type}
{

}

AObject::~AObject()
{

}
}
