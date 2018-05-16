//
// Created by Nicolas Guerin on 16/05/2018.
//

#pragma once

#include <array>

#define MAP_SIZE 15

class Map {
	public:
		Map();
		~Map();

		//Getter
		std::array<std::array<int, MAP_SIZE>, MAP_SIZE> getMap() const noexcept { return _map; };
	private:
		//Private member Functions
		std::array<std::array<int, MAP_SIZE>, MAP_SIZE> createMap() const noexcept;
		std::array<std::array<int, MAP_SIZE>, MAP_SIZE>	addBoxes(std::array<std::array<int, MAP_SIZE>, MAP_SIZE> map) const noexcept;

		//Variable
		std::array<std::array<int, MAP_SIZE>, MAP_SIZE> _map;

};