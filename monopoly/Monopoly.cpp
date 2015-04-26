#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>
#include<vector>
#include<iostream>
#include<cstdio>
#include<list>
using namespace std;

#define ID_BUTTON1 1001
#define ID_BUTTON2 1002
#define ID_BUTTON3 1003
#define ID_BUTTON4 1004
#define ID_BUTTON5 1005
#define ID_EDIT1 100
#define ID_EDIT2 101
#define ID_EDIT3 102
#define TIMER 01
#define ID_CHILD 1
#define ID_LIST1 500
#define ID_LIST2 501
#define ID_LIST3 502
#define ID_LIST4 503
#define ID_LIST5 504
#define ID_LIST6 505
#define ID_LIST7 506
#define ID_LIST8 507
#define ID_LIST9 508
#define ID_LIST10 509
#define ID_LIST11 510
#define ID_LIST12 511
#define ID_LIST13 512
#define ID_LIST14 513
#define ID_LIST15 514
#define ID_LIST16 515
#define ID_LIST17 516
#define ID_LIST18 517
#define ID_LIST19 518
#define ID_LIST20 519

#define ID_CHECK1 50
#define ID_CHECK2 51
#define ID_CHECK3 52
#define ID_CHECK4 53
#define ID_COMBO 200
#define ID_COMBO2 201
#define MU_FILE_NEW 2000
#define MU_FILE_OPEN 2001
#define MU_FILE_QUIT 2002

static TCHAR WindowsClass[] = "win32app";
static TCHAR Title[] = "MyWindow";
HINSTANCE hinst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);				// для дочернего окна
HWND add_btn, go_btn, list1, list2, edit, edit_name, edit_salary, edit_num, checkbox1, checkbox2, checkbox3, checkbox4, combo, combo2;
HMENU hMenubar, hMenu;
int window_y_pos;


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow) {	// описание окна
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;		// стиль для отлавливания даблклика
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION)); // стандартная иконка виндовс
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(100, 70, 150));
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
		WS_OVERLAPPEDWINDOW,
		100, 100, 1200, 700,		// х у ширина высота
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

class Cell {
	string name;
	string owner;
	int cost;
	int penalty;

public:

	Cell() {
		name = "";
		owner = "";
		cost = 0;
		penalty = 0;
	}

	void SetName(string s) {
		name = s;
	}

	void SetOwner(string s) {
		owner = s;
	}

	void SetCost(int n) {
		cost = n;
	}

	void SetPenalty(int n) {
		penalty = n;
	}

	int GetCost() {
		return cost;
	}

	int GetPenalty() {
		return penalty;
	}

	string GetName() {
		return name;
	}

	string GetOwner() {
		return owner;
	}

};

class Person {
	string name;
	int money;
public:
	Person() {
		name = "";
		money = 1000;
	}

	void SetName(string s) {
		name = s;
	}

	void SetMoney(int n) {
		money = n;
	}

	string GetName() {
		return name;
	}

	int GetMoney() {
		return money;
	}
};

list<Cell>listbox_arr;
int size = 20;

void SetArr() {
	int id = 500;
	for (int i = 0; i < size; i++, id++) {
		listbox_arr.push_back(new Cell());
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {


	switch (message) {
	case WM_COMMAND:
		if (LOWORD(wParam) == MU_FILE_QUIT) {
			
		}



		break;
	case BN_CLICKED:

		break;

	case WM_CREATE:
		
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;

}


