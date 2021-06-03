#pragma once

#include "classes.h"


void GotoXY(size_t x, size_t y);

void draw_coord(size_t x, size_t y);

void draw_ships(size_t x, size_t y, std::vector<std::vector<bool>> arr, bool bot);

bool cursor_in_map(size_t start_x, size_t start_y, size_t x, size_t y);

void draw_dead_missed_ships(size_t x, size_t y, std::vector<std::vector<bool>> dead, std::vector<std::vector<bool>> missed);

short check_size(std::vector<std::vector<bool>> arr, short& vec_x, short& vec_y, bool& direction);

void fill_missed_around(short vec_x, short vec_y, std::vector<std::vector<bool>>& missed_shots, std::vector<std::vector<bool>> dead_ships, short size, bool direction);

void bot_shooting(std::vector<std::vector<bool>> player, std::vector<std::vector<bool>>& dead_ships, std::vector<std::vector<bool>>& missed_ships, short& mode, short& hit_x, short& hit_y, short& direction, short& lives, std::vector<short>& dirs);

void play(std::vector<std::vector<bool>> player, std::vector<std::vector<bool>> bot);

bool ship_in_map(size_t start_x, size_t start_y, size_t x, size_t y, size_t size_ship, size_t direction); //0 - горизонталь, 1 - вертикаль

void game_setting(Player& my_map);
