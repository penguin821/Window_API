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

	static Line line[MAX_LINES];

	static int current_line = 0;
	static int LineFullCount = 0;
	static int count = 0;

	TCHAR lpCount[MAX_LENGTH];
	TCHAR lpOut[MAX_LENGTH] = {};

	switch (uMsg) 
	{
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		break;
	case WM_CHAR:
	{
		if (wParam == VK_BACK)
			break;
		if (wParam == VK_RETURN)
			break;
		else
		{
			if (MAX_ONE_LINE == line[current_line].count)
			{
				if (9 == current_line)
					current_line = 0;
				else
					current_line++;

				line[current_line].isFull = true;

				
				for (int i = 0; i < MAX_LINES; i++)
				{
					if (true == line[i].isFull)
						count++;
				}

				if (MAX_LINES <= count)
				{
					if (10 == current_line)
						current_line = 0;

					line[current_line].count = 0;
				}
				else
					count = 0;
			}
			if (line[current_line].count < MAX_ONE_LINE)
				line[current_line].l_message[line[current_line].count++] = wParam;
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
			if (line[current_line].count == 0)
				break;
			else
				if (MAX_LINES <= count)
					line[current_line].l_message[--line[current_line].count] = ' ';
				else
					line[current_line].l_message[--line[current_line].count] = '\0';
		}
		else if (wParam == VK_RETURN)
		{
			if (MAX_LINES <= count)
			{
				if (9 == current_line)
				{
					current_line = 0;
					line[current_line].count = 0;
				}
				else
				{
					current_line++;
					line[current_line].count = 0;
				}
			}
			else
			{
				if (9 == current_line)
					current_line = 0;
				else
					current_line++;
			}

		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < MAX_LINES; i++)
		{
			TextOut(hdc, line[i].l_rect.left, line[i].l_rect.top + (i * 20),
				line[i].l_message, lstrlen(line[i].l_message));
		}
		if (MAX_LINES <= count)
		{
			GetTextExtentPoint32(hdc, line[current_line].l_message, lstrlen(line[current_line].l_message), &line[current_line].l_size);
			SetCaretPos(line[current_line].l_size.cx / MAX_ONE_LINE * line[current_line].count, current_line * 20);
		}
		else
		{
			GetTextExtentPoint32(hdc, line[current_line].l_message, lstrlen(line[current_line].l_message), &line[current_line].l_size);
			SetCaretPos(line[current_line].l_size.cx, current_line * 20);
		}
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