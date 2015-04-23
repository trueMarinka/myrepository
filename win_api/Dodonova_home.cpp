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
#define ID_CHECK1 50
#define ID_CHECK2 51
#define ID_CHECK3 52
#define ID_CHECK4 53
#define ID_COMBO 200
#define ID_COMBO2 201

static TCHAR WindowsClass[] = "win32app";
static TCHAR Title[] = "MyWindow";
HINSTANCE hinst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);				// для дочернего окна
HWND add_btn, go_btn, list1, list2, edit, edit_name, edit_salary, edit_num, checkbox1, checkbox2, checkbox3, checkbox4, combo, combo2;
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


// Игра "Убить врага"

char what[20], where[20], result[20];
int arm[] = { 20, 10, 5 }, leg[] = { 30, 20, 10 };
int death = 0, line, line1;

void Update(HWND arr[], int size) {
	for (int i = 0; i < size; i++) {
		if (SendMessage(arr[i], BM_GETCHECK, 0, 0) == 1) {
			SendMessage(arr[i], BM_SETCHECK, 0, 0);
		}
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HWND enemy[] = { checkbox1, checkbox2, checkbox3 };
	switch (message) {
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_COMBO && HIWORD(wParam) == CBN_SELENDOK) {
			line = SendMessage(combo, CB_GETCURSEL, 0, 0);
			SendMessage(combo, CB_GETLBTEXT, line, (LPARAM)what);
		}

		if (LOWORD(wParam) == ID_COMBO2 && HIWORD(wParam) == CBN_SELENDOK) {
			line1 = SendMessage(combo2, CB_GETCURSEL, 0, 0);
			SendMessage(combo2, CB_GETLBTEXT, line1, (LPARAM)where);
		}

		if (LOWORD(wParam) == ID_BUTTON1) {
			memset(result, 0, sizeof(result));				// обнуляю результат
			strcat_s(result, what);
			strcat_s(result, where);
			SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)result);
			if (line == 0) {
				death += arm[line1];
			}
			if (line == 1) {
				death += leg[line1];
			}
			Update(enemy, 3);

			switch (line1) {
			case 0:
				SendMessage(checkbox1, BM_SETCHECK, 1, 0);
				break;
			case 1:
				SendMessage(checkbox2, BM_SETCHECK, 1, 0);
				break;
			case 2:
				SendMessage(checkbox3, BM_SETCHECK, 1, 0);
				break;
			}
			if (death >= 100) {
				death = 100;
				string s = "Смерть: " + std::to_string(death) + "%";
				SendMessage(edit, WM_SETTEXT, 0, (LPARAM)s.c_str());
				MessageBox(hwnd,  "Враг убит!", "", TRUE);
				Update(enemy, 3);
				death = 0;
			}
			string s = "Смерть: " + std::to_string(death) + "%";
			SendMessage(edit, WM_SETTEXT, 0, (LPARAM)s.c_str());
			
		}
		break;

	case WM_CREATE:
		combo = CreateWindowEx(WS_EX_CLIENTEDGE, "combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 30, 100, 100, 150, hwnd, (HMENU)ID_COMBO, hinst, NULL);
		combo2 = CreateWindowEx(WS_EX_CLIENTEDGE, "combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 30, 180, 100, 150, hwnd, (HMENU)ID_COMBO2, hinst, NULL);
		SendMessage(combo, WM_SETTEXT, 0, (LPARAM) "ЧЕМ");
		SendMessage(combo, CB_ADDSTRING, 0, (LPARAM) "рукой");
		SendMessage(combo, CB_ADDSTRING, 0, (LPARAM) "ногой");

		SendMessage(combo2, WM_SETTEXT, 0, (LPARAM) "КУДА");
		SendMessage(combo2, CB_ADDSTRING, 0, (LPARAM) " в голову");
		SendMessage(combo2, CB_ADDSTRING, 0, (LPARAM) " в живот");
		SendMessage(combo2, CB_ADDSTRING, 0, (LPARAM) " в ноги");

		add_btn = CreateWindowEx(NULL, "button", "УДАР", WS_CHILD | WS_VISIBLE, 30, 270, 100, 50, hwnd, (HMENU)ID_BUTTON1, hinst, NULL);
		list1 = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox", "", WS_CHILD | WS_VISIBLE, 150, 100, 120, 300, hwnd, (HMENU)ID_LIST1, hinst, NULL);
		checkbox1 = CreateWindowEx(NULL, "button", "голова", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 350, 200, 100, 20, hwnd, (HMENU)ID_CHECK1, hinst, NULL);
		checkbox2 = CreateWindowEx(NULL, "button", "живот", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 350, 230, 100, 20, hwnd, (HMENU)ID_CHECK2, hinst, NULL);
		checkbox3 = CreateWindowEx(NULL, "button", "ноги", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 350, 260, 100, 20, hwnd, (HMENU)ID_CHECK3, hinst, NULL);
		edit = CreateWindowEx(NULL, "edit", "Смерть: ", WS_CHILD | WS_VISIBLE | ES_READONLY, 350, 350, 100, 20, hwnd, (HMENU)ID_EDIT1, hinst, NULL);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;

}

//###########################################################################################################


//1. Комбинированный список заполнить произвольными различными строками. Рядом расположить кнопку «Вниз». 
// Если выбрать строку и нажать кнопку, то эта строка должна переместиться вниз на одну позицию в списке.
// Если эта строка уже последняя в списке, то сообщить об этом и заблокировать кнопку. 

//string words[] = { "Побег из Шоушенка", "Зеленая миля", "Форрест Гамп", "Список Шиндлера", "1+1", "Король Лев", "Начало", "Леон", "Интерстеллар", "Бойцовский клуб" };
//void SetList(HWND list, int size) {
//	for (int i = 0; i < size; i++) {
//		SendMessage(list, CB_ADDSTRING, 0, (LPARAM)words[i].c_str());
//	}
//}
//int size = 10,  cur_sel;
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
//	string str, tmp;
//		
//	switch (message) {
//	case WM_COMMAND:
//		if (LOWORD(wParam) == ID_COMBO && HIWORD(wParam) == CBN_SELENDOK) {
//			cur_sel = SendMessage(combo, CB_GETCURSEL, 0, 0);
//		}
//	
//		if (LOWORD(wParam) == ID_BUTTON1) {
//			int length = SendMessage(combo, CB_GETCOUNT, 0, 0);
//			if (cur_sel == length - 1) {
//				MessageBox(hwnd, "Это последняя строка!", "", TRUE);
//			}
//			else {
//				SendMessage(combo, CB_GETLBTEXT, cur_sel + 1, (LPARAM)tmp.c_str());
//				SendMessage(combo, CB_GETLBTEXT, cur_sel, (LPARAM)str.c_str());
//
//				SendMessage(combo, CB_DELETESTRING, cur_sel, 0);
//				SendMessage(combo, CB_INSERTSTRING, cur_sel + 1, (LPARAM)str.c_str());
//			}
//		}
//	
//		break;
//	case BN_CLICKED:
//	
//		break;
//		
//	case WM_CREATE:
//		combo = CreateWindowEx(WS_EX_CLIENTEDGE, "combobox", "", WS_CHILD | WS_VISIBLE, 30, 100, 200, 300, hwnd, (HMENU)ID_COMBO, hinst, NULL);
//		SetList(combo, size);
//				
//		add_btn = CreateWindowEx(NULL, "button", "Вниз", WS_CHILD | WS_VISIBLE, 300, 270, 100, 20, hwnd, (HMENU)ID_BUTTON1, hinst, NULL);
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

//######################################################################################################################################

//2. Отобразить комбинированный список, содержащий названия специальностей, однострочный редактор с надписью «Фамилия»
// и кнопку «Записать». При нажатии кнопки конкатенация строки из редактора и названия выбранной специальности 
// записывается в список строк.  

//string jobs[] = { "продавец", "менеджер", "сварщик", "программист", "дизайнер", "администратор", "рекламщик", "копирайтер", "верстальщик", "секретарь" };
//int size = 10, cur_sel;
//
//void SetList(HWND list) {
//	for (int i = 0; i < size; i++) {
//		SendMessage(list, CB_ADDSTRING, 0, (LPARAM)jobs[i].c_str());
//	}
//}
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
//	char str[20], name[20], result[20];
//	HDC hdc;
//	PAINTSTRUCT ps;
//
//	switch (message) {
//	case WM_COMMAND:
//		if (LOWORD(wParam) == ID_COMBO && HIWORD(wParam) == CBN_SELENDOK) {
//			cur_sel = SendMessage(combo, CB_GETCURSEL, 0, 0);
//		}
//
//		if (LOWORD(wParam) == ID_BUTTON1) {
//			SendMessage(combo, CB_GETLBTEXT, cur_sel, (LPARAM)str);
//			SendMessage(edit, WM_GETTEXT, 20, (LPARAM)name);
//			if (name[0] == 0) {
//				MessageBox(hwnd, "Нет фамилии!", "", TRUE);
//			}
//			else {
//				memset(result, 0, sizeof(result));
//				strcat_s(result, name);
//				strcat_s(result, " ");
//				strcat_s(result, str);
//				SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)result);
//			}
//		}
//
//		break;
//	case WM_PAINT:
//		hdc = BeginPaint(hwnd, &ps);
//		TextOut(hdc, 190, 80, "Фамилия:", 8);
//		break;
//
//	case WM_CREATE:
//		combo = CreateWindowEx(WS_EX_CLIENTEDGE, "combobox", "", WS_CHILD | WS_VISIBLE, 30, 100, 150, 200, hwnd, (HMENU)ID_COMBO, hinst, NULL);
//		edit = CreateWindowEx(NULL, "edit", "", WS_CHILD | WS_VISIBLE, 190, 100, 100, 20, hwnd, (HMENU)ID_EDIT1, hinst, NULL);
//		add_btn = CreateWindowEx(NULL, "button", "Записать", WS_CHILD | WS_VISIBLE, 190, 270, 100, 20, hwnd, (HMENU)ID_BUTTON1, hinst, NULL);
//		list1 = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox", "name_list", WS_CHILD | WS_VISIBLE, 300, 100, 150, 195, hwnd, (HMENU)ID_LIST1, hinst, NULL);
//		SetList(combo);
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