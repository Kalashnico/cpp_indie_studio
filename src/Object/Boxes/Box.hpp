//
// Created by Nicolas Guerin on 14/05/2018.
//

#pragma once

#include <Object/AObject.hpp>
#include "Loot.hpp"

namespace object {

class Box : public AObject {
	public:
		explicit Box(Loot loot);
		~Box() ;

		void destroyBox() noexcept { _destroy = true; };

		//Getter
		bool isDestroyed() const noexcept { return _destroy; }
		Loot getLoot() const noexcept { return _loot; }

	private:
		Loot _loot;
		bool _destroy;
};
}
