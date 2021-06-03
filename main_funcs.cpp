#include "main_funcs.h"



void GotoXY(size_t x, size_t y) {
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}


void draw_coord(size_t x, size_t y) {
	char a = 'A';
	size_t temp_x = x;
	size_t temp_y = y;
	for (size_t i = 0; i < ch::N; ++i) {

		GotoXY(x + 1 + ch::between, y);
		std::cout << a;
		++a;
		x += ch::x;

		if (i == 9) {
			std::cout << std::endl;
		}
	}

	x = temp_x;
	a = 'A';

	for (size_t i = 0; i < ch::N; ++i) {
		GotoXY(x + 1 + ch::between, y + ch::N * ch::y - (ch::y - 2));

		std::cout << a;
		++a;
		x += ch::x;

		if (i == 9) {
			std::cout << std::endl;
		}
	}

	x = temp_x;

	for (size_t i = 0; i < ch::N; ++i) {
		if (i < 9) {
			GotoXY(x + 1, y + 1);
			std::cout << i + 1;
			y += ch::y;
			std::cout << std::endl;
		}
		else {
			GotoXY(x, y + 1);
			std::cout << i + 1;
			y += ch::y;
			std::cout << std::endl;
		}
	}

	x = temp_x;
	y = temp_y;

	for (size_t i = 0; i < ch::N; ++i) {
		GotoXY(x + ch::between + ch::N * ch::x + ch::between - (ch::x - 1), y + 1);
		std::cout << i + 1;
		y += ch::y;
		std::cout << std::endl;
	}
}




void draw_ships(size_t x, size_t y, std::vector<std::vector<bool>> arr, bool bot) {
	x += 1 + ch::between;
	y += 1;
	for (size_t i = 0; i < ch::N; ++i) {
		GotoXY(x, y + ch::y * i);

		for (size_t j = 0; j < ch::N; ++j) {
			if (arr[i][j] == 1 && bot == 0) {
				std::cout << "#";
			}
			else {
				std::cout << "-";
			}
			GotoXY(x + ch::x * (j + 1), y + ch::y * i);
		}
		std::cout << std::endl;
	}
}


bool cursor_in_map(size_t start_x, size_t start_y, size_t x, size_t y) {
	if (y < start_y + 1 || y > start_y + ch::N * ch::y || x < start_x + ch::between + 1 || x > start_x + 1 + ch::N * ch::x) {
		return false;
	}
	return true;
}


void draw_dead_missed_ships(size_t x, size_t y, std::vector<std::vector<bool>> dead, std::vector<std::vector<bool>> missed) {
	x += ch::x + 1;
	y += 1;
	for (size_t i = 0; i < dead.size(); ++i) {
		for (size_t j = 0; j < dead.size(); ++j) {
			if (dead[i][j] == 1) {
				GotoXY(x + ch::x * j, y);
				std::cout << "\x1b[31mX\x1b[0m";
			}
			if (missed[i][j] == 1) {
				GotoXY(x + ch::x * j, y);
				std::cout << "\x1b[34mo\x1b[0m";
			}
		}
		y += ch::y;
	}

}

short check_size(std::vector<std::vector<bool>> arr, short& vec_x, short& vec_y, bool& direction) {
	short size_ship = 1;
	short temp_x = vec_x;
	short temp_y = vec_y;

	if (vec_y == 0 || (temp_y != ch::N - 1 && arr[temp_y + 1][temp_x] == 1)) {
		while (temp_y != ch::N - 1 && arr[temp_y + 1][temp_x] != 0)
		{
			++size_ship;
			++temp_y;
			direction = 1;
			if (temp_y == ch::N - 1) {
				break;
			}
		}
	}

	temp_y = vec_y;

	if (vec_y == ch::N - 1 || (temp_y != 0 && arr[temp_y - 1][temp_x] == 1)) {
		while (arr[vec_y - 1][temp_x] != 0)
		{
			++size_ship;
			--vec_y;
			direction = 1;
			if (vec_y == 0) {
				break;
			}
		}
	}

	if (vec_x == 0 || (temp_x != ch::N - 1 && arr[temp_y][temp_x + 1] == 1)) {
		while (arr[temp_y][temp_x + 1] != 0)
		{
			++size_ship;
			++temp_x;
			direction = 0;
			if (temp_x == ch::N - 1) {
				break;
			}
		}
	}

	temp_x = vec_x;

	if (vec_x == ch::N - 1 || (temp_x != 0 && arr[temp_y][temp_x - 1] == 1)) {
		while (arr[temp_y][vec_x - 1] != 0)
		{
			++size_ship;
			--vec_x;
			direction = 0;
			if (vec_x == 0) {
				break;
			}
		}
	}
	return size_ship;
}

void fill_missed_around(short vec_x, short vec_y, std::vector<std::vector<bool>>& missed_shots, std::vector<std::vector<bool>> dead_ships, short size, bool direction) {
	short temp_x = vec_x;
	short temp_y = vec_y;

	switch (direction) {
	case 0:
		if (vec_y != 0 && vec_y != ch::N - 1) {
			for (size_t i = 0; i < size; ++i) {
				missed_shots[vec_y + 1][vec_x + i] = 1;
				missed_shots[vec_y - 1][vec_x + i] = 1;
			}
			--vec_y;
			if (vec_x + size - 1 != ch::N - 1) {
				for (size_t i = 0; i < 3; ++i) {
					missed_shots[vec_y + i][vec_x + size] = 1;
				}
			}
			if (vec_x != 0) {
				for (size_t i = 0; i < 3; ++i) {
					missed_shots[vec_y + i][vec_x - 1] = 1;
				}
			}

			break;
		}
		if (vec_y == 0) {
			for (size_t i = 0; i < size; ++i) {
				missed_shots[vec_y + 1][vec_x + i] = 1;
			}

			if (vec_x != 0) {
				for (size_t i = 0; i < 2; ++i)
				{
					missed_shots[vec_y + i][vec_x - 1] = 1;
				}
			}
			if (vec_x + size - 1 != ch::N - 1) {
				for (size_t i = 0; i < 2; ++i)
				{
					missed_shots[vec_y + i][vec_x + size] = 1;
				}
			}
			break;
		}

		if (vec_y == ch::N - 1) {
			for (size_t i = 0; i < size; ++i) {
				missed_shots[vec_y - 1][vec_x + i] = 1;
			}
			if (vec_x != 0) {
				for (size_t i = 0; i < 2; ++i)
				{
					missed_shots[vec_y - i][vec_x - 1] = 1;
				}
			}
			if (vec_x + size - 1 != ch::N - 1) {
				for (size_t i = 0; i < 2; ++i)
				{
					missed_shots[vec_y - i][vec_x + size] = 1;
				}
			}
			break;
		}
	case 1:
		if (vec_x != 0 && vec_x != ch::N - 1) {
			for (size_t i = 0; i < size; ++i) {
				missed_shots[vec_y + i][vec_x + 1] = 1;
				missed_shots[vec_y + i][vec_x - 1] = 1;
			}
			--vec_x;
			if (vec_y != 0) {
				for (size_t i = 0; i < 3; ++i) {
					missed_shots[vec_y - 1][vec_x + i] = 1;
				}
			}

			if (vec_y + size - 1 != ch::N - 1) {
				for (size_t i = 0; i < 3; ++i) {
					missed_shots[vec_y + size][vec_x + i] = 1;
				}
			}
			break;
		}
		if (vec_x == 0) {
			for (size_t i = 0; i < size; ++i) {
				missed_shots[vec_y + i][vec_x + 1] = 1;
			}

			if (vec_y != 0) {
				for (size_t i = 0; i < 2; ++i)
				{
					missed_shots[vec_y - 1][vec_x + i] = 1;
				}
			}
			if (vec_y + size - 1 != ch::N - 1) {
				for (size_t i = 0; i < 2; ++i)
				{
					missed_shots[vec_y + size][vec_x + i] = 1;
				}
			}
			break;
		}

		if (vec_x == ch::N - 1) {
			for (size_t i = 0; i < size; ++i) {
				missed_shots[vec_y + i][vec_x - 1] = 1;
			}
			if (vec_y != 0) {
				for (size_t i = 0; i < 2; ++i)
				{
					missed_shots[vec_y - 1][vec_x - i] = 1;
				}
			}
			if (vec_y + size - 1 != ch::N - 1) {
				for (size_t i = 0; i < 2; ++i)
				{
					missed_shots[vec_y + size][vec_x - i] = 1;
				}
			}
			break;
		}
	}
}

void play(std::vector<std::vector<bool>> player, std::vector<std::vector<bool>> bot) {
	std::cout << "\tВАШЕ ПОЛЕ:";
	draw_coord(ch::start_x, ch::start_y);
	draw_ships(ch::start_x, ch::start_y, player, 0);

	size_t start_x_bot = ch::start_x + ch::N * ch::x + 2 * ch::between + 10;

	GotoXY(start_x_bot, 0);
	std::cout << "ПОЛЕ ПРОТИВНИКА:";
	draw_coord(start_x_bot, ch::start_y);
	draw_ships(start_x_bot, ch::start_y, bot, 1);

	short x = start_x_bot + ch::between + 1;
	short y = ch::start_y + 1;

	short vec_x = 0;
	short vec_y = 0;

	char symbol;

	std::vector<std::vector<bool>> dead_ships(bot.size());
	std::vector<std::vector<bool>> missed_shots(bot.size());
	std::vector<std::vector<bool>> dead_ships_player(player.size());
	std::vector<std::vector<bool>> missed_ships_player(player.size());

	for (size_t i = 0; i < bot.size(); ++i) {
		dead_ships[i].resize(bot.size());
		missed_shots[i].resize(bot.size());
		dead_ships_player[i].resize(player.size());
		missed_ships_player[i].resize(player.size());
	}

	bool won = 1;
	short mode = 0;

	short hit_x = 0;
	short hit_y = 0;
	bool hitting = 0;
	short direction_bot = 0;
	short lives = 0;

	std::vector<short> dirs;
	while (won) {
		bool winning = 1;
		short true_size_ship = 0;
		short size_ship = 0;

		while (winning) {
			GotoXY(x, y);
			if (dead_ships[vec_y][vec_x] == 1) {
				std::cout << "\x1b[32m@\x1b[0m";
			}

			else if (missed_shots[vec_y][vec_x] == 1) {
				std::cout << "\x1b[31m@\x1b[0m";
			}
			else {
				std::cout << "@";
			}

			size_t temp_x = x;
			size_t temp_y = y;
			size_t temp_vec_x = vec_x;
			size_t temp_vec_y = vec_y;


			symbol = _getch();

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
			case 13:
				if (missed_shots[vec_y][vec_x] == 1 || dead_ships[vec_y][vec_x] == 1) {
					continue;
				}
				if (bot[vec_y][vec_x] == 1) {
					dead_ships[vec_y][vec_x] = 1;
					winning = 1;
					short new_x_true = vec_x;
					short new_y_true = vec_y;
					bool direction_true = 0;
					bool direction_now = 0;
					true_size_ship = check_size(bot, new_x_true, new_y_true, direction_true);
					short new_x_now = vec_x;
					short new_y_now = vec_y;
					size_ship = check_size(dead_ships, new_x_now, new_y_now, direction_now);
					if (true_size_ship == size_ship) {
						fill_missed_around(new_x_true, new_y_true, missed_shots, dead_ships, size_ship, direction_true);
						GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
						std::cout << "                                                ";
						GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
						std::cout << "Вы добили корабль по координате:  " << vec_y + 1 << "  " << char(vec_x + 48 + 17);
						Sleep(1000);
						break;
					}
					GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
					std::cout << "                                                ";
					GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
					std::cout << "Вы попали по короблю в:  " << vec_y + 1 << "  " << char(vec_x + 48 + 17);
					Sleep(1000);
				}
				else {
					winning = 0;
					missed_shots[vec_y][vec_x] = 1;
					GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
					std::cout << "                                                ";
					GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
					std::cout << "Вы промахнулись по координате:  " << vec_y + 1 << "  " << char(vec_x + 48 + 17);
					Sleep(1000);
				}
			}

			if (!cursor_in_map(start_x_bot, ch::start_y, x, y)) {
				x = temp_x;
				y = temp_y;
				vec_x = temp_vec_x;
				vec_y = temp_vec_y;
			}

			draw_ships(start_x_bot, ch::start_y, bot, 1);
			draw_dead_missed_ships(start_x_bot, ch::start_y, dead_ships, missed_shots);

			if (dead_ships == bot) {
				Sleep(3000);
				GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
				std::cout << "                                                ";
				std::cout << "YOU HAVE WON";
				return;
			}
		}
		bot_shooting(player, dead_ships_player, missed_ships_player, mode, hit_x, hit_y, direction_bot, lives, dirs);


		if (dead_ships_player == player) {
			Sleep(3000);
			GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
			std::cout << "                                                ";
			std::cout << "YOU LOST";
			return;
		}
	}
}