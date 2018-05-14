//
// Created by Nicolas Guerin on 14/05/2018.
//

#include <iostream>
#include <ctime>
#include "Map.hpp"

int main(void) {

	srand(time(nullptr));
	Map map;

	std::array<std::array<int, MAP_SIZE>, MAP_SIZE> pMap = map.getMap();
	for (auto i = 0; i < MAP_SIZE; ++i) {
		for (auto c = 0; c < MAP_SIZE; ++c) {
			std::cout <<  pMap.at(i).at(c);
		}
		std::cout << std::endl;
	}
	return 0;
}
