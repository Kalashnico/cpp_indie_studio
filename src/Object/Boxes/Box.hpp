//
// Created by Nicolas Guerin on 14/05/2018.
//

#pragma once

#include "AObject.hpp"
#include "Loot.hpp"

namespace object {

class Box : public AObject {
	public:
		explicit Box(std::unique_ptr<Loot> loot);
		~Box() ;

		std::unique_ptr<Loot> getLoot() noexcept { return std::move(_loot); }

	private:
		std::unique_ptr<Loot> _loot;
};
}
