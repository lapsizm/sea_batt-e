#include "classes.h"
#include "main_funcs.h"

int main() {
	setlocale(LC_ALL, "Rus");

	Sea_Bot bot;
	bot.set_map();

	Player my_map;

	std::cout << "\x1b[36m\t\t\t\t���� ������� ���\x1b[0m" << std::endl << std::endl;
	std::cout << "\x1b[32m\t������� ����:\x1b[0m" << std::endl;
	std::cout << "\t������ ������� ������� �����" << std::endl;
	std::cout << "\tw - ����������� �����" << std::endl;
	std::cout << "\ts - ����������� ����" << std::endl;
	std::cout << "\ta - ����������� �����" << std::endl;
	std::cout << "\td - ����������� ������" << std::endl;
	std::cout << "\tr - �������� �������" << std::endl << std::endl;

	char enter;
	std::cout << "\t������� \x1b[34mENTER\x1b[0m, ����� ������ ������" << std::endl;
	enter = _getch();
	if (enter == 13) {
		game_setting(my_map);
		Sleep(1000);
		system("cls");
		std::cout << "\t�������� ������!" << std::endl;
		Sleep(1000);

		system("cls");
		
		play(my_map.GetMap(), bot.GetMap());
	}	
}