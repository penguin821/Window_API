#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window";
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
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
	Window = CreateWindow(lpszClass, L"windows program 1-1", WS_OVERLAPPEDWINDOW,
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
	int x = rand() % 701, y = rand() % 501, N = rand() % 10, count = rand() % 81 + 20;
	TCHAR lpCount[10010];
	TCHAR lpOut[10010] = {};

	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));

		//wsprintf(lpCount, L"111");
		//RECT r_rect = { 0, 0, 22, 15};
		//DrawText(hdc, lpCount, 3, &r_rect, DT_WORDBREAK);
		//EndPaint(hWnd, &ps);
		//break;
		for (int i = 0; i < count; ++i)
		{
			for (int i = 0; i < count; ++i)
			{
				wsprintf(lpCount, L"%d", N);
				lstrcat(lpOut, lpCount);
			}
			wsprintf(lpCount, L" ");
			lstrcat(lpOut, lpCount);
		}
		RECT r_rect = { x, y, 0 + 8 * count, 0 + 20 * count };
		DrawText(hdc, lpOut, (count * count) + count, &r_rect, DT_WORDBREAK);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}