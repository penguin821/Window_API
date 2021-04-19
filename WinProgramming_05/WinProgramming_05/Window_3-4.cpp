#include <iostream>
#include <Windows.h>
#include <tchar.h>
//#include "resource.h"

#define _MSG_BOX(MESSAGE) MessageBox(0, TEXT(MESSAGE), TEXT("Error"), MB_OK);

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 800;

struct Cars
{
	RECT self;
	RECT temp;
	BOOL isCut;
};
struct Lights
{
	RECT self;
	BOOL isOn;
	short r, g, b;
};

enum Dir { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_END };
enum LightPos { UP_R, UP_Y, UP_G, DOWN_R, DOWN_Y, DOWN_G, END};

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window1";
LRESULT CALLBACK WndProc1(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

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
	Window = CreateWindow(lpszClass, L"windows program 3-4", WS_OVERLAPPEDWINDOW,
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
	static POINT mouse;
	static Cars car[4];
	static Lights light[6];
	HBRUSH blackBrush, cyanBrush, oldBrush, colorBrush;
	HPEN solidPen, dotPen, oldPen, selectPen;
	static short carTimer1, carTimer2, carTimer3, carTimer4, trafficTimer, traffic_count;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		GetClientRect(hWnd, &C);

		car[DIR_UP].self = { C.right / 2 + 15,5 * C.bottom / 6,2 * C.right / 3 - 15,C.bottom };
		car[DIR_UP].temp = { C.right / 2 + 15,C.bottom,2 * C.right / 3 - 15,C.bottom };

		car[DIR_DOWN].self = { C.right / 3 + 15,C.top,C.right / 2 - 15, C.bottom / 6 };
		car[DIR_DOWN].temp = { C.right / 3 + 15,C.top,C.right / 2 - 15, C.top };

		car[DIR_LEFT].self = { 5 * C.right / 6,C.bottom / 2 + 15,C.right,2 * C.bottom / 3 - 15 };
		car[DIR_LEFT].temp = { C.right,C.bottom / 2 + 15,C.right,2 * C.bottom / 3 - 15 };

		car[DIR_RIGHT].self = { C.left,C.bottom / 3 + 15,C.right / 6,C.bottom / 2 - 15 };
		car[DIR_RIGHT].temp = { C.left,C.bottom / 3 + 15,C.left,C.bottom / 2 - 15 };

		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				light[3 * i + j].self = { 2 * C.right / 3 + 15 + j * (C.right / 9 - 10) + 10, (i * 6 + 1) * C.bottom / 9 + 10 ,
					2 * C.right / 3 + 15 + (j + 1) * (C.right / 9 - 10) - 10, (i * 6 + 2) * C.bottom / 9 - 10 };
				light[3 * i + j].isOn = false;
				light[3 * i + j].r = 0;
				light[3 * i + j].g = 0;
				light[3 * i + j].b = 0;
			}
		}

		light[UP_R].r = 255;
		light[UP_R].g = 0;
		light[UP_R].b = 0;

		light[UP_Y].r = 255;
		light[UP_Y].g = 255;
		light[UP_Y].b = 0;

		light[UP_G].r = 0;
		light[UP_G].g = 255;
		light[UP_G].b = 0;

		light[DOWN_R].r = 255;
		light[DOWN_R].g = 0;
		light[DOWN_R].b = 0;

		light[DOWN_Y].r = 255;
		light[DOWN_Y].g = 255;
		light[DOWN_Y].b = 0;

		light[DOWN_G].r = 0;
		light[DOWN_G].g = 255;
		light[DOWN_G].b = 0;

		carTimer1 = 40;
		carTimer2 = 60;
		carTimer3 = 80;
		carTimer4 = 100;

		light[UP_G].isOn = true;
		light[DOWN_R].isOn = true;

		SetTimer(hWnd, DIR_UP, carTimer1, NULL);
		SetTimer(hWnd, DIR_DOWN, carTimer2, NULL);
		SetTimer(hWnd, DIR_LEFT, carTimer3, NULL);
		SetTimer(hWnd, DIR_RIGHT, carTimer4, NULL);
	}
	break;
	//case WM_COMMAND:
	//{
	//	switch (LOWORD(wParam))
	//	{
	//	case ID_GAME_START:
	//		break;
	//	case ID_GAME_END:
	//		KillTimer(hWnd, DIR_UP);
	//		KillTimer(hWnd, DIR_DOWN);
	//		KillTimer(hWnd, DIR_LEFT);
	//		KillTimer(hWnd, DIR_RIGHT);
	//		KillTimer(hWnd, 4);
	//		PostQuitMessage(0);
	//		break;
	//	case ID_SPEED_ACCELERATE:
	//		break;
	//	case ID_SPEED_SLOWDOWN:
	//		break;
	//	case ID_DIRECTION_UP:
	//		break;
	//	case ID_DIRECTION_LEFT:
	//		break;
	//	case ID_DIRECTION_ALL:
	//		break;
	//	case ID_TRAFFICLIGHT_RED:
	//		break;
	//	case ID_TRAFFICLIGHT_BLUE:
	//		break;
	//	case ID_TRAFFICLIGHT_YELLOW:
	//		break;
	//	case ID_TRAFFICLIGHT_AUTO:
	//		break;
	//	}
	//}
	//break;
	case WM_CHAR:
	{
		if (wParam == 'q' || wParam == 'Q')
		{
			PostQuitMessage(0);
		}
		if (wParam == 'a')
		{
			SetTimer(hWnd, 4, trafficTimer, NULL);
		}
		if (wParam == 'A')
		{
			KillTimer(hWnd, 4);
		}
		if (wParam == '+' || wParam == '=')
		{
			carTimer1 -= 1;
			carTimer2 -= 1;
			carTimer3 -= 1;
			carTimer4 -= 1;
			SetTimer(hWnd, DIR_UP, carTimer1, NULL);
			SetTimer(hWnd, DIR_DOWN, carTimer2, NULL);
			SetTimer(hWnd, DIR_LEFT, carTimer3, NULL);
			SetTimer(hWnd, DIR_RIGHT, carTimer4, NULL);
		}
		if (wParam == '-' || wParam == '_')
		{
			carTimer1 += 1;
			carTimer2 += 1;
			carTimer3 += 1;
			carTimer4 += 1;
			SetTimer(hWnd, DIR_UP, carTimer1, NULL);
			SetTimer(hWnd, DIR_DOWN, carTimer2, NULL);
			SetTimer(hWnd, DIR_LEFT, carTimer3, NULL);
			SetTimer(hWnd, DIR_RIGHT, carTimer4, NULL);
		}
	}
	break;
	case WM_TIMER:
	{
		GetClientRect(hWnd, &C);
		switch (wParam)
		{
		case DIR_UP:
		{
			if (light[UP_G].isOn || light[UP_Y].isOn)
			{
				car[DIR_UP].self.top -= 10;
				car[DIR_UP].self.bottom -= 10;
				if (C.top > car[DIR_UP].self.top)
				{
					car[DIR_UP].isCut = true;
					car[DIR_UP].temp.top = C.bottom - (C.top - car[DIR_UP].self.top);

					if (C.top > car[DIR_UP].self.bottom)
					{
						car[DIR_UP].self = car[DIR_UP].temp;
						car[DIR_UP].temp = { C.right / 2 + 15,C.bottom,2 * C.right / 3 - 15,C.bottom };
						car[DIR_UP].isCut = false;
					}
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case DIR_DOWN:
		{
			if (light[UP_G].isOn || light[UP_Y].isOn)
			{
				car[DIR_DOWN].self.top += 10;
				car[DIR_DOWN].self.bottom += 10;
				if (C.bottom < car[DIR_DOWN].self.bottom)
				{
					car[DIR_DOWN].isCut = true;
					car[DIR_DOWN].temp.bottom = car[DIR_DOWN].self.bottom - C.bottom;

					if (C.bottom < car[DIR_DOWN].self.top)
					{
						car[DIR_DOWN].self = car[DIR_DOWN].temp;
						car[DIR_DOWN].temp = { C.right / 3 + 15,C.top,C.right / 2 - 15, C.top };
						car[DIR_DOWN].isCut = false;
					}
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case DIR_LEFT:
		{
			if (light[DOWN_G].isOn || light[DOWN_Y].isOn)
			{
				car[DIR_LEFT].self.left -= 10;
				car[DIR_LEFT].self.right -= 10;
				if (C.left > car[DIR_LEFT].self.left)
				{
					car[DIR_LEFT].isCut = true;
					car[DIR_LEFT].temp.left = C.right - (C.left - car[DIR_LEFT].self.left);

					if (C.left > car[DIR_LEFT].self.right)
					{
						car[DIR_LEFT].self = car[DIR_LEFT].temp;
						car[DIR_LEFT].temp = { C.right,C.bottom / 2 + 15,C.right,2 * C.bottom / 3 - 15 };
						car[DIR_LEFT].isCut = false;
					}
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case DIR_RIGHT:
		{
			if (light[DOWN_G].isOn || light[DOWN_Y].isOn)
			{
				car[DIR_RIGHT].self.left += 10;
				car[DIR_RIGHT].self.right += 10;
				if (C.right < car[DIR_RIGHT].self.right)
				{
					car[DIR_RIGHT].isCut = true;
					car[DIR_RIGHT].temp.right = car[DIR_RIGHT].self.right - C.right;

					if (C.right < car[DIR_RIGHT].self.left)
					{
						car[DIR_RIGHT].self = car[DIR_RIGHT].temp;
						car[DIR_RIGHT].temp = { C.left,C.bottom / 3 + 15,C.left,C.bottom / 2 - 15 };
						car[DIR_RIGHT].isCut = false;
					}
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case 4:
		{
			traffic_count++;
			if (100 == traffic_count)
			{
				if (light[UP_G].isOn)
				{
					light[UP_G].isOn = false;
					light[UP_Y].isOn = true;
					light[DOWN_R].isOn = true;
					light[DOWN_Y].isOn = false;
					light[DOWN_G].isOn = false;
					traffic_count = 0;
				}
				else if (light[DOWN_G].isOn)
				{
					light[DOWN_G].isOn = false;
					light[DOWN_Y].isOn = true;
					light[UP_R].isOn = true;
					light[UP_G].isOn = false;
					light[UP_Y].isOn = false;
					traffic_count = 0;
				}
				else if (light[UP_Y].isOn)
				{
					light[UP_Y].isOn = false;
					light[UP_R].isOn = true;
					light[DOWN_G].isOn = true;
					light[DOWN_R].isOn = false;
					light[DOWN_Y].isOn = false;
					traffic_count = 0;
				}
				else if (light[DOWN_Y].isOn)
				{
					light[DOWN_Y].isOn = false;
					light[DOWN_R].isOn = true;
					light[UP_G].isOn = true;
					light[UP_R].isOn = false;
					light[UP_Y].isOn = false;
					traffic_count = 0;
				}
				else if (light[DOWN_R].isOn && light[UP_R].isOn)
				{
					light[DOWN_G].isOn = false;
					light[DOWN_Y].isOn = false;
					light[DOWN_R].isOn = true;
					light[UP_G].isOn = true;
					light[UP_R].isOn = false;
					light[UP_Y].isOn = false;
					traffic_count = 0;
				}

			}
		}
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{

	}
	InvalidateRect(hWnd, NULL, FALSE);
	break;
	case WM_LBUTTONUP:
	{
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);

		int selected = -1;
		for (int i = 0; i < 6; ++i)
		{
			if (PtInRect(&light[i].self, mouse))
			{
				selected = i;
				break;
			}
		}

		if (0 <= selected && selected < 3)
		{
			for (int i = 0; i < 3; ++i)
			{
				if (i == selected)
					light[i].isOn = true;
				else
					light[i].isOn = false;
			}
		}
		else if (3 <= selected && selected < 6)
		{
			for (int i = 3; i < 6; ++i)
			{
				if (i == selected)
					light[i].isOn = true;
				else
					light[i].isOn = false;
			}
		}
	}
	break;
	case WM_MOUSEMOVE:
	{

	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		cyanBrush = CreateSolidBrush(RGB(0, 255, 255));
		blackBrush = CreateSolidBrush(RGB(0, 0, 0));
		dotPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		solidPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

		GetClientRect(hWnd, &C);
		Rectangle(hdc, C.left, C.top, C.right, C.bottom);
		// 맵
		Rectangle(hdc, C.left, C.top, C.right / 3, C.bottom / 3);
		Rectangle(hdc, 2 * C.right / 3, C.top, C.right, C.bottom / 3);
		Rectangle(hdc, C.left, 2 * C.bottom / 3, C.right / 3, C.bottom);
		Rectangle(hdc, 2 * C.right / 3, 2 * C.bottom / 3, C.right, C.bottom);

		//신호등 틀
		Rectangle(hdc, 2 * C.right / 3 + 15, C.bottom / 9, C.right - 15, 2 * C.bottom / 9);
		Rectangle(hdc, 2 * C.right / 3 + 15, 7 * C.bottom / 9, C.right - 15, 8 * C.bottom / 9);

		for (int i = 0; i < 6; i++)
		{
			colorBrush = CreateSolidBrush(RGB(light[i].r, light[i].g, light[i].b));
			oldBrush = (HBRUSH)SelectObject(hdc, colorBrush);
			if (light[i].isOn)
			{
				selectPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
				oldPen = (HPEN)SelectObject(hdc, selectPen);
				Ellipse(hdc, light[i].self.left, light[i].self.top, light[i].self.right, light[i].self.bottom);
				SelectObject(hdc, oldPen);
				DeleteObject(selectPen);
			}
			else
				Ellipse(hdc, light[i].self.left, light[i].self.top, light[i].self.right, light[i].self.bottom);
			SelectObject(hdc, oldBrush);
			DeleteObject(colorBrush);
		}

		oldPen = (HPEN)SelectObject(hdc, dotPen);
		Rectangle(hdc, C.right / 3, C.bottom / 3, 2 * C.right / 3, 2 * C.bottom / 3);

		
		oldPen = (HPEN)SelectObject(hdc, solidPen);
		MoveToEx(hdc, C.right / 2, C.top, NULL);
		LineTo(hdc, C.right / 2, C.bottom);
		MoveToEx(hdc, C.left, C.bottom / 2, NULL);
		LineTo(hdc, C.right, C.bottom / 2);
		// 차
		oldBrush = (HBRUSH)SelectObject(hdc, cyanBrush);
		Rectangle(hdc, car[DIR_UP].self.left, car[DIR_UP].self.top, car[DIR_UP].self.right, car[DIR_UP].self.bottom);
		if (car[DIR_UP].isCut)
			Rectangle(hdc, car[DIR_UP].temp.left, car[DIR_UP].temp.top, car[DIR_UP].temp.right, car[DIR_UP].temp.bottom);

		Rectangle(hdc, car[DIR_DOWN].self.left, car[DIR_DOWN].self.top, car[DIR_DOWN].self.right, car[DIR_DOWN].self.bottom);
		if (car[DIR_DOWN].isCut)
			Rectangle(hdc, car[DIR_DOWN].temp.left, car[DIR_DOWN].temp.top, car[DIR_DOWN].temp.right, car[DIR_DOWN].temp.bottom);

		Rectangle(hdc, car[DIR_LEFT].self.left, car[DIR_LEFT].self.top, car[DIR_LEFT].self.right, car[DIR_LEFT].self.bottom);
		if (car[DIR_LEFT].isCut)
			Rectangle(hdc, car[DIR_LEFT].temp.left, car[DIR_LEFT].temp.top, car[DIR_LEFT].temp.right, car[DIR_LEFT].temp.bottom);

		Rectangle(hdc, car[DIR_RIGHT].self.left, car[DIR_RIGHT].self.top, car[DIR_RIGHT].self.right, car[DIR_RIGHT].self.bottom);
		if (car[DIR_RIGHT].isCut)
			Rectangle(hdc, car[DIR_RIGHT].temp.left, car[DIR_RIGHT].temp.top, car[DIR_RIGHT].temp.right, car[DIR_RIGHT].temp.bottom);

		SelectObject(hdc, oldPen);
		DeleteObject(solidPen);
		DeleteObject(dotPen);

		SelectObject(hdc, oldBrush);
		DeleteObject(blackBrush);
		DeleteObject(cyanBrush);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		KillTimer(hWnd, DIR_UP);
		KillTimer(hWnd, DIR_DOWN);
		KillTimer(hWnd, DIR_LEFT);
		KillTimer(hWnd, DIR_RIGHT);
		KillTimer(hWnd, 4);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}