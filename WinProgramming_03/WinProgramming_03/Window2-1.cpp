#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window";
constexpr int WINDOW_WIDTH = 700;
constexpr int WINDOW_HEIGHT = 650;
LRESULT CALLBACK WndProc2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND Window;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	srand(time(NULL));
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc2;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	Window = CreateWindow(lpszClass, L"windows program 1-1", WS_CAPTION | WS_BORDER | WS_SYSMENU,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(Window, nCmdShow);
	UpdateWindow(Window);// WM_PAINT

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc2(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR lpOut[25];
	int x = 0, y = 0;

	RECT LT_rect{ 0,0,WINDOW_WIDTH / 3,WINDOW_HEIGHT / 3 };
	RECT RT_rect{ 2 * WINDOW_WIDTH / 3,0,WINDOW_WIDTH,WINDOW_HEIGHT / 3 };
	RECT LB_rect{ 0,2 * WINDOW_HEIGHT / 3,WINDOW_WIDTH / 3,WINDOW_HEIGHT };
	RECT RB_rect{ 2 * WINDOW_WIDTH / 3,2 * WINDOW_HEIGHT / 3,WINDOW_WIDTH,WINDOW_HEIGHT };
	RECT CM_rect{ WINDOW_WIDTH / 3,WINDOW_HEIGHT / 3,2 * WINDOW_WIDTH / 3,2 * WINDOW_HEIGHT / 3 };

	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		wsprintf(lpOut, L"Left-Top (%d, %d)", x, y);
		TextOut(hdc, 0, 0, lpOut, lstrlen(lpOut));

		SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		wsprintf(lpOut, L"Right-Top (%d, %d)", WINDOW_WIDTH, 0);
		TextOut(hdc, WINDOW_WIDTH-130, 0, lpOut, lstrlen(lpOut));

		SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		wsprintf(lpOut, L"Left-Bot (%d, %d)", 0, WINDOW_HEIGHT);
		TextOut(hdc, 0, WINDOW_HEIGHT-55, lpOut, lstrlen(lpOut));

		SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		wsprintf(lpOut, L"Right-Bot (%d, %d)", WINDOW_WIDTH, WINDOW_HEIGHT);
		TextOut(hdc, WINDOW_WIDTH-144, WINDOW_HEIGHT-55, lpOut, lstrlen(lpOut));

		SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		wsprintf(lpOut, L"Center-Mid (%d, %d)", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		TextOut(hdc, (WINDOW_WIDTH / 2)-60, (WINDOW_HEIGHT / 2)-15, lpOut, lstrlen(lpOut));

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}