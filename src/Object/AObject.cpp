//
// Created by Nicolas Guerin on 17/05/2018.
//

#include "AObject.hpp"
#include "Loot.hpp"

namespace object {

AObject::AObject(Type type)
	: _type{type},
	_toBeDestroyed{false}
{}

std::unique_ptr<Loot> AObject::getLoot() noexcept
{
	return nullptr;
}

}
