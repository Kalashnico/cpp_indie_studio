//
// Created by Nicolas Guerin on 14/05/2018.
//

#pragma once

#include "Loot.hpp"

class Box {
	public:
		Box(int posx, int posy, Loot loot);
		~Box();

		void destroyBox() noexcept { _destroy = true; };
		
		//Getter
		bool isDestroyed() const noexcept { return _destroy; };

	private:
		int _posx;
		int _posy;
		Loot _loot;
		std::string _pathToMesh;
		bool _destroy;
};
