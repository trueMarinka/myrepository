#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>
#include<vector>
#include<iostream>
#include<cstdio>
#include<time.h>
#include <io.h>
#include<map>

#pragma comment(lib,"Winmm.lib")
using namespace std;
static TCHAR WindowsClass[] = "win32app";
static TCHAR Title[] = "MyWindow";
HINSTANCE hinst;

#define ID_1_MONEY_EDIT 50
#define ID_2_MONEY_EDIT 51
#define ID_1_NEWS_EDIT 52
#define ID_2_NEWS_EDIT 53
#define ID_SOUND 7001
#define ID_BRAS 102
#define ID_REZ 103
#define ID_PLAYER1 104
#define ID_PLAYER2 105


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND btnBras, editRez, checkbox;


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow) {	// описание окна
	srand(time(NULL));
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;		// стиль для отлавливания даблклика
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION)); // стандартная иконка виндовс
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.hbrBackground = CreateSolidBrush(RGB(100, 70, 150));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex)) {	// если не удалось создать окно
		MessageBox(NULL, "CAll failed!", "MyWindow", NULL);
		return 1;
	}

	hinst = hinstance;
	HWND hwnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		125, 10, 1100, 700,		// х у ширина высота
		NULL, NULL,
		hinst, NULL);

	if (!hwnd) {
		MessageBox(NULL, "CAll failed!", "MyWindow", NULL);
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

// координаты фишек в ячейках:
int pos_x_user_in_cell1[] = { 950, 770, 570, 390, 190, 25, 25, 25, 25, 190, 390, 570, 770, 950, 950, 950 };
int pos_x_user_in_cell2[] = { 1015, 835, 635, 455, 255, 90, 90, 90, 90, 255, 455, 635, 835, 1015, 1015, 1015 };
int pos_y_user_in_cell[] = { 600, 600, 600, 600, 600, 600, 440, 250, 10, 10, 10, 10, 10, 10, 250, 440 };

// координаты editbox в ячейках:
int edit_pos_x[] = { 0, 830, 645, 455, 255, 0, 75, 75, 0, 275, 455, 635, 835, 0, 1008, 1008 };
int edit_pos_y[] = { 0, 555, 550, 559, 555, 0, 373, 196, 0, 87, 87, 87, 85, 0, 214, 374 };

int click = 1;
HANDLE hBitmap, hOldBitmap, hBitmapP1, hBitmapP2, hBitShtrP1, hBitShtrP2, hBitPropP1, hBitPropP2;

class Cell {
	string type;
	string owner;
	int sum;
	int penalty;

public:
	HWND edit;
	Cell() {
		type = "";
		owner = "";
		sum = 0;
		penalty = 0;
	}

	Cell(string _type, int _sum, int _penalty, string _owner = "") {
		type = _type;
		owner = _owner;
		sum = _sum;
		penalty = _penalty;
		
	}

	void SetEdit(HWND hwnd, int id, int _x, int _y) {
		edit = CreateWindowEx(NULL, "edit", "нет", WS_CHILD | WS_VISIBLE, _x, _y, 60, 20, hwnd, (HMENU)id, hinst, NULL);
	}

	void SetOwner(string s) {
		owner = s;
	}

	void SetType(string _type) {
		type = _type;
	}

	int GetCost() {
		return sum;
	}

	int GetPenalty() {
		return penalty;
	}

	string GetOwner() {
		return owner;
	}
};

class MessageCell : public Cell {
public:
	int i = 0;
	map <string, int> message;
	map<string, int>::iterator it;

	string Message_text() {
		it = message.begin();
		if (i > 5) {
			i = 0;
		}
		std::advance(it, i);
		return it->first;
	}

	int Message_sum() {
		it = message.begin();
		if (i > 5) {
			i = 0;
		}
		std::advance(it, i);
		i++;
		return it->second;
	}
};

class Player {
public:
	string name;
	int id;
	int money;
	int cur_cell;
	bool miss_turn;
	bool img_change;
	HWND money_edit;
	HWND news_edit;
	HWND fishka;
	string linus_quotes[4];

	Player(string _name, int _id) {
		img_change = false;
		name = _name;
		money = 100;
		cur_cell = 0;
		id = _id;
		miss_turn = false;
		SetLlinusQuote();
		hBitmapP1 = LoadImage(NULL, "pic1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitmapP2 = LoadImage(NULL, "pic_2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitPropP1 = LoadImage(NULL, "picProp1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitPropP2 = LoadImage(NULL, "picProp2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitShtrP1 = LoadImage(NULL, "picShtr1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); 
		hBitShtrP2 = LoadImage(NULL, "picShtr2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	void SetLlinusQuote() {
		linus_quotes[0] = "Моё имя Линус, и я ваш Бог";
		linus_quotes[1] = "Microsoft — не есть зло, просто у них по-настоящему паршивые операционные системы.";
		linus_quotes[2] = "Интеллект — это способность избегать выполнения работы, но так, чтобы она при этом была сделана";
		linus_quotes[3] = "Философия Линукса: \"Смейся в лицо опасности\". Ой. Не то. \"Сделай сам\". Да, правильно.";
	}

	string GetLinusQuote() {
		int random = rand() % 4;
		return linus_quotes[random];
	}

	void SetEdits(HWND window, int money_x, int money_y, int news_x, int news_y, int ID1, int ID2) {
		money_edit = CreateWindowEx(NULL, "edit", "100", WS_CHILD | WS_VISIBLE | ES_READONLY, money_x, money_y, 60, 20, window, (HMENU)ID1, hinst, NULL);
		news_edit = CreateWindowEx(NULL, "edit", "Давай начнем!", WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_READONLY, news_x, news_y, 180, 80, window, (HMENU)ID2, hinst, NULL);
	}

	void Fishka(HWND window, int x, int y, int ID, string name) {
		fishka = CreateWindowEx(NULL, "button", (LPSTR)name.c_str(), WS_CHILD | WS_VISIBLE | BS_BITMAP, x, y, 60, 60, window, (HMENU)ID, hinst, NULL);
		SetNativeImage();
	}

	void SetNativeImage() {
		if (id == 1) {
			SendMessage(fishka, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmapP1);
		}
		if (id == 2) {
			SendMessage(fishka, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmapP2);
		}
		img_change = false;
	}

	void SetImage(HANDLE img) {
		SendMessage(fishka, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img);
		img_change = true;
	}

	void Move(int cell) {
		if (id == 1) {
			MoveWindow(fishka, pos_x_user_in_cell1[cell], pos_y_user_in_cell[cell], 60, 60, TRUE);
		}
		if (id == 2) {
			MoveWindow(fishka, pos_x_user_in_cell2[cell], pos_y_user_in_cell[cell], 60, 60, TRUE);
		}
		cur_cell = cell;
	}

	void UpdateMoney(int sum) {
		money += sum;
		string s;
		s = std::to_string(money);
		SendMessage(money_edit, WM_SETTEXT, 0, (LPARAM)s.c_str());
	}

	void UpdateNews(string s) {
		SendMessage(news_edit, WM_SETTEXT, 0, (LPARAM)s.c_str());
	}

	void PirateSound(int &click) {
		if (click == 1) {
			PlaySound("start.wav", NULL, SND_ASYNC | SND_FILENAME);
			click = 2;
		}
		else if (click == 2) {
			PlaySound(NULL, NULL, SND_FILENAME);
			click = 1;
		}
	}

	void PrisonSound() {
		PlaySound("Prop.wav", NULL, SND_ASYNC | SND_FILENAME);
	}

	void ChanceSound() {
		PlaySound("good.wav", NULL, SND_ASYNC | SND_FILENAME);
	}

	void BugSound() {
		PlaySound("bad.wav", NULL, SND_ASYNC | SND_FILENAME);
	}

	void BuySound() {
		PlaySound("buy.wav", NULL, SND_ASYNC | SND_FILENAME);
	}

	void PenaltySound() {
		PlaySound("shtraf.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
};

const int player1_money_x = 240;			
const int player1_money_y = 430;
const int player2_money_x = 825;
const int player2_money_y = 420;

const int player1_news_x = 180;
const int player1_news_y = 290;
const int player2_news_x = 733;
const int player2_news_y = 290;

vector<Cell> cells;
MessageCell chance, bug;
Player user1("игрок1", 1);
Player user2("игрок2", 2);
void SetCells(HWND hwnd);
void SetPlayers(HWND hwnd);
int NextCell(Player &player, int brosok);
void CheckCell(HWND win, Player &pl, int cell);
void WhoFirst();
void ChangeTurn(Player &p);
void DoSome(HWND wind, Player &p, int cell);
void GameOver(HWND wind, string name);

bool sound = true;
int brosok, next_cell, turn;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hDC, hCompatibleDC;
	PAINTSTRUCT PaintStruct;
	RECT Rect;
	BITMAP Bitmap;
	
	switch (message) {
	case WM_COMMAND:

		if (user1.money < 0) {
			GameOver(hwnd, user2.name);
		}
		if (user2.money < 0) {
			GameOver(hwnd, user1.name);
		}

		if (LOWORD(wParam) == ID_SOUND) {                          //Включение/выключение звука
			auto res = SendMessage(checkbox, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED){
				sound=true;}
			if (res == BST_UNCHECKED){
				sound=false;}
		}

		if (LOWORD(wParam) == ID_BRAS) {			// бросаем кубик

			if (sound) {
				PlaySound("kosti.wav", NULL, SND_ASYNC | SND_FILENAME);
			}

			brosok = rand() % 6 + 1;
			string s = std::to_string(brosok);
			SendMessage(editRez, WM_SETTEXT, 0, (LPARAM)s.c_str());
			Sleep(1000);


			if (turn == 1) {						// перемещаем фишку
				if (user1.miss_turn) {
					next_cell = NextCell(user2, brosok);
					user2.Move(next_cell);
					CheckCell(hwnd, user2, user2.cur_cell);
					user1.miss_turn = false;
				}
				else {
					if (user1.img_change) {
						user1.SetNativeImage();
					}
					next_cell = NextCell(user1, brosok);
					user1.Move(next_cell);
					CheckCell(hwnd, user1, user1.cur_cell);
				}
			}
			else {
				if (user2.miss_turn) {
					next_cell = NextCell(user1, brosok);
					user1.Move(next_cell);
					CheckCell(hwnd, user1, user1.cur_cell);
					user2.miss_turn = false;
				}
				else {
					if (user2.img_change) {
						user2.SetNativeImage();
					}
					next_cell = NextCell(user2, brosok);
					user2.Move(next_cell);
					CheckCell(hwnd, user2, user2.cur_cell);
				}
			}
		}

		if (LOWORD(wParam) == ID_PLAYER1) {
			if (sound) {
				user1.PirateSound(click);
			}
		}

		if (LOWORD(wParam) == ID_PLAYER2) {
			MessageBox(hwnd, user2.GetLinusQuote().c_str(), "Цитаты", FALSE);
		}

		break;
		
	case WM_CREATE:
		hBitmap = LoadImage(NULL, "picture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		btnBras = CreateWindowEx(NULL, "button", "Бросок", WS_CHILD | WS_VISIBLE, 510, 215, 60, 20, hwnd, (HMENU)ID_BRAS, hinst, NULL);
		editRez = CreateWindowEx(NULL, "edit", "0", WS_CHILD | WS_VISIBLE, 580, 215, 15, 20, hwnd, (HMENU)ID_REZ, hinst, NULL);
		checkbox = CreateWindow("button", "Звук", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 800, 470, 55, 14, hwnd, (HMENU)ID_SOUND, hinst, NULL);
		SendMessage(checkbox, BM_SETCHECK, BST_CHECKED, 0);
		SetCells(hwnd);
		SetPlayers(hwnd);
		WhoFirst();
		break;
			
	case WM_PAINT:
		//*************ничего интересного, прорисовка фона*****************
		hDC = BeginPaint(hwnd, &PaintStruct);
		GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
		hCompatibleDC = CreateCompatibleDC(hDC);
		hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
		GetClientRect(hwnd, &Rect);
		StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth,
			Bitmap.bmHeight, SRCCOPY);
		SelectObject(hCompatibleDC, hOldBitmap);
		DeleteDC(hCompatibleDC);
		EndPaint(hwnd, &PaintStruct);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
		
	return 0;
		
}

void GameOver(HWND wind, string name) {
	string s = "Выиграл " + name + "!";
	MessageBox(wind, s.c_str(), "", FALSE);
	PostQuitMessage(0);
}

void CheckCell(HWND win, Player &pl, int cell) {
	switch (cell) {
	case 0:	
		// выдача денег за прохождение круга уже описана в ф-и NextCell
		break;
	case 5:		// шанс
		if (sound) {
			pl.ChanceSound();
		}
		pl.UpdateNews(chance.Message_text());
		pl.UpdateMoney(chance.Message_sum());
		break;
	case 8:		//тюрьма
		if (sound) {
			pl.PrisonSound();
		}
		if (pl.id == 1) {
			pl.SetImage(hBitPropP1);
		}
		else if (pl.id == 2) {
			pl.SetImage(hBitPropP2);
		}
		pl.UpdateNews("Посиди, подумай!");
		pl.miss_turn = true;
		break;
	case 13:	// баг	
		if (sound) {
			pl.BugSound();
		}
		pl.UpdateNews(bug.Message_text());
		pl.UpdateMoney(bug.Message_sum());
		break;
	default:
		DoSome(win, pl, cell);
		break;
	}
	ChangeTurn(pl);
}

void DoSome(HWND wind, Player &p, int cell) {
	if (cells[cell].GetOwner() != "") {		// есть владелец
		if (cells[cell].GetOwner() != p.name) {		// владелец не я
			if (p.id == 1) {
				p.SetImage(hBitShtrP1);
			}
			else {
				p.SetImage(hBitShtrP2);
			}
			if (sound) {
				p.PenaltySound();
			}
			p.UpdateMoney(-cells[cell].GetPenalty());	// плачу штраф
			p.UpdateNews("Заплатил штраф!");
			
			if (p.id == 1) {
				user2.UpdateMoney(cells[cell].GetPenalty());
				user2.UpdateNews("Денежки капают!");
			}
			else {
				user1.UpdateMoney(cells[cell].GetPenalty());
				user1.UpdateNews("Денежки капают!");
			}
		}
	}
	else {
		auto res = MessageBox(wind, "Хотите купить?", "", TRUE);
		if (res == IDOK) {		//нажали "ок"
			if (p.money >= cells[cell].GetCost()) {		// хватает денег
				if (sound) {
					p.BuySound();
				}
				cells[cell].SetOwner(p.name);
				SendMessage(cells[cell].edit, WM_SETTEXT, 0, (LPARAM)p.name.c_str());
				p.UpdateMoney(-cells[cell].GetCost());
				p.UpdateNews("Новая покупка!");
			}
			else {
				MessageBox(wind, "Не достаточно денег:(", "", FALSE);
			}
		}
	}
}

void ChangeTurn(Player &p) {
	if (p.id == 1) {
		turn = 2;
	}
	else if (p.id == 2) {
		turn = 1;
	}
}

void WhoFirst() {
	int t = rand() % 2;
	if (t) {
		turn = 2;
	}
	else {
		turn = 1;
	}
}

int NextCell(Player &player, int brosok) {
	int n;
	if (player.cur_cell + brosok >= 16) {
		n = (player.cur_cell + brosok) - 16;
		player.UpdateMoney(cells[0].GetCost());		// выдача денег за прохождение круга
		player.UpdateNews("За прохождение круга получи 50$");
	}
	else {
		n = player.cur_cell + brosok;
	}
	return n;
}

void SetPlayers(HWND hwnd) {
	user1.SetEdits(hwnd, player1_money_x, player1_money_y, player1_news_x, player1_news_y, ID_1_MONEY_EDIT, ID_1_NEWS_EDIT);
	user1.Fishka(hwnd, 945, 600, ID_PLAYER1, "игрок1");
	user2.SetEdits(hwnd, player2_money_x, player2_money_y, player2_news_x, player2_news_y, ID_2_MONEY_EDIT, ID_2_NEWS_EDIT);
	user2.Fishka(hwnd, 1015, 600, ID_PLAYER2, "игрок2");
}

void SetCells(HWND hwnd) {
	chance.SetType("Chance");
	chance.message["Ваш старый умирающий Macbook, оставил Вам наследство! Получи 50$"] = 50;
	chance.message["Вы получили грант на разработку ПО под расческу для усов! Получи 20$"] = 20;
	chance.message["Ваш IBM 3 на 27% состоит из золота! Получи 30$"] = 30;
	chance.message["Вы получили нобелевскую премию за вклад в развитие игры МОНОПОЛИЯ! Получи 25$"] = 25;
	chance.message["Вы никогда не платили за лицензионное ПО. За наглость получи 15$"] = 15;
	chance.message["Вы написали приложение без единого бага!!! За хорошую фантазию 40$"] = 40;

	bug.SetType("bug");
	bug.message["Вы наконец решили заменить шариковую мышку! Новая мышь -10$"] = -10 ;
	bug.message["Работая со сложным кодом, Вы вывихнули  кисть руки! Лечение -20$"] = -20;
	bug.message["Вы пили пиво и меняли пароли! Восстановление системы -25$"] = -25;
	bug.message["Вы написали крутую хакерскую программу! Решение суда: штраф -30$"] = -30;
	bug.message["Никогда, никогда не пейте кофе над ноутбуком! Новый ноут -40$"] = -40;
	bug.message["В казино вы всегда ставили на 0 или 1! Плохая система -50$"] = -50;

	cells.push_back(*new Cell("Go", 50, 0));
	cells.push_back(*new Cell("Brend", 60, 10));
	cells.push_back(*new Cell("Brend", 100, 20));
	cells.push_back(*new Cell("Brend", 60, 10));
	cells.push_back(*new Cell("Brend", 120, 20));
	cells.push_back(chance);
	cells.push_back(*new Cell("Brend", 80, 10));
	cells.push_back(*new Cell("Brend", 150, 25));
	cells.push_back(*new Cell("Prison", 0, 0));
	cells.push_back(*new Cell("Brend", 220, 50));
	cells.push_back(*new Cell("Brend", 120, 20));
	cells.push_back(*new Cell("Brend", 100, 15));
	cells.push_back(*new Cell("Brend", 80, 10));
	cells.push_back(bug);
	cells.push_back(*new Cell("Brend", 160, 30));
	cells.push_back(*new Cell("Brend", 200, 35));

	// создаем edit в каждой ячейке кроме угловых в заданных координатах
	for (int i = 0; i < cells.size(); i++) {
		if (i == 0 || i == 5 || i == 8 || i == 13) {
			continue;
		}
		cells[i].SetEdit(hwnd, i, edit_pos_x[i], edit_pos_y[i]);
	}
}


