#include "classes.h"
#include "main_funcs.h"

int main() {
	setlocale(LC_ALL, "Rus");

	Sea_Bot bot;
	bot.set_map();

	Player my_map;

	std::cout << "\x1b[36m\t\t\t\tИГРА МОРСКОЙ БОЙ\x1b[0m" << std::endl << std::endl;
	std::cout << "\x1b[32m\tПравила игры:\x1b[0m" << std::endl;
	std::cout << "\tНельзя ставить корабли рядом" << std::endl;
	std::cout << "\tw - перемещение вверх" << std::endl;
	std::cout << "\ts - перемещение вниз" << std::endl;
	std::cout << "\ta - перемещение влево" << std::endl;
	std::cout << "\td - перемещение вправо" << std::endl;
	std::cout << "\tr - разворот корабля" << std::endl << std::endl;

	char enter;
	std::cout << "\tНажмите \x1b[34mENTER\x1b[0m, чтобы начать играть" << std::endl;
	enter = _getch();
	if (enter == 13) {
		game_setting(my_map);
		Sleep(1000);
		system("cls");
		std::cout << "\tНачинаем играть!" << std::endl;
		Sleep(1000);

		system("cls");
		
		play(my_map.GetMap(), bot.GetMap());
	}	
}