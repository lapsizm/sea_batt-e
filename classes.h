#pragma once

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <vector>


namespace ch {
	const size_t N = 10;
	const size_t x = 4;
	const size_t y = 2;
	const size_t between = 4;
	const size_t start_x = 3;
	const size_t start_y = 3;
}


class Sea_Battle {
protected:
	std::vector<std::vector<bool>> map = {};
public:

	Sea_Battle() {
		map.resize(ch::N);
		for (size_t i = 0; i < ch::N; ++i) {
			map[i].resize(ch::N);
		}
	}

	std::vector<std::vector<bool>>& GetMap() {
		return map;
	}

	bool out_of_map(size_t x, size_t y, size_t size_ship, size_t direction);   //0 - вправо, 1 - вниз, 2 - вверх, 3 - влево 


	bool set_is_possible(size_t x, size_t y, size_t size_ship, size_t direction, bool check_bot);

};



class Sea_Bot : public Sea_Battle {
public:
	Sea_Bot() = default;

	void set_map();
};


class Player : public Sea_Battle {
public:

	Player() = default;

	void ship_show(size_t vec_x, size_t vec_y, size_t x, size_t y, size_t size_ship, bool direction);

	bool set_ship(size_t vec_x, size_t vec_y, size_t size_ship, bool direction);

};


