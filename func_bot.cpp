#include "main_funcs.h"

void bot_shooting(std::vector<std::vector<bool>> player, std::vector<std::vector<bool>>& dead_ships, std::vector<std::vector<bool>>& missed_ships, short& mode, short& hit_x, short& hit_y, short& direction, short& lives, std::vector<short>& dirs) {

	while (mode == 0) {
		if (dead_ships == player) {
			return;
		}

		hit_x = rand() % ch::N;
		hit_y = rand() % ch::N;
		while (missed_ships[hit_x][hit_y] == 1 || dead_ships[hit_x][hit_y] == 1) {
			hit_x = rand() % ch::N;
			hit_y = rand() % ch::N;
		}
		if (player[hit_x][hit_y] == 0) {
			missed_ships[hit_x][hit_y] = 1;
			draw_dead_missed_ships(ch::start_x, ch::start_y, dead_ships, missed_ships);

			GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
			std::cout << "                                                ";
			GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
			std::cout << "Бот промахнулся по координате:  " << hit_x + 1 << "  " << char(hit_y + 48 + 17);
			return;
		}
		else if (player[hit_x][hit_y] == 1) {
			mode = 1;
			++lives;
			dead_ships[hit_x][hit_y] = 1;
			dirs.clear();

			std::vector<short> temp_dirs(4, -1);
			short temp_dir;
			bool there_is = 0;
			for (size_t i = 0; i < 4; ++i) {
				temp_dir = rand() % 4;
				for (size_t j = 0; j < 4; ++j) {
					if (temp_dirs[j] == temp_dir) {
						--i;
						there_is = 1;
						break;
					}
				}
				if (!there_is) {
					temp_dirs[i] = temp_dir;     //0 - вправо, 1 - влево, 2 - вверх, 3 - вниз
				}
				there_is = 0;
			}
			for (size_t i = 0; i < temp_dirs.size(); ++i) {
				dirs.push_back(temp_dirs[i]);
			}

			bool temp_d = 0;
			short new_x = hit_x;
			short new_y = hit_y;
			short size = check_size(player, new_y, new_x, temp_d);

			bool get = 0;

			if (size == 1) {
				get = 1;
				mode = 0;
				lives = 0;
				fill_missed_around(new_y, new_x, missed_ships, dead_ships, size, temp_d);
				draw_dead_missed_ships(ch::start_x, ch::start_y, dead_ships, missed_ships);

				GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
				std::cout << "                                                ";
				GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
				std::cout << "Бот добил ваш корабль по координате:  " << hit_x + 1 << "  " << char(hit_y + 48 + 17);

				Sleep(3500);
			}


			if (hit_x == 0) {						//0 - вправо, 1 - влево, 2 - вверх, 3 - вниз
				short temp_dir;
				for (size_t i = 0; i < 4; ++i) {
					if (dirs[i] == 2) {
						temp_dir = i;
						break;
					}
				}
				dirs.erase(dirs.begin() + temp_dir);
			}
			if (hit_x == ch::N - 1) {
				short temp_dir;
				for (size_t i = 0; i < 4; ++i) {
					if (dirs[i] == 3) {
						temp_dir = i;
						break;
					}
				}
				dirs.erase(dirs.begin() + temp_dir);
			}
			if (hit_y == 0) {
				short temp_dir;
				for (size_t i = 0; i < 4; ++i) {
					if (dirs[i] == 1) {
						temp_dir = i;
						break;
					}
				}
				dirs.erase(dirs.begin() + temp_dir);
			}

			if (hit_y == ch::N - 1) {
				short temp_dir;
				for (size_t i = 0; i < 4; ++i) {
					if (dirs[i] == 0) {
						temp_dir = i;
						break;
					}
				}
				dirs.erase(dirs.begin() + temp_dir);
			}
			direction = dirs[dirs.size() - 1];
			draw_dead_missed_ships(ch::start_x, ch::start_y, dead_ships, missed_ships);
			if (!get) {
				GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
				std::cout << "                                                ";
				GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
				std::cout << "Бот попал по кораблю в координате:  " << hit_x + 1 << "  " << char(hit_y + 48 + 17);

				Sleep(3500);
			}
		}
	}
	short temp_hit_x = hit_x;
	short temp_hit_y = hit_y;
	short temp_dir = direction;

	if (mode == 1) {
		switch (temp_dir) {
		case 0:
			++temp_hit_y;
			break;
		case 1:
			--temp_hit_y;
			break;
		case 2:
			--temp_hit_x;
			break;
		case 3:
			++temp_hit_x;
			break;
		}
		if (missed_ships[temp_hit_x][temp_hit_y] == 1) {
			dirs.pop_back();
			direction = dirs[dirs.size() - 1];
			bot_shooting(player, dead_ships, missed_ships, mode, hit_x, hit_y, direction, lives, dirs);
			return;
		}

		if (player[temp_hit_x][temp_hit_y] == 0) {
			missed_ships[temp_hit_x][temp_hit_y] = 1;
			dirs.pop_back();
			direction = dirs[dirs.size() - 1];
			draw_dead_missed_ships(ch::start_x, ch::start_y, dead_ships, missed_ships);
			GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
			std::cout << "                                                ";
			GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
			std::cout << "Бот промахнулся по координате:  " << temp_hit_x + 1 << "  " << char(temp_hit_y + 48 + 17);
		}
		else {
			dead_ships[temp_hit_x][temp_hit_y] = 1;
			bool temp_d = 0;
			short new_x = hit_x;
			short new_y = hit_y;
			short size = check_size(player, new_y, new_x, temp_d);
			if (size == 2) {
				mode = 0;
				fill_missed_around(new_y, new_x, missed_ships, dead_ships, size, temp_d);
				lives = 0;
				draw_dead_missed_ships(ch::start_x, ch::start_y, dead_ships, missed_ships);
				GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
				std::cout << "                                                ";
				GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
				std::cout << "Бот добил корабль по координате:  " << temp_hit_x + 1 << "  " << char(temp_hit_y + 48 + 17);

				Sleep(3500);
				bot_shooting(player, dead_ships, missed_ships, mode, hit_x, hit_y, direction, lives, dirs);
				return;
			}
			++lives;
			mode = 2;
			draw_dead_missed_ships(ch::start_x, ch::start_y, dead_ships, missed_ships);
			GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
			std::cout << "                                                ";
			GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
			std::cout << "Бот попал по кораблю в координате:  " << hit_x + 1 << "  " << char(hit_y + 48 + 17);

			Sleep(3500);
		}
	}

	if (mode == 2) {
		if (temp_hit_x == 0 && direction == 2) {
			direction = 3;
			temp_hit_x = hit_x;
			temp_hit_y = hit_y;
		}
		if (temp_hit_x == ch::N - 1 && direction == 3) {
			direction = 2;
			temp_hit_x = hit_x;
			temp_hit_y = hit_y;
		}
		if (temp_hit_y == 0 && direction == 1) {
			direction = 0;
			temp_hit_x = hit_x;
			temp_hit_y = hit_y;
		}
		if (temp_hit_y == ch::N - 1 && direction == 0) {
			direction = 1;
			temp_hit_x = hit_x;
			temp_hit_y = hit_y;
		}


		while (player[temp_hit_x][temp_hit_y] == 1) {
			switch (direction) {
			case 0:
				++temp_hit_y;
				break;
			case 1:
				--temp_hit_y;
				break;
			case 2:
				--temp_hit_x;
				break;
			case 3:
				++temp_hit_x;
				break;
			}
			if (temp_hit_x >= 0 && temp_hit_x <= ch::N - 1 && temp_hit_y >= 0 && temp_hit_y <= ch::N - 1 && player[temp_hit_x][temp_hit_y] == 1) {
				dead_ships[temp_hit_x][temp_hit_y] = 1;
				bool temp_d = 0;
				short new_x = hit_x;
				short new_y = hit_y;
				short size = check_size(player, new_y, new_x, temp_d);

				++lives;
				if (lives == size) {
					mode = 0;
					fill_missed_around(new_y, new_x, missed_ships, dead_ships, size, temp_d);
					lives = 0;
					draw_dead_missed_ships(ch::start_x, ch::start_y, dead_ships, missed_ships);
					GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
					std::cout << "                                                ";
					GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
					std::cout << "Бот добил ваш корабль по координате:  " << temp_hit_x + 1 << "  " << char(temp_hit_y + 48 + 17);

					Sleep(3500);
					bot_shooting(player, dead_ships, missed_ships, mode, hit_x, hit_y, direction, lives, dirs);
					return;
				}
				draw_dead_missed_ships(ch::start_x, ch::start_y, dead_ships, missed_ships);
				GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
				std::cout << "                                                ";
				GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
				std::cout << "Бот попал в ваш корабль по координате:  " << temp_hit_x + 1 << "  " << char(temp_hit_y + 48 + 17);

				Sleep(3500);
			}
			else {
				bool hit = 0;
				if (temp_hit_x >= 0 && temp_hit_x <= ch::N - 1 && temp_hit_y >= 0 && temp_hit_y <= ch::N - 1 && missed_ships[temp_hit_x][temp_hit_y] != 1) {
					missed_ships[temp_hit_x][temp_hit_y] = 1;
					hit = 1;
				}
				switch (direction) {
				case 0:
					direction = 1;
					break;
				case 1:
					direction = 0;
					break;
				case 2:
					direction = 3;
					break;
				case 3:
					direction = 2;
					break;
				}
				draw_dead_missed_ships(ch::start_x, ch::start_y, dead_ships, missed_ships);
				if (hit) {
					GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
					std::cout << "                                                ";
					GotoXY(ch::start_x, ch::start_y + ch::N * ch::y + 5);
					std::cout << "Бот промахнулся в координате:  " << temp_hit_x + 1 << "  " << char(temp_hit_y + 48 + 17);

					Sleep(3500);
					return;
				}
				temp_hit_x = hit_x;
				temp_hit_y = hit_y;
			}
		}
	}
}