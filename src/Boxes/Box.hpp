//
// Created by Nicolas Guerin on 14/05/2018.
//

#pragma once

#include <string>
#include "../Map/IObject.hpp"
#include "../Loot/Loot.hpp"

class Box : public map::IObject {
	public:
		Box(Loot loot);
		~Box();

		void destroyBox() noexcept { _destroy = true; };

		//Getter
		bool isDestroyed() const noexcept { return _destroy; };

	private:
		Loot _loot;
		std::string _pathToMesh;
		bool _destroy;
};
