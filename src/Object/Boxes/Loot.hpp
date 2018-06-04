//
// Created by Nicolas Guerin on 14/05/2018.
//

#pragma once

#include <string>
#include <array>
#include "AObject.hpp"

namespace object {

//Theses are the paths to loot meshs
class Loot : public AObject {
	public:
		Loot();
		~Loot();

		//Getters
		LootCategory getLootCategory() const noexcept { return _category; };

	private:
		LootCategory _category;

		//Member Function
		void setupLoot() noexcept;

};
}
