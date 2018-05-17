//
// Created by Nicolas Guerin on 17/05/2018.
//

#pragma once

#include <Object/AObject.hpp>

namespace object {

class Bomb : public AObject {
	public:
		Bomb(int blast);
		~Bomb();

	private:
		int _blastSize;

};
}
