#include "main_funcs.h"

bool ship_in_map(size_t start_x, size_t start_y, size_t x, size_t y, size_t size_ship, size_t direction) { //0 - горизонталь, 1 - вертикаль

	switch (direction) {
	case 0:
		if (y < start_y + 1 || y > start_y + ch::N * ch::y || x < start_x + ch::between + 1 || x + size_ship + (size_ship - 1) * (ch::x - 1) > start_x + 1 + ch::between + ch::N * ch::x) {
			return false;
		}
		break;
	case 1:
		if (x < start_x + ch::between || x > start_x + ch::between + ch::N * ch::x || y < start_y + 1 || y + size_ship + (size_ship - 1) * (ch::y - 1) > start_y + ch::N * ch::y + 1) {
			return false;
		}
		break;
	}

	return true;
}


void game_setting(Player& my_map) {
	size_t size_ship = 4;
	size_t num_ships = 0;
	bool direction = 0;
	char symbol;

	size_t x = ch::start_x + 1 + ch::between;
	size_t y = ch::start_y + 1;

	size_t vec_x = 0;
	size_t vec_y = 0;

	system("cls");
	while (size_ship != 0) {
		draw_coord(ch::start_x, ch::start_y);
		draw_ships(ch::start_x, ch::start_y, my_map.GetMap(), 0);
		my_map.ship_show(vec_x, vec_y, x, y, size_ship, direction);

		bool temp_dir = direction;
		size_t temp_x = x;
		size_t temp_y = y;
		size_t temp_vec_x = vec_x;
		size_t temp_vec_y = vec_y;

		symbol = _getch();
		GotoXY(ch::start_x, ch::start_y + ch::y * ch::N + 2);
		std::cout << "                                                ";

		switch (symbol) {
		case 'w':
			y -= ch::y;
			vec_y -= 1;
			break;
		case 'a':
			x -= ch::x;
			vec_x -= 1;
			break;
		case 's':
			y += ch::y;
			vec_y += 1;
			break;
		case 'd':
			x += ch::x;
			vec_x += 1;
			break;
		case 'r':
			direction = !direction;
			break;
		case 13:
			if (my_map.set_ship(vec_x, vec_y, size_ship, direction)) {
				++num_ships;
				switch (num_ships) {
				case 1:
					size_ship = 3;
					break;
				case 3:
					size_ship = 2;
					break;
				case 6:
					size_ship = 1;
					break;
				case 10:
					size_ship = 0;
					break;
				}
			}
			else {
				GotoXY(ch::start_x, ch::start_y + ch::y * ch::N + 2);
				std::cout << "\x1b[31mWARNING: Вы не можете поставить здесь корабль!\x1b[0m" << std::endl;
			}
			break;
		}

		if (!ship_in_map(ch::start_x, ch::start_y, x, y, size_ship, direction)) {
			x = temp_x;
			y = temp_y;
			vec_x = temp_vec_x;
			vec_y = temp_vec_y;
			direction = temp_dir;
		}
	}
}
