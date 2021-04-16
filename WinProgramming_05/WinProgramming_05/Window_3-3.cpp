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
	short x,y;
	short r, g, b;
	short p_r, p_g, p_b;
	bool isCollision;
	RECT rect;
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
	Window = CreateWindow(lpszClass, L"windows program 3-3", WS_OVERLAPPEDWINDOW,
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

	static RECT Cage;
	static RECT new_Cage;

	static POINT mouse;
	static Circles circle[100];

	static int speed1, speed2, speed3, speed4;

	static int startX, startY, oldX, oldY, move_x, move_y;
	static BOOL Drag,Move;
	int endX, endY;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		GetClientRect(hWnd, &C);
		Cage.left = oldX = 0; 
		Cage.top = oldY = 0;
		Drag = FALSE;

		for (int i = 0; i < 100; ++i)
		{
			circle[i].x = rand() % C.right + C.left;
			circle[i].y = rand() % C.bottom + C.top;
			circle[i].r = rand() % 256;
			circle[i].g = rand() % 256;
			circle[i].b = rand() % 256;
			circle[i].p_r = rand() % 256;
			circle[i].p_g = rand() % 256;
			circle[i].p_b = rand() % 256;
			circle[i].isCollision = false;
			circle[i].rect = { circle[i].x, circle[i].y, circle[i].x + 10, circle[i].y + 10 };
		}

		speed1 = 90;
		speed2 = 70;
		speed3 = 50;
		speed4 = 30;

		SetTimer(hWnd, 1, speed1, NULL);
		SetTimer(hWnd, 2, speed2, NULL);
		SetTimer(hWnd, 3, speed3, NULL);
		SetTimer(hWnd, 4, speed4, NULL);
	}
	break;
	case WM_TIMER:
	{
		GetClientRect(hWnd, &C);
		switch (wParam)
		{
		case 1:
			for (int i = 0; i < 25; i++)
			{
				if ((Cage.right > circle[i].x && Cage.left< circle[i].x) && (Cage.bottom == circle[i].y + 10))
					continue;

				if (C.bottom == circle[i].y)
					circle[i].y = C.top;
				else
					circle[i].y += 1;
			}
			break;
		case 2:
			for (int i = 25; i < 50; i++)
			{
				if ((Cage.right > circle[i].x && Cage.left < circle[i].x) && (Cage.bottom == circle[i].y + 10))
					continue;

				if (C.bottom == circle[i].y)
					circle[i].y = C.top;
				else
					circle[i].y += 1;
			}
			break;
		case 3:
			for (int i = 50; i < 75; i++)
			{
				if ((Cage.right > circle[i].x && Cage.left < circle[i].x) && (Cage.bottom == circle[i].y + 10))
					continue;

				if (C.bottom == circle[i].y)
					circle[i].y = C.top;
				else
					circle[i].y += 1;
			}
			break;
		case 4:
			for (int i = 75; i < 100; i++)
			{
				if ((Cage.right > circle[i].x && Cage.left < circle[i].x) && (Cage.bottom == circle[i].y + 10))
					continue;

				if (C.bottom == circle[i].y)
					circle[i].y = C.top;
				else
					circle[i].y += 1;
			}
			break;
		}
	}
	InvalidateRect(hWnd, NULL, FALSE);
	break;
	case WM_CHAR:
	{
		if (wParam == 'q' || wParam == 'Q')
		{
			PostQuitMessage(0);
		}
		if (wParam == 'S' || wParam == 's')
		{

		}
		if (wParam == 'D' || wParam == 'd')
		{
			Cage.right = 0;
			Cage.left = 0;
			Cage.top = 0;
			Cage.bottom = 0;
		}
		if (wParam == '+' || wParam == '=')
		{
			SetTimer(hWnd, 1, speed1 - 20, NULL);
			SetTimer(hWnd, 2, speed2 - 20, NULL);
			SetTimer(hWnd, 3, speed3 - 20, NULL);
			SetTimer(hWnd, 4, speed4 - 20, NULL);
		}
		if (wParam == '-' || wParam == '_')
		{
			SetTimer(hWnd, 1, speed1 + 20, NULL);
			SetTimer(hWnd, 2, speed2 + 20, NULL);
			SetTimer(hWnd, 3, speed3 + 20, NULL);
			SetTimer(hWnd, 4, speed4 + 20, NULL);
		}
	}
	InvalidateRect(hWnd, NULL, FALSE);
	break;
	case WM_LBUTTONDOWN:
	{
		oldX = Cage.left = LOWORD(lParam);
		oldY = Cage.top = HIWORD(lParam);
		Drag = TRUE;
	}
	InvalidateRect(hWnd, NULL, TRUE);
	break;
	case WM_LBUTTONUP:
	{
		Drag = FALSE;
	}
	break;
	case WM_RBUTTONDOWN:
	{
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
		if (PtInRect(&Cage, mouse))
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
		hdc = GetDC(hWnd); 
		if (Drag)
		{
			SetROP2(hdc, R2_XORPEN);
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
			SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
			Cage.right = LOWORD(lParam);
			Cage.bottom = HIWORD(lParam);
			Rectangle(hdc, Cage.left, Cage.top, oldX, oldY); // 지우기
			Rectangle(hdc, Cage.left, Cage.top, Cage.right, Cage.bottom); // 그리기
			oldX = Cage.right;
			oldY = Cage.bottom;
		}
		if (Move)
		{
			mouse.x = LOWORD(lParam);
			mouse.y = HIWORD(lParam);
			new_Cage.left = mouse.x - (Cage.right - Cage.left) / 2;
			new_Cage.right = mouse.x + (Cage.right - Cage.left) / 2;
			new_Cage.top = mouse.y - (Cage.bottom - Cage.top) / 2;
			new_Cage.bottom = mouse.y + (Cage.bottom - Cage.top) / 2;

			Cage = new_Cage;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case VK_UP:
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		case VK_DOWN:
			break;
		}
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &C);

		Rectangle(hdc, C.left, C.top, C.right, C.bottom); // 지우기

		Rectangle(hdc, Cage.left, Cage.top, Cage.right, Cage.bottom); // 그리기

		for (int i = 0; i < 100; ++i)
		{
			hBrush = CreateSolidBrush(RGB(circle[i].r, circle[i].g, circle[i].b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, circle[i].x, circle[i].y, circle[i].x + 10, circle[i].y + 10);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		KillTimer(hWnd, 4);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}