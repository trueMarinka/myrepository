#include <iostream>
#include<string>
#include<list>
#include<Windows.h>
#include<conio.h>
using namespace std;

enum VKey { ENTER = 13, ESC = 27, MVK_UP = 72, MVK_LEFT = 75, MVK_RIGHT = 77, MVK_DOWN = 80 };
void SetConsoleCursorPosition(short x_position, short y_position);
void UpdateConsole();
void ShowMenu();
void ShowSubmarine();
void GoAhead();
void GoBack();
void ShowInfo(string action);
int pos_x = 0, pos_y = 0;
int btn = 0;

class Submarine {
public:
	int x, y;
	string name;
	const int max_gas = 100;
	int gas;
	const int max_torpedo = 5;
	int torpedo;
	list<string>targets; 
	string target;

	Submarine() {
		x = 20;
		y = 10;
		name = "SARA";
		gas = max_gas;
		torpedo = max_torpedo;
		targets = { "1aim", "2aim", "3aim", "4aim", "5aim", "6aim" };
		target = "";
	}

	void FuelRate() {		// расход топлива
		gas -= 5;
	}

	bool IsCharge() {		// заряжены ли торпеды
		return torpedo;
	}

	void ReCharge() {		// перезарядить торпеды
		torpedo = max_torpedo;
		Sleep(2000);
	}

	void ShowTargets() {	// показать цели
		if (targets.size() == 0) {
			targets = { "1aim", "2aim", "3aim", "4aim", "5aim", "6aim" };
		}

		Sleep(2000);
		list<string>::iterator it;
		pos_x = 70;
		pos_y = 6;
		SetConsoleCursorPosition(pos_x, pos_y);
		for (it = targets.begin(); it != targets.end(); it++) {
			cout << (*it);
			pos_y++;
			SetConsoleCursorPosition(pos_x, pos_y);
		}

		for (;;) {
			if (kbhit) {
				btn = getch();
			}

			if (btn == MVK_UP) {
				pos_y--;
				SetConsoleCursorPosition(pos_x, pos_y);
			}

			if (btn == MVK_DOWN) {
				pos_y++;
				SetConsoleCursorPosition(pos_x, pos_y);
			}

			if (btn == ENTER) {
				it = targets.begin();
				int n = 6 + targets.size();			// 6 позиция по у с которой начинается меню целей

				for (int i = targets.size(); i > 0; i--, it++) {
					if (pos_y == (n - i)) {
						target = (*it);
						ShowInfo("Цель выбрана: " + target);
						Sleep(2000);
						return;
					}
				}
			}
		}
	}

	void Attack(string _target) {	// атаковать
		try {
			if (!IsCharge()) {
				throw false;
			}
			if (_target == "") {
				throw 1;
			}
			Sleep(2000);
			targets.remove(_target);
			torpedo--;
			cout << "\a\a";
			target = "";
			ShowInfo("Цель поражена!");
			Sleep(2000);
		}
		catch (bool) {
			ShowInfo("Нужно перезарядить торпеды!");
			Sleep(2000);
		}
		catch (int) {
			ShowInfo("Цель не выбрана!");
			Sleep(2000);
		}
	}
};

Submarine sub;

void main() {
	
	string target;
	SetConsoleOutputCP(1251);
	ShowMenu();
	ShowSubmarine();

	for (;;) {

		if (sub.gas <= 0) {
			SetConsoleCursorPosition(0, 5);
			cout << "Закончилось топливо, игра окончена!";
			return;
		}

		if (kbhit) {
			btn = getch();
		}

		if (btn == MVK_UP) {
			pos_y--;
			SetConsoleCursorPosition(pos_x, pos_y);
		}

		if (btn == MVK_LEFT) {
			pos_x-=30;
			SetConsoleCursorPosition(pos_x, pos_y);
		}

		if (btn == MVK_RIGHT) {
			pos_x+=30;
			SetConsoleCursorPosition(pos_x, pos_y);
		}

		if (btn == MVK_DOWN) {
			pos_y++;
			SetConsoleCursorPosition(pos_x, pos_y);
		}

		if (btn == ENTER) {
			if (pos_x == 30) {
				switch (pos_y) {
				case 0:						//движение вперед
					try {
						GoAhead();
					}
					catch (bool) {
						SetConsoleCursorPosition(0, 5);
						cout << "Закончилось топливо, игра окончена!";
						return;
					}
					
					break;
				case 1:						// движение назад
					try {
						GoBack();
					}
					catch (bool) {
						SetConsoleCursorPosition(0, 5);
						cout << "Закончилось топливо, игра окончена!";
						return;
					}
					break;
				case 2:						// stop
					ShowInfo("stop");
					break;
				}
			}
			else if (pos_x == 60) {
				switch (pos_y) {
				case 0:						//поиск цели
					ShowInfo("поиск цели");
					sub.ShowTargets();
					UpdateConsole();
					break;
				case 1:						// заряд торпеды
					ShowInfo("заряд торпеды");
					sub.ReCharge();
					UpdateConsole();
					break;
				case 2:
					ShowInfo("атака");// атака
					Sleep(2000);
					UpdateConsole();
					sub.Attack(sub.target);
					UpdateConsole();
					break;
				}
			}
		}
	}
}

void GoAhead() {
	if (sub.gas <= 0) {
		throw false;
	}
	ShowInfo("движение вперед");
	Sleep(2000);
	while (!kbhit() && sub.gas > 0) {
		sub.FuelRate();
		sub.x += 5;
		UpdateConsole();
		Sleep(2000);
		if (sub.x == 70) {
			sub.x = 0;
		}
	}
}

void GoBack() {
	if (sub.gas <= 0) {
		throw false;
	}
	ShowInfo("движение назад");
	Sleep(2000);
	while (!kbhit() && sub.gas > 0) {
		sub.FuelRate();
		sub.x -= 5;
		UpdateConsole();
		Sleep(2000);
		if (sub.x == 0) {
			sub.x = 70;
		}
	}
}

void UpdateConsole() {
	system("cls");
	ShowMenu();
	ShowSubmarine();
}

void ShowInfo(string action) {
	string s = action;
	pos_x = 30;
	pos_y = 20;
	SetConsoleCursorPosition(pos_x, pos_y);
	cout << s;
	pos_x = 0;
	pos_y = 2;
	SetConsoleCursorPosition(pos_x, pos_y);
}

void ShowMenu() {
	pos_x = pos_y = 0;
	SetConsoleCursorPosition(pos_x, pos_y);
	cout << "Имя: " << sub.name << endl
		 << "Топливо: " << sub.gas << endl
		 << "Торпеды: " << sub.torpedo;
	pos_x = 30;
	SetConsoleCursorPosition(pos_x, pos_y);
	cout << "Движение вперед";
	pos_y++;
	SetConsoleCursorPosition(pos_x, pos_y);
	cout << "Движение назад";
	pos_y++;
	SetConsoleCursorPosition(pos_x, pos_y);
	cout << "Cтоп";
	pos_x = 60;
	pos_y = 0;
	SetConsoleCursorPosition(pos_x, pos_y);
	cout << "Поиск цели";
	pos_y++;
	SetConsoleCursorPosition(pos_x, pos_y);
	cout << "Зарядить торпеды";
	pos_y++;
	SetConsoleCursorPosition(pos_x, pos_y);
	cout << "Атака";
}

void ShowSubmarine() {
	pos_x = sub.x;
	pos_y = sub.y;
	SetConsoleCursorPosition(pos_x, pos_y);
	cout << "       --------";
	pos_y++;
	SetConsoleCursorPosition(pos_x, pos_y);
	cout << "_\\|/__|        |";
	pos_y++;
	SetConsoleCursorPosition(pos_x, pos_y);
	cout << " /|\\   --------";
	pos_x = 0;
	pos_y = 2;
	SetConsoleCursorPosition(pos_x, pos_y);
}

void SetConsoleCursorPosition(short x_position, short y_position) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _coordPosition = { x_position, y_position };
	SetConsoleCursorPosition(hConsole, _coordPosition);
}