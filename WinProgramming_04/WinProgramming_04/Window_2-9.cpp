#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <map>

using namespace std;

#define _MSG_BOX(MESSAGE) MessageBox(0, TEXT(MESSAGE), TEXT("Error"), MB_OK);

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
	static SIZE input_size;
	static TCHAR str[MAX_LENGTH+1];
	static int key_count = 0;
	static int shape_count;
	static bool isFirst;
	static float numbers[MAX_INPUT];
	static map<int, shape_info> save_shape;
	int count_numb = 0;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		shape_count = 0;
		isFirst = true;
	}
	break;
	case WM_CHAR:
		if (wParam == 'o')
		{
			PostQuitMessage(0);
		}
		if (wParam == 'p'|| wParam == 'P')
		{
			if (0 < shape_count)
				shape_count--;
		}
		if (wParam == 'n'|| wParam == 'N')
		{
			if (false == save_shape[shape_count + 1].isDraw)
				break;
			else
				shape_count++;
		}
		if (wParam == 'k'|| wParam == 'K')
		{
			save_shape[shape_count].r = rand() % 256;
			save_shape[shape_count].g = rand() % 256;
			save_shape[shape_count].b = rand() % 256;
			save_shape[shape_count].p_r = rand() % 256;
			save_shape[shape_count].p_g = rand() % 256;
			save_shape[shape_count].p_b = rand() % 256;
		}
		if (wParam == '+' || wParam == '=')
		{
			if (save_shape[shape_count].thick <= 10)
				save_shape[shape_count].thick++;
			else
			{
				save_shape[shape_count].x2++;
				save_shape[shape_count].y2++;
			}

		}
		if (wParam == '-')
		{
			if (save_shape[shape_count].thick > 1)
				save_shape[shape_count].thick--;
			else
			{
				save_shape[shape_count].x2--;
				save_shape[shape_count].y2--;
			}
		}
		else
			break;
	case WM_KEYDOWN:
		if (wParam == VK_BACK)
		{
			if (0 == key_count)
				break;
			else
				str[--key_count] = '\0';
		}
		if (wParam == VK_RETURN)
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
			if ((MAX_INPUT != count_numb) || (numbers[0] > 5) || (numbers[0] <= 0) || 10 == shape_count)
			{
				for (int i = 0; i < key_count; i++)
				{
					str[i] = '\0';
				}
				key_count = 0;
				if (10 == shape_count)
					MessageBox(0, L"Full !", L"Error", MB_OK);
				else
					MessageBox(0, L"Input shape info first !", L"Error", MB_OK);
			}
			else // 정상 입력시 처리, numbers[2] 단수
			{
				str[key_count] = '\0';

				if (false == isFirst)
					shape_count++;

				save_shape[shape_count].shape = numbers[0];
				save_shape[shape_count].x1 = numbers[1];
				save_shape[shape_count].y1 = numbers[2];
				save_shape[shape_count].x2 = numbers[3];
				save_shape[shape_count].y2 = numbers[4];
				save_shape[shape_count].thick = numbers[5];
				save_shape[shape_count].r = rand() % 256;
				save_shape[shape_count].g = rand() % 256;
				save_shape[shape_count].b = rand() % 256;
				save_shape[shape_count].p_r = rand() % 256;
				save_shape[shape_count].p_g = rand() % 256;
				save_shape[shape_count].p_b = rand() % 256;
				save_shape[shape_count].isDraw = true;
				isFirst = false;
			}
		}
		if (wParam == VK_UP)
		{
			save_shape[shape_count].y1 -= 3;
			save_shape[shape_count].y2 -= 3;
		}
		if (wParam == VK_DOWN)
		{
			save_shape[shape_count].y1 += 3;
			save_shape[shape_count].y2 += 3;
		}
		if (wParam == VK_LEFT)
		{
			save_shape[shape_count].x1 -= 3;
			save_shape[shape_count].x2 -= 3;
		}
		if (wParam == VK_RIGHT)
		{
			save_shape[shape_count].x1 += 3;
			save_shape[shape_count].x2 += 3;
		}
		else
		{
			if (MAX_LENGTH == key_count)
				break;
			else
			{
				if ((48 <= wParam && 57 >= wParam) || 32 == wParam)
				{
					str[key_count++] = wParam;
					str[key_count] = '\0';
				}
			}
		}
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

		GetTextExtentPoint32(hdc, str, lstrlen(str), &input_size);
		TextOut(hdc, 0, 0, str, lstrlen(str));
		SetCaretPos(input_size.cx, 0);

		shape_info& s = save_shape[shape_count];
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		hPen = CreatePen(PS_DOT, s.thick, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);

		if (1 == s.shape) // 직선
		{
			hBrush = CreateSolidBrush(RGB(s.r, s.g, s.b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			hPen = CreatePen(PS_DOT, s.thick, RGB(s.p_r, s.p_g, s.p_b));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			MoveToEx(hdc, s.x1, s.y1, NULL);
			LineTo(hdc, s.x2, s.y2);
		}
		if (2 == s.shape) // 삼각형
		{
			hBrush = CreateSolidBrush(RGB(s.r, s.g, s.b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			hPen = CreatePen(PS_DOT, s.thick, RGB(s.p_r, s.p_g, s.p_b));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			POINT Tri[6] = { {(s.x1 + s.x2) / 2 ,s.y1},{s.x1,s.y2},{s.x2,s.y2} };
			Polygon(hdc, Tri, 3); // 삼각형
		}
		if (3 == s.shape) // 사각형
		{
			hBrush = CreateSolidBrush(RGB(s.r, s.g, s.b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			hPen = CreatePen(PS_DOT, s.thick, RGB(s.p_r, s.p_g, s.p_b));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Rectangle(hdc, s.x1, s.y1, s.x2, s.y2);
		}
		if (4 == save_shape[shape_count].shape) // 원
		{
			hBrush = CreateSolidBrush(RGB(s.r, s.g, s.b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			hPen = CreatePen(PS_DOT, s.thick, RGB(s.p_r, s.p_g, s.p_b));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Ellipse(hdc, s.x1, s.y1, s.x2, s.y2);
		}

		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}