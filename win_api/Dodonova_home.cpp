#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>
#include<vector>
#include<iostream>
#include <cstdio>
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
#define ID_CHECK1 50
#define ID_CHECK2 51
#define ID_CHECK3 52
#define ID_CHECK4 53

static TCHAR WindowsClass[] = "win32app";
static TCHAR Title[] = "MyWindow";
HINSTANCE hinst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);				// для дочернего окна
HWND add_btn, go_btn, list1, list2, edit, edit_name, edit_salary, edit_num, checkbox1, checkbox2, checkbox3, checkbox4;
int window_y_pos;
int width = 500, heigth = 500;

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
		100, 100, width, heigth,		// х у ширина высота
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

//1. В клиентской области окна приложения создать 2 списка, первый из которых содержит числа от 1 до 5,
// второй – числа от 200 до 205. При нажатии кнопки «Добавить» в список с фокусом ввода добавить очередное число.

int l = 0, k = 0;
const int size = 5;
int f = -1;
int arr1[size], arr2[size];
char s[20] = {0};

void SetArr() {
	for (int i = 0, k = 200; i < size; i++, k++) {
		arr1[i] = i + 1;
		arr2[i] = k;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	

	switch (message) {
	case WM_COMMAND:
		if (HIWORD(wParam) == LBN_SETFOCUS) {
			switch (LOWORD(wParam)) {
			case ID_LIST1:
				f = 1;
				break;

			case ID_LIST2:
				f = 2;
				break;
			}
		}

	case BN_CLICKED:
		if (LOWORD(wParam) == ID_BUTTON1) {
			if (f == 1) {
				if (l >= size) {
					l = 0;
				}
				_itoa_s(arr1[l], s, 10);
				SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)s);
				l++;
			}
			if(f == 2) {
				if (k >= size) {
					k = 0;
				}
				_itoa_s(arr2[k], s, 10);
				SendMessage(list2, LB_ADDSTRING, 0, (LPARAM)s);
				k++;
			}
		}
		break;

	case WM_CREATE:
		add_btn = CreateWindowEx(NULL, "button", "добавить", WS_CHILD | WS_VISIBLE, 180, 250, 100, 20, hwnd, (HMENU)ID_BUTTON1, hinst, NULL);
		list1 = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox", "", WS_CHILD | WS_VISIBLE | LBS_STANDARD, 50, 150, 100, 300, hwnd, (HMENU)ID_LIST1, hinst, NULL);
		list2 = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox", "", WS_CHILD | WS_VISIBLE | LBS_STANDARD, 300, 150, 100, 300, hwnd, (HMENU)ID_LIST2, hinst, NULL);
		SetArr();
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;

}


//2. На форме разместить 4 элемента Check Box c надписями «Сильный», «Смелый», «Добрый», «Умный».
// При нажатии на кнопку «Добавить» выбранные качества отображаются с использованием MessageBox. 

//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
//	char str[50] = {0};
//	char buf[50];
//	HWND checkboxes[] = { checkbox1, checkbox2, checkbox3, checkbox4 };
//	int size = 4;
//	LRESULT res;
//
//	switch (message) {
//
//	case WM_COMMAND:
//		for (int i = 0; i < size; i++) {
//			res = SendMessage(checkboxes[i], BM_GETCHECK, 0, 0);
//			if (res == BST_CHECKED) {
//				GetWindowText(checkboxes[i], buf, 50);
//				strcat_s(str, sizeof(str), buf);
//				strcat_s(str, " ");
//			}
//		}
//
//		case BN_CLICKED:
//			if (LOWORD(wParam) == ID_BUTTON1) {
//				MessageBox(hwnd, str, "", TRUE);
//			}
//
//		break;
//
//	case WM_CREATE:
//		add_btn = CreateWindowEx(NULL, "button", "добавить", WS_CHILD | WS_VISIBLE, 180, 250, 100, 20, hwnd, (HMENU)ID_BUTTON1, hinst, NULL);
//		checkbox1 = CreateWindowEx(NULL, "button", "Сильный", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 200, 40, 100, 20, hwnd, (HMENU)ID_CHECK1, hinst, NULL);
//		checkbox2 = CreateWindowEx(NULL, "button", "Смелый", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 200, 70, 100, 20, hwnd, (HMENU)ID_CHECK2, hinst, NULL);
//		checkbox3 = CreateWindowEx(NULL, "button", "Добрый", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 200, 100, 100, 20, hwnd, (HMENU)ID_CHECK3, hinst, NULL);
//		checkbox4 = CreateWindowEx(NULL, "button", "Умный", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 200, 130, 100, 20, hwnd, (HMENU)ID_CHECK4, hinst, NULL);
//		break;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//
//	default:
//		return DefWindowProc(hwnd, message, wParam, lParam);
//	}
//
//	return 0;
//
//}



// 3. На форме разместить список строк, однострочный редактор и кнопка «Найти».
// При нажатии на кнопку найти строку из редактора в списке строк.Если найти не удалось, то сообщить об этом.

//string words[] = { "синий", "белый", "красный", "черный", "зеленый", "серый", "розовый", "желтый" };
//int size = 8;
//
//void SetList() {
//	for (int i = 0; i < size; i++) {
//		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)words[i].c_str());
//	}
//}
//
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
//	char str[50];
//
//	switch (message) {
//
//	case WM_COMMAND:
//		if (LOWORD(wParam) == ID_BUTTON1) {
//			SendMessage(edit, WM_GETTEXT, sizeof(str), (LPARAM)str);
//			auto res = SendMessage(list1, LB_SELECTSTRING, 1, (LPARAM)str);
//
//			if (res == -1) {
//				MessageBox(hwnd, "Нет такой строки!", 0, 0);
//			}
//		}
//		break;
//
//	case WM_CREATE:
//		add_btn = CreateWindowEx(NULL, "button", "Найти", WS_CHILD | WS_VISIBLE, 180, 250, 100, 20, hwnd, (HMENU)ID_BUTTON1, hinst, NULL);
//		edit =  CreateWindowEx(NULL, "edit", "", WS_CHILD | WS_VISIBLE, 180, 200, 100, 20, hwnd, (HMENU)ID_EDIT1, hinst, NULL);
//		list1 = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox", "", WS_CHILD | WS_VISIBLE | LBS_STANDARD, 50, 150, 100, 300, hwnd, (HMENU)ID_LIST1, hinst, NULL);
//		SetList();
//		break;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//
//	default:
//		return DefWindowProc(hwnd, message, wParam, lParam);
//	}
//
//	return 0;
//
//}



