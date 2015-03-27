#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>

static TCHAR WindowsClass[] = "win32app"; 
static TCHAR Title[] = "MyWindow";
HINSTANCE hinst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int window_y_pos;

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow) {	// �������� ����
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;		// ����� ��� ������������ ���������
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION)); // ����������� ������ �������
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(100, 70, 150));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex)) {	// ���� �� ������� ������� ����
		MessageBox(NULL, "CAll failed!", "MyWindow", NULL);
		return 1;
	}

	hinst = hinstance;
	HWND hwnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500,		// � � ������ ������
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

//1. ����� �������� ������ ����� ������ � ���������� ������� ���� ���� �������� ������������ �� ���������.
// ������� ����� ������� ���������� ��������.

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {

	case WM_LBUTTONDBLCLK:
		window_y_pos = 100;
		SetTimer(hwnd, 1, 500, NULL);
		break;

	case WM_TIMER:
		MoveWindow(hwnd, 100, window_y_pos -= 5, 500, 500, TRUE);

		if (window_y_pos < 10) {
			window_y_pos = 100;
		}
		break;

	case WM_KEYDOWN:
		KillTimer(hwnd, 1);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
//######################################################################


// 2. ������ ������ ������� �� ���������� ������� ���� �������� � ��������� ������� �� ������� ����.
// ������ ��������� ������� ����� �������� ������ ����. ������� ����� ������ ������� ���������� �������� �������.
//
//int width = 500, heigth = 500;
//bool resize = false;
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
//	switch (message) {
//	case WM_RBUTTONDOWN:
//		resize = true;
//		break;
//
//	case WM_CHAR:
//		if (resize) {
//			if (wParam > 47 && wParam < 58) {
//				width = heigth -= 5;
//				MoveWindow(hwnd, 100, 100, width, heigth, TRUE);
//
//				if (width == 100) {
//					width = heigth = 500;
//					MoveWindow(hwnd, 100, 100, width, heigth, TRUE);
//				}
//			}
//			else {
//				resize = false;
//				width = heigth = 500;
//				MoveWindow(hwnd, 100, 100, width, heigth, TRUE);
//			}
//		}
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
//}
//#########################################################################


//3. ������ ������ ������� �� ���������� ������� ���� �������� � ��������� ��� �������� (���������� � 2 ����). 
// ������� ����� ������� ���������� �������� �������.

//int width = 500, heigth = 500;
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
//	switch (message) {
//	case WM_RBUTTONDOWN:
//		MoveWindow(hwnd, 100, 100, width/2, heigth/2, TRUE);
//		break;
//
//	case WM_KEYDOWN:
//		MoveWindow(hwnd, 100, 100, width, heigth, TRUE);
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
//}
//####################################################################################


//4. ����������� ���� � ������� �������� ���� �������� � ��������� �������������� �������� ��������� ����.
// ������� ����� ����� �� ������� �QWER..� ���������� ���� � ������ ������� ���� ������.

//int width = 500, heigth = 500, pos_x, pos_y, screen_width;
//char s[20];
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
//	FLASHWINFO pf;
//	pf.cbSize = sizeof(FLASHWINFO);
//	pf.hwnd = hwnd;
//	pf.dwFlags = FLASHW_ALL;
//	pf.uCount = 50;
//	pf.dwTimeout = 0;
//
//	HDC dc = GetDC(GetDesktopWindow());
//	screen_width = GetDeviceCaps(dc, HORZRES);		// ����� ������ ������
//	pos_x = screen_width - width;
//
//	switch (message) {
//	case WM_MOUSEMOVE:
//		pos_y = HIWORD(lParam);
//		if (pos_y < heigth/2) {
//			FlashWindowEx(&pf);
//		}
//		break;
//
//	case WM_CHAR:
//		if (wParam == 'q' || wParam == 'w' || wParam == 'e' || wParam == 'r' || wParam == 't' || wParam == 'y' || wParam == 'u' || wParam == 'i' || wParam == 'o' || wParam == 'p') {
//			MoveWindow(hwnd, pos_x, 0, width, heigth, TRUE);
//		}
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
//}