#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <map>

using namespace std;

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int MAX_LENGTH = 21;
constexpr int MAX_INPUT = 6;

constexpr int DIVIDE_WIDTH = 3;
constexpr int DIVIDE_HEIGHT = 2;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window1";
LRESULT CALLBACK WndProc1(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
enum Shape { SP_X, SP_EXTRI, SP_DIA, SP_BUTR, SP_SAND, SP_EMPTYSQ, SP_END };

struct shape_info 
{
	short shape, x1, y1, x2, y2, thick;
	short r, g, b;
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
	Window = CreateWindow(lpszClass, L"windows program 2-9", WS_OVERLAPPEDWINDOW,
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
	static TCHAR str[MAX_LENGTH+1];
	static int key_count = 0;
	static int shape_count;
	static bool isInput;
	static float numbers[MAX_INPUT];
	static map<int, shape_info> save_shape;
	int count_numb = 0;
	static TCHAR str[MAX_LENGTH + 1];
	HBRUSH hBrush, oldBrush;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		shape_count = 0;
	}
	break;
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		if (wParam == 'o')
		{
			PostQuitMessage(0);
		}
		if (wParam == VK_BACK)
		{
			if (key_count == 0)
				break;
			else
				str[--key_count] = '\0';
		}
		else if (wParam == VK_RETURN)
		{
			str[key_count] = '\n';
			for (int i = 0; i < key_count; i++)
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
			if ((MAX_INPUT != count_numb) || (numbers[0] > 5) || (numbers[0] <= 0))
			{
				for (int i = 0; i < key_count; i++)
				{
					str[i] = '\0';
				}
				key_count = 0;
				isInput = false;
			}
			else // 정상 입력시 처리, numbers[2] 단수
			{
				str[key_count] = '\0';

				save_shape[shape_count].shape = numbers[0];
				save_shape[shape_count].x1 = numbers[1];
				save_shape[shape_count].y1 = numbers[2];
				save_shape[shape_count].x2 = numbers[3];
				save_shape[shape_count].y2 = numbers[4];
				save_shape[shape_count].thick = numbers[5];
				shape_count++;
				isInput = true;
			}
		}
		else
		{
			if (MAX_LENGTH == key_count)
				break;
			else
			{
				str[key_count++] = wParam;
				str[key_count] = '\0';
			}
		}
		TextOut(hdc, 0, 0, str, lstrlen(str));
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
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
	InvalidateRect(hWnd, NULL, TRUE);
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &C);

		shape_info& s = save_shape[shape_count];

		if (1 == s.shape) // 직선
		{
			hBrush = CreateSolidBrush(RGB(t_r, t_g, t_b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			MoveToEx(hdc, s.x1, s.y1, NULL);
			LineTo(hdc, s.x2, s.y2);
		}
		if (2 == s.shape) // 삼각형
		{
			hBrush = CreateSolidBrush(RGB(t_r, t_g, t_b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			POINT Tri[6] = { {(s.x1 + s.x2) / 2 ,s.y1},{s.x1,s.y2},{s.x2,s.y2} };
			Polygon(hdc, Tri, 3); // 삼각형
		}
		if (3 == s.shape) // 사각형
		{
			hBrush = CreateSolidBrush(RGB(t_r, t_g, t_b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, s.x1, s.y1, s.x2, s.y2);
		}
		if (4 == save_shape[shape_count].shape) // 원
		{
			hBrush = CreateSolidBrush(RGB(t_r, t_g, t_b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, s.x1, s.y1, s.x2, s.y2);
		}

		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}