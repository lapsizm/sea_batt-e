#include "classes.h"
#include "main_funcs.h"

bool Sea_Battle::out_of_map(size_t x, size_t y, size_t size_ship, size_t direction) {   //0 - вправо, 1 - вниз, 2 - вверх, 3 - влево  
	switch (direction) {
	case 0:
		if (y + size_ship > ch::N) {
			return true;
		}
		break;
	case 1:
		if (x + size_ship > ch::N) {
			return true;
		}
		break;

	case 2:
		if (x < size_ship - 1) {
			return true;
		}
		break;
	case 3:
		if (y < size_ship - 1) {
			return true;
		}
		break;
	}
	return false;
}


bool Sea_Battle::set_is_possible(size_t x, size_t y, size_t size_ship, size_t direction, bool check_bot) {
	if (check_bot == 1 && out_of_map(x, y, size_ship, direction)) {
		return false;
	}

	for (size_t i = 0; i < size_ship; ++i) {
		if (map[x][y] == 1)
		{
			return false;
		}

		if (x != 0) {
			if (map[x - 1][y] == 1) {
				return false;
			}
		}

		if (x != ch::N - 1)
		{
			if (map[x + 1][y] == 1) {
				return false;
			}
		}

		if (y != 0) {
			if (map[x][y - 1] == 1) {
				return false;
			}
		}

		if (y != ch::N - 1) {
			if (map[x][y + 1] == 1) {
				return false;
			}
		}

		if (x != 0 && y != 0) {
			if (map[x - 1][y - 1] == 1) {
				return false;
			}
		}

		if (x != 0 && y != ch::N - 1) {
			if (map[x - 1][y + 1] == 1) {
				return false;
			}
		}

		if (x != ch::N - 1 && y != 0) {
			if (map[x + 1][y - 1] == 1) {
				return false;
			}
		}

		if (x != ch::N - 1 && y != ch::N - 1) {
			if (map[x + 1][y + 1] == 1) {
				return false;
			}
		}

		switch (direction) {			 //0 - вправо, 1 - вниз, 2 - вверх, 3 - влево 
		case 0: ++y; continue;
		case 1: ++x; continue;
		case 2: --x; continue;
		case 3: --y; continue;
		}
	}
	return true;
}


void Sea_Bot::set_map() {
	srand(time(NULL));

	for (size_t size_ship = 4, num_ships = 1; size_ship != 0; --size_ship, ++num_ships)
	{
		for (short i = 0; i < num_ships; ++i) {
			size_t x = rand() % 10;
			size_t y = rand() % 10;
			size_t direction = rand() % 4;    //0 - вправо, 1 - влево, 2 - вверх, 3 - вниз

			if (set_is_possible(x, y, size_ship, direction, 1))
			{
				for (size_t j = 0; j < size_ship; ++j)
				{
					map[x][y] = 1;

					switch (direction) {
					case 0: ++y; continue;
					case 1: ++x; continue;
					case 2: --x; continue;
					case 3: --y; continue;
					}
				}
			}
			else {
				--i;
			}
		}

	}
}

void Player::ship_show(size_t vec_x, size_t vec_y, size_t x, size_t y, size_t size_ship, bool direction) {


	for (size_t i = 0; i < size_ship; ++i) {
		GotoXY(x, y);
		if (set_is_possible(vec_y, vec_x, size_ship, direction, 0)) {
			std::cout << "\x1b[32m#\x1b[0m";
		}
		else {
			std::cout << "\x1b[31m#\x1b[0m";
		}
		switch (direction) {   //0 - горизонталь(вправо), 1 - вертикаль(вниз)
		case 0:
			x += ch::x;
			break;
		case 1:
			y += ch::y;
			break;
		}
	}
}

bool Player::set_ship(size_t vec_x, size_t vec_y, size_t size_ship, bool direction) {
	if (!(set_is_possible(vec_y, vec_x, size_ship, direction, 0))) {
		return false;
	}
	switch (direction) {										//0 - горизонталь, 1 - вертикаль
	case 0:
		for (size_t i = 0; i < size_ship; ++i) {
			map[vec_y][vec_x] = 1;
			++vec_x;
		}

		break;
	case 1:
		for (size_t i = 0; i < size_ship; ++i) {
			map[vec_y][vec_x] = 1;
			++vec_y;
		}
		break;
	}
	return true;
}