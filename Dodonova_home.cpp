#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>

#define ID_BUTTON1 1001
#define ID_BUTTON2 1002
#define ID_BUTTON3 1003
#define ID_BUTTON4 1004
#define ID_BUTTON5 1005
#define ID_EDIT1 100
#define ID_EDIT2 101
#define TIMER 01
#define ID_CHILD 1

static TCHAR WindowsClass[] = "win32app";
static TCHAR Title[] = "MyWindow";
HINSTANCE hinst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);				// для дочернего окна
HWND button1, button2, button3, button4, button5, edit1, edit2;
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


//1. Падающие друг за другом кнопки(классная работа)

//void ScreenToClient(HWND hWnd, LPRECT lpRect);
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
//
//	HWND buttons[] = { button2, button3, button4, button5 };
//	int y_pos, f = 0;
//	char s[20];
//	RECT rect;
//	POINT point;
//	switch (message) {
//
//		case WM_COMMAND:
//			case BN_CLICKED:
//				if (LOWORD(wParam) == ID_BUTTON1) {
//					SetTimer(hwnd, TIMER, 500, NULL);
//				}
//			break;
//		case WM_TIMER:
//			for (int i = 0; i < 4; i++) {
//				GetWindowRect(buttons[i], &rect);
//				ScreenToClient(hwnd, &rect);
//				y_pos = rect.top;
//				MoveWindow(buttons[i], 300, y_pos += 20, 100, 20, TRUE);
//
//				if (i == 3 && y_pos >= heigth) {
//					KillTimer(hwnd, TIMER);
//					PostQuitMessage(0);
//				}
//			}
//			break;
//
//		case WM_CREATE:
//		button1 = CreateWindowEx(NULL, "button", "MyButton1", WS_CHILD | WS_VISIBLE, 10, 10, 100, 20, hwnd, (HMENU)ID_BUTTON1, hinst, NULL);
//		button2 = CreateWindowEx(NULL, "button", "MyButton2", WS_CHILD | WS_VISIBLE, 200, -20, 100, 20, hwnd, (HMENU)ID_BUTTON2, hinst, NULL);
//		button3 = CreateWindowEx(NULL, "button", "MyButton3", WS_CHILD | WS_VISIBLE, 200, -60, 100, 20, hwnd, (HMENU)ID_BUTTON3, hinst, NULL);
//		button4 = CreateWindowEx(NULL, "button", "MyButton4", WS_CHILD | WS_VISIBLE, 200, -100, 100, 20, hwnd, (HMENU)ID_BUTTON4, hinst, NULL);
//		button5 = CreateWindowEx(NULL, "button", "MyButton5", WS_CHILD | WS_VISIBLE, 200, -140, 100, 20, hwnd, (HMENU)ID_BUTTON5, hinst, NULL);
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
//}
//
//void ScreenToClient(HWND hWnd, LPRECT lpRect) {
//	POINT LeftTop;
//	POINT RightBottom;
//	LeftTop.x = lpRect->left;
//	LeftTop.y = lpRect->top;
//	ScreenToClient(hWnd, &LeftTop);
//	RightBottom.x = lpRect->right;
//	RightBottom.y = lpRect->bottom;
//	ScreenToClient(hWnd, &RightBottom);
//	SetRect(lpRect, LeftTop.x, LeftTop.y, RightBottom.x, RightBottom.y);
//}


// 2. В центре экрана отобразить окно, содержащее фрагмент текста и кнопки «Выход» и «Далее».
// При нажатии кнопки «Выход» завершить работу, а кнопки «Далее» - текст в окне заменить другим фрагментом,
// а кнопки заменить кнопками «Назад» и «Выход». При нажатии кнопки «Назад» вернуться к исходному состоянию. 

//HWND child_window, exit_btn, next_btn;
//
//int chld_wnd_width = 200, chld_wnd_height = 150, click_count = 0;;
//std::string text = "Hello world!";
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
//
//	switch (message) {
//	case WM_COMMAND:
//		case BN_CLICKED:
//			switch (LOWORD(wParam)){
//				case ID_BUTTON1:
//					PostQuitMessage(0);
//				break;
//				case ID_BUTTON2:
//					click_count++;
//					if (click_count % 2 != 0) {
//						text = "Goodbye world!";
//						SendMessage(edit, WM_SETTEXT, 0, (LPARAM)text.c_str());
//						SetWindowText(next_btn, "Back");
//					}
//					else {
//						text = "Hello world!";
//						SendMessage(edit, WM_SETTEXT, 0, (LPARAM)text.c_str());
//						SetWindowText(next_btn, "Next");
//					}
//
//				break;
//			}
//		break;
//
//	case WM_CREATE:
//		WNDCLASS w;
//		memset(&w, 0, sizeof(WNDCLASS));
//		w.lpfnWndProc = ChildProc;
//		w.hInstance = hinst;
//		w.hbrBackground = CreateSolidBrush(RGB(0, 255, 255));
//		w.lpszClassName = "ChildWClass";
//		w.hCursor = LoadCursor(NULL, IDC_ARROW);
//		RegisterClass(&w);
//
//		child_window = CreateWindowEx(NULL, "ChildWClass", "small_wnd", WS_CHILD | WS_VISIBLE | WS_BORDER, width/2 - chld_wnd_width/2, heigth/2 - chld_wnd_height, chld_wnd_width, chld_wnd_height, hwnd, (HMENU)ID_CHILD, hinst, NULL);
//		edit = CreateWindowEx(NULL, "edit", "", WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 10, 100, 20, child_window, (HMENU)ID_EDIT, hinst, NULL);
//		SendMessage(edit, WM_SETTEXT, 0, (LPARAM)text.c_str());
//		exit_btn = CreateWindowEx(NULL, "button", "Exit", WS_CHILD | WS_VISIBLE, 10, 300, 100, 20, hwnd, (HMENU)ID_BUTTON1, hinst, NULL);
//		next_btn = CreateWindowEx(NULL, "button", "Next", WS_CHILD | WS_VISIBLE, 380, 300, 100, 20, hwnd, (HMENU)ID_BUTTON2, hinst, NULL);
//		break;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//		
//	default:
//		return DefWindowProc(hwnd, message, wParam, lParam);
//	}
//	return 0;
//
//}
//
//LRESULT CALLBACK ChildProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) {			// для дочернего окна
//
//	if (Message == WM_DESTROY) {
//		return 0;
//	}
//	return DefWindowProc(hwnd, Message, wparam, lparam);
//}



// 3. В окне отобразить два однострочных текстовых редактора и кнопку «Обмен». 
// При нажатии кнопки происходит обмен текстовых строк в редакторах и выводится соответствующее сообщение

//std::string text1, text2;
//HWND change_btn;
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
//
//	switch (message) {
//	case WM_COMMAND:
//		case BN_CLICKED:
//			if (LOWORD(wParam) == ID_BUTTON1) {
//				GetWindowText(edit1, (LPSTR)text1.c_str(), 50);
//				GetWindowText(edit2, (LPSTR)text2.c_str(), 50);
//				SendMessage(edit1, WM_SETTEXT, 0, (LPARAM)text2.c_str());
//				SendMessage(edit2, WM_SETTEXT, 0, (LPARAM)text1.c_str());
//				MessageBox(hwnd, "Произошел обмен", "", TRUE);
//			}
//		break;
//
//	case WM_CREATE:
//		edit1 = CreateWindowEx(NULL, "edit", "", WS_CHILD | WS_VISIBLE, 5, heigth/2 - 20, 100, 20, hwnd, (HMENU)ID_EDIT1, hinst, NULL);
//		edit2 = CreateWindowEx(NULL, "edit", "", WS_CHILD | WS_VISIBLE, width - 20 - 100, heigth / 2 - 20, 100, 20, hwnd, (HMENU)ID_EDIT2, hinst, NULL);
//		change_btn = CreateWindowEx(NULL, "button", "Обмен", WS_CHILD | WS_VISIBLE, width/2-50, heigth/2 - 20, 100, 20, hwnd, (HMENU)ID_BUTTON1, hinst, NULL);
//		break;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//		
//	default:
//		return DefWindowProc(hwnd, message, wParam, lParam);
//	}
//	return 0;
//
//}



// 4. В нижней части клиентской области окна отобразить кнопку с надписью «Показать», в верхней части окна – статическую надпись «Введите текст».
// После нажатия на кнопку в средней части окна отображается многострочный редактор с исходным текстом «Нажмите правую клавишу мыши». 
// После нажатия правой клавиши мыши скрыть редактор.

//HWND show_btn;
//std::string text = "Введите текст";
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
//	HDC hdc;
//	PAINTSTRUCT ps;
//
//	switch (message) {
//	case WM_RBUTTONDOWN:
//		DestroyWindow(edit1);
//		break;
//
//	case WM_COMMAND:
//		case BN_CLICKED:
//			if (LOWORD(wParam) == ID_BUTTON1) {
//				edit1 = CreateWindowEx(NULL, "edit", "", WS_CHILD | WS_VISIBLE |ES_MULTILINE, width/2 - 50, 100, 100, 100, hwnd, (HMENU)ID_EDIT1, hinst, NULL);
//				SendMessage(edit1, WM_SETTEXT, 0, (LPARAM)"Нажмите правую клавишу мыши");
//			}
//		break;
//
//	case WM_PAINT:
//		hdc = BeginPaint(hwnd, &ps);
//		TextOut(hdc, 200, 5, text.c_str(), 13);
//		EndPaint(hwnd, &ps);
//		break;
//
//	case WM_CREATE:
//		show_btn = CreateWindowEx(NULL, "button", "Показать", WS_CHILD | WS_VISIBLE, width/2-50, 350, 100, 20, hwnd, (HMENU)ID_BUTTON1, hinst, NULL);
//		break;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//		
//	default:
//		return DefWindowProc(hwnd, message, wParam, lParam);
//	}
//	return 0;
//
//}