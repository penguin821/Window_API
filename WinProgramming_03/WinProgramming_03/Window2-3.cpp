#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window";
constexpr int WINDOW_WIDTH = 700;
constexpr int WINDOW_HEIGHT = 650;
constexpr int MAX_LENGTH = 100;
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
	static SIZE input_size;
	static SIZE output_size;
	static TCHAR str[MAX_LENGTH]; 
	static int count = 0;
	static int x, y, N;
	static bool isInput = false;
	static float numbers[MAX_LENGTH];
	int count_numb = 0;
	TCHAR lpCount[10010];
	TCHAR lpOut[10010] = {};

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		if (wParam == 'o')
		{
			PostQuitMessage(0);
		}

		if (wParam == VK_BACK)
		{
			if (count == 0)
				break;
			else
				str[--count] = '\0';
		}
		else if (wParam == VK_RETURN)
		{
			str[count] = '\n';
			for (int i = 0; i < count; i++)
			{
				if (48 <= str[i] && 57 >= str[i]) // 상수일때
				{
					if (48 <= str[i + 1] && 57 >= str[i + 1]) // 두자리 상수일때
					{
						if (48 <= str[i + 2] && 57 >= str[i + 2]) // 세자리 상수일때
						{
							numbers[count_numb] = 100 * (str[i] - 48) + 10 * (str[i + 1] - 48) + (str[i + 2] - 48);
							count_numb++;
							i++; 
							i++;// 두 차례 추가로 넘김
						}
						else
						{
							numbers[count_numb] = 10 * (str[i] - 48) + (str[i + 1] - 48);
							count_numb++;
							i++; // 한 차례 추가로 넘김
						}
					}
					else
					{
						numbers[count_numb] = str[i] - 48;
						count_numb++;
					}
				}
			}
			if ((4 <= count_numb || 3 > count_numb) || (numbers[2] > 19 || numbers[2] < 1))
			{
				for (int i = 0; i < count; i++)
				{
					str[i] = '\0';
				}
				count = 0;
				isInput = false;
			}
			else // 정상 입력시 처리, numbers[2] 단수
			{
				N = numbers[2];
				str[count] = '\0';
				isInput = true;
			}
		}
		else
		{
			if (MAX_LENGTH == count)
				break;
			else
			{
				str[count++] = wParam;
				str[count] = '\0';
			}
		}
		TextOut(hdc, 0, 0, str, lstrlen(str));
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetTextExtentPoint32(hdc, str, lstrlen(str), &input_size);
		TextOut(hdc, 0, 0, str, lstrlen(str));
		SetCaretPos(input_size.cx, 0);

	if (true == isInput)
		{
			for (int i = 1; i < 10; ++i)
			{
				wsprintf(lpCount, L"%d * %d = %d   ", N, i, N * i);
				lstrcat(lpOut, lpCount);
			}
			GetTextExtentPoint32(hdc, lpOut, lstrlen(lpOut), &output_size);
			RECT r_rect = { numbers[0], numbers[1],numbers[0] + 50, numbers[1] + WINDOW_HEIGHT };
			DrawText(hdc, lpOut, _tcslen(lpOut), &r_rect, DT_WORDBREAK);
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