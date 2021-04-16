#include <iostream>
#include <Windows.h>
#include <tchar.h>

#define _MSG_BOX(MESSAGE) MessageBox(0, TEXT(MESSAGE), TEXT("Error"), MB_OK);

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window1";
LRESULT CALLBACK WndProc1(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

struct Circles
{
	short x, y;
	short r, g, b;
	bool isCollision;
	RECT rect;
};

struct shape_info
{
	short shape, x1, y1, x2, y2, thick;
	short r, g, b;
	short p_r, p_g, p_b;
	bool isDraw = false;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	srand(time(NULL));
	HWND Window;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc1;
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
	Window = CreateWindow(lpszClass, L"windows program 3-2", WS_OVERLAPPEDWINDOW,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(Window, nCmdShow);
	UpdateWindow(Window);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc1(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT C;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	static int DIVIDE_HEIGHT = 3, DIVIDE_WIDTH = 10;
	static RECT Board[3][10];
	static RECT Player,new_Player;
	static POINT mouse;
	static Circles circle;

	static int ball_speed;

	static int startX, startY, oldX, oldY, move_x, move_y;
	static BOOL Move, isStart;
	int endX, endY;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		GetClientRect(hWnd, &C);
		for (int i = 0; i < DIVIDE_HEIGHT; ++i)
		{
			for (int j = 0; j < DIVIDE_WIDTH; ++j)
			{
				Board[i][j] = { C.left + (j + 1) * C.right / 12,C.top + (i + 1) * C.bottom / 12,
					C.left + (j + 2) * C.right / 12,C.top + (i + 2) * C.bottom / 12 };
			}
		}

		Player = { C.left + 4 * C.right / 12,C.top + 10 * C.bottom / 12,C.left + 8 * C.right / 12,C.top + 11 * C.bottom / 12 };
		circle.x = Player.left;
		circle.y = Player.top - 20;
		circle.rect = { circle.x ,circle.y,circle.x + 20,circle.y + 20 };
		isStart = false;
		ball_speed = 5;
	}
	break;
	case WM_CHAR:
	{
		if (wParam == 'q' || wParam == 'Q')
		{
			PostQuitMessage(0);
		}
		if (wParam == 's' || wParam == 'S')
		{
			isStart = TRUE;
			SetTimer(hWnd, 1, ball_speed, NULL);
		}
		if (wParam == 'n' || wParam == 'N')
		{

		}
		if (wParam == 'k' || wParam == 'K')
		{

		}
		if (wParam == '+' || wParam == '=')
		{

		}
		if (wParam == '-')
		{

		}
	}
	break;
	case WM_TIMER:
	{
		GetClientRect(hWnd, &C);
		switch (wParam)
		{
		case 1:
			circle.x += 1;
			circle.y -= 1;
			circle.rect = { circle.x ,circle.y,circle.x + 20,circle.y + 20 };
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
	}
	case WM_RBUTTONDOWN:
	{
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
		if (PtInRect(&Player, mouse))
			Move = TRUE;
	}
	InvalidateRect(hWnd, NULL, FALSE);
	break;
	case WM_RBUTTONUP:
	{
		InvalidateRect(hWnd, NULL, FALSE);
		Move = FALSE;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (Move)
		{
			mouse.x = LOWORD(lParam);
			mouse.y = HIWORD(lParam);
			new_Player.left = mouse.x - (Player.right - Player.left) / 2;
			new_Player.right = mouse.x + (Player.right - Player.left) / 2;
			new_Player.top = Player.top;
			new_Player.bottom = Player.bottom;
			Player = new_Player;
			if (!isStart)
			{
				circle.x = Player.left;
				circle.y = Player.top - 20;
				circle.rect = { circle.x ,circle.y,circle.x + 20,circle.y + 20 };
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &C);
		Rectangle(hdc, C.left, C.top, C.right, C.bottom); // Áö¿ì±â
		for (int i = 0; i < DIVIDE_HEIGHT; ++i)
		{
			for (int j = 0; j < DIVIDE_WIDTH; ++j)
			{
				Rectangle(hdc, Board[i][j].left, Board[i][j].top, Board[i][j].right, Board[i][j].bottom);
			}
		}

		Rectangle(hdc, Player.left, Player.top, Player.right, Player.bottom);

		Ellipse(hdc, circle.rect.left, circle.rect.top, circle.rect.right, circle.rect.bottom);
		
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}