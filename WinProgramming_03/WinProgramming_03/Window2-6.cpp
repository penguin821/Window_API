#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window";
constexpr int WINDOW_WIDTH = 700;
constexpr int WINDOW_HEIGHT = 650;
constexpr int MAX_LENGTH = 800;
constexpr int MAX_LINES = 10;
constexpr int MAX_ONE_LINE = 5;

struct Line
{
	TCHAR l_message[MAX_ONE_LINE];
	RECT l_rect;
	SIZE l_size;
	int count = 0;
	bool isFull = false;
};


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
	RECT C;
	static SIZE size;
	static TCHAR Memo[MAX_LINES][MAX_ONE_LINE];
	static TCHAR kpos[MAX_ONE_LINE];
	static short kpos_x, kpos_y;

	switch (uMsg)
	{
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		kpos_x = 0;
		kpos_y = 0;

		for (int i = 0; i < MAX_LINES; ++i)
		{
			for (int j = 0; j < MAX_ONE_LINE; ++j)
			{
				Memo[i][j] = '\0';
			}
		} // 전체 메모장 출력
		for (int j = 0; j < MAX_ONE_LINE; ++j)
		{
			kpos[j] = ' ';
		}
		break;
	case WM_CHAR:
	{
		if (wParam == VK_BACK)
			break;
		if (wParam == VK_RETURN)
			break;
		else
		{
			Memo[kpos_y][kpos_x] = wParam;
			if (kpos_x + 1 >= MAX_ONE_LINE)
			{
				kpos_y++;
				kpos_x = 0;
			}
			else
				kpos_x++;
		}
		InvalidateRect(hWnd, NULL, TRUE);
	}
	break;
	case WM_KEYDOWN:
		if (wParam == 'o')
		{
			PostQuitMessage(0);
		}

		if (wParam == VK_BACK)
		{

		}
		else if (wParam == VK_RETURN)
		{
			if (MAX_LINES == kpos_y)
				kpos_y = 0;
			else
				kpos_y++;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &C);

		for (int i = 0; i < MAX_LINES; ++i)
		{
			TextOut(hdc, C.left, C.top + (i * 20), Memo[i], MAX_ONE_LINE);
		} // 전체 메모장 출력

		GetTextExtentPoint32(hdc, kpos, lstrlen(kpos), &size);
		int a = lstrlen(kpos);
		SetCaretPos(size.cx / MAX_ONE_LINE * kpos_x, kpos_y * 20);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}