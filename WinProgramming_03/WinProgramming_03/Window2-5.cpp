#include <iostream>
#include <Windows.h>
#include <tchar.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

constexpr int DIVIDE_WIDTH = 3;
constexpr int DIVIDE_HEIGHT = 2;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window1";
LRESULT CALLBACK WndProc1(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
enum Shape { SP_X, SP_EXTRI, SP_DIA, SP_BUTR, SP_SAND, SP_EMPTYSQ, SP_END };

//void GetShape(int shape)
//{
//	switch (shape)
//	{
//	case SP_X:
//		if (height % 2 == 1)
//		{
//			for (float i = 0; i < ceil(height / 2); i++)
//			{
//				for (float j = 0; j < i * 2; j++)
//				{
//					cout << " ";
//				}
//				for (float j = 0; j < size - (i * 4); j++)
//				{
//					if (0 == j || size - (i * 4) - 1 == j)
//						cout << "*";
//					else
//						cout << " ";
//				}
//				cout << "\n";
//			}
//
//			for (int i = 0; i < height - ceil(height / 2); i++)
//			{
//				for (int j = 0; j < height - (i * 2) - 1; j++)
//				{
//					cout << " ";
//				}
//				for (int j = 0; j < (i * 4) + 2; j++)
//				{
//					if (0 == j || (i * 4) + 2 - 1 == j)
//						cout << "*";
//					else
//						cout << " ";
//				}
//				cout << "\n";
//			}
//		}
//		else
//		{
//			for (float i = 0; i < ceil(height / 2); i++)
//			{
//				for (float j = 0; j < i * 2; j++)
//				{
//					cout << " ";
//				}
//				for (float j = 0; j < size - (i * 4); j++)
//				{
//					if (0 == j || size - (i * 4) - 1 == j)
//						cout << "*";
//					else
//						cout << " ";
//				}
//				cout << "\n";
//			}
//
//			for (int i = 0; i < height - ceil(height / 2); i++)
//			{
//				for (int j = 0; j < height - (i * 2) - 2; j++)
//				{
//					cout << " ";
//				}
//				for (int j = 0; j < (i * 4) + 4; j++)
//				{
//					if (0 == j || (i * 4) + 4 - 1 == j)
//						cout << "*";
//					else
//						cout << " ";
//				}
//				cout << "\n";
//			}
//		}
//		break;
//	case SP_EXTRI:
//		for (int i = 0; i < height; i++)
//		{
//			for (int j = 0; j < i; j++)
//			{
//				cout << " ";
//			}
//			for (int j = 0; j < size - (i * 2); j++)
//			{
//				cout << "*";
//			}
//			cout << "\n";
//		}
//		break;
//	case SP_DIA:
//		for (int i = 0; i < height; i++)
//		{
//			for (int j = height - 1; j > i; j--)
//			{
//				cout << " ";
//			}
//			for (int j = 0; j < 2 * i + 2; j++)
//			{
//				cout << "*";
//			}
//			cout << "\n";
//		}
//		for (int i = 1; i < height; i++)
//		{
//			for (int j = 0; j < i; j++)
//			{
//				cout << " ";
//			}
//			for (int j = 2 * height; j > 2 * i; j--)
//			{
//				cout << "*";
//			}
//			cout << "\n";
//		}
//		break;
//	case SP_BUTR:
//		for (int i = 0; i < height; i++)
//		{
//			for (int j = 0; j <= i; j++)
//				cout << "*";
//			for (int x = 1; x < height - i; x++)
//				cout << " ";
//			for (int y = 1; y < height - i; y++)
//				cout << " ";
//			for (int z = 0; z <= i; z++)
//				cout << "*";
//			cout << "\n";
//		}
//		for (int i = 1; i < height; i++)
//		{
//			for (int j = 0; j < height - i; j++)
//				cout << "*";
//			for (int x = 1; x <= i; x++)
//				cout << " ";
//			for (int y = 1; y <= i; y++)
//				cout << " ";
//			for (int z = 0; z < height - i; z++)
//				cout << "*";
//			cout << "\n";
//		}
//		break;
//	case SP_SAND:
//		if (height % 2 == 1)
//		{
//			for (float i = 0; i < ceil(height / 2); i++)
//			{
//				for (float j = 0; j < i * 2; j++)
//				{
//					cout << " ";
//				}
//				for (float j = 0; j < size - (i * 4); j++)
//				{
//					cout << "*";
//				}
//				cout << "\n";
//			}
//
//			for (int i = 0; i < height - ceil(height / 2); i++)
//			{
//				for (int j = 0; j < height - (i * 2) - 1; j++)
//				{
//					cout << " ";
//				}
//				for (int j = 0; j < (i * 4) + 2; j++)
//				{
//					cout << "*";
//				}
//				cout << "\n";
//			}
//		}
//		else
//		{
//			for (float i = 0; i < ceil(height / 2); i++)
//			{
//				for (float j = 0; j < i * 2; j++)
//				{
//					cout << " ";
//				}
//				for (float j = 0; j < size - (i * 4); j++)
//				{
//					cout << "*";
//				}
//				cout << "\n";
//			}
//
//			for (int i = 0; i < height - ceil(height / 2); i++)
//			{
//				for (int j = 0; j < height - (i * 2) - 2; j++)
//				{
//					cout << " ";
//				}
//				for (int j = 0; j < (i * 4) + 4; j++)
//				{
//					cout << "*";
//				}
//				cout << "\n";
//			}
//		}
//		break;
//	case SP_EMPTYSQ:
//		for (int i = 0; i < height; i++)
//		{
//			if (0 == i || height - 1 == i)
//			{
//				for (int j = 0; j < size; j++)
//				{
//					cout << "*";
//				}
//			}
//			else
//			{
//				for (int j = 0; j < size; j++)
//				{
//					if (0 == j || size - 1 == j)
//						cout << "*";
//					else
//						cout << " ";
//				}
//			}
//			cout << "\n";
//		}
//		break;
//	}
//}

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
	Window = CreateWindow(lpszClass, L"windows program 2-5", WS_OVERLAPPEDWINDOW,
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
	static SIZE output_size;
	TCHAR lpCount[10010];
	static TCHAR lpOut[WINDOW_HEIGHT / 20][WINDOW_HEIGHT / 10];
	switch (uMsg)
	{
	case WM_CREATE:
	{
		
	}
	break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		//wsprintf(lpCount, L"111");
		//RECT r_rect = { 0, 0, 22, 15};
		//DrawText(hdc, lpCount, 3, &r_rect, DT_WORDBREAK);
		//EndPaint(hWnd, &ps);
		//break;
		//for (int i = 0; i < DIVIDE_WIDTH; ++i) // 가로
		//{
		//	for (int i = 0; i < DIVIDE_HEIGHT; ++i) // 세로
		//	{
		for (int i = 20; i < WINDOW_HEIGHT; i += 20) // 한줄씩 증가
		{
			for (int j = 0; j < WINDOW_WIDTH/10 - i; j++)
			{
				wsprintf(lpCount, L"*");
				lstrcat(lpOut[(i / 20) - 1], lpCount);
			}
			GetTextExtentPoint32(hdc, lpOut[(i / 20) - 1], lstrlen(lpOut[(i / 20) - 1]), &output_size);
			RECT r_rect = { WINDOW_WIDTH / 10 + i, i, (WINDOW_WIDTH / 10 + i) + output_size.cx, i + output_size.cy };
			DrawText(hdc, lpOut[(i / 20) - 1], _tcslen(lpOut[(i / 20) - 1]), &r_rect, DT_WORDBREAK);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}