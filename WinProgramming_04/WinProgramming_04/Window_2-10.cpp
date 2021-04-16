#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <map>

using namespace std;

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 800;

constexpr int DIVIDE_MAX = 50;

constexpr short EMPTY = 0;
constexpr short BLOCK = 1;
constexpr short COLOR = 2;
constexpr short SIZECHANGE = 3;
constexpr short PLAYER1 = 4;
constexpr short PLAYER2 = 5;
enum DIR { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_END };

struct NPC
{
	bool isSummon;
	short pos_x, pos_y;
	short pattern;
	DIR dir;
};

struct shape_info
{
	short shape, pos_x, pos_y;
	bool isSelect;
	short r, g, b, x1, x2, y1, y2;
	short p_r, p_g, p_b;
	bool isDraw = false;
};

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window1";
LRESULT CALLBACK WndProc1(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
enum Shape { SP_X, SP_EXTRI, SP_DIA, SP_BUTR, SP_SAND, SP_EMPTYSQ, SP_END };

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
	Window = CreateWindow(lpszClass, L"windows program 3-1", WS_OVERLAPPEDWINDOW,
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

	static bool isFirst;
	static int DIVIDE_NOW;
	static map <int, shape_info> save_shape;
	static RECT Board[DIVIDE_MAX][DIVIDE_MAX];
	static int shape_count;
	static short select;

	static short board_mode;
	static short pos_x, pos_y, dir_x, dir_y, mouse_x, mouse_y;
	static bool isMoving, isBooster;
	static int player_timer;
	static int npc_timer;
	static float r;
	static short booster_count, npc_summon_count;
	static DIR dir;
	static NPC npc;


	switch (uMsg)
	{
	case WM_CREATE:
	{
		shape_count = 0;
		isFirst = true;
		DIVIDE_NOW = 30;
		GetClientRect(hWnd, &C);
		isMoving = false;
		isBooster = false;
		booster_count = 0;
		dir = DIR_END;
		player_timer = 150;
		npc_timer = 200;
		r = C.right / 80;
		pos_x = 0;
		pos_y = 0;

		npc.pos_x = rand() % 40;
		npc.pos_y = rand() % 40;
		npc.isSummon = true;
		npc.dir = DIR(rand() % 4);
		SetTimer(hWnd, 2, npc_timer, NULL); // npc
	}
	break;
	case WM_TIMER:
	{
		GetClientRect(hWnd, &C);
		switch (wParam)
		{
		case 1: // 플레이어
			if (true == isBooster)
				booster_count++;
			if (true == isMoving)
			{
				hdc = GetDC(hWnd);
				SetROP2(hdc, R2_XORPEN);
				SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
				SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(0, 0, 255)));
				Ellipse(hdc, C.left + pos_x * C.right / DIVIDE_NOW + 1, C.top + pos_y * C.bottom / DIVIDE_NOW + 1,
					C.left + (pos_x + 1) * C.right / DIVIDE_NOW - 1, C.top + (pos_y + 1) * C.bottom / DIVIDE_NOW - 1);
				if (DIR_UP == dir)
				{
					if (0 == pos_y)
					{
						if (39 != pos_x)
							pos_x += 1;
						else
							pos_x = 0;
						dir = DIR_DOWN;
					}
					else
						pos_y -= 1;
				}
				else if (DIR_DOWN == dir)
				{
					if (39 == pos_y)
					{
						if (39 != pos_x)
							pos_x += 1;
						else
							pos_x = 0;
						dir = DIR_UP;
					}
					else
						pos_y += 1;
				}
				else if (DIR_LEFT == dir)
				{
					if (0 == pos_x)
					{
						if (39 != pos_y)
							pos_y += 1;
						else
							pos_y = 0;
						dir = DIR_RIGHT;
					}
					else
						pos_x -= 1;
				}
				else if (DIR_RIGHT == dir)
				{
					if (39 == pos_x)
					{
						if (39 != pos_y)
							pos_y += 1;
						else
							pos_y = 0;
						dir = DIR_LEFT;
					}
					else
						pos_x += 1;
				}
				Ellipse(hdc, C.left + (pos_x * C.right / DIVIDE_NOW) + 1, C.top + (pos_y * C.bottom / DIVIDE_NOW) + 1,
					C.left + ((pos_x + 1) * C.right / DIVIDE_NOW) - 1, C.top + ((pos_y + 1) * C.bottom / DIVIDE_NOW) - 1);
				ReleaseDC(hWnd, hdc);
			}
			break;
		case 2: // npc
		{
			hdc = GetDC(hWnd);
			SetROP2(hdc, R2_XORPEN);
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
			SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(0, 255, 255)));
			Ellipse(hdc, C.left + npc.pos_x * C.right / DIVIDE_NOW + 1, C.top + npc.pos_y * C.bottom / DIVIDE_NOW + 1,
				C.left + (npc.pos_x + 1) * C.right / DIVIDE_NOW - 1, C.top + (npc.pos_y + 1) * C.bottom / DIVIDE_NOW - 1);
			if (DIR_UP == npc.dir)
			{
				if (0 == npc.pos_y)
					npc.dir = DIR_DOWN;
				else
					npc.pos_y -= 1;
			}
			else if (DIR_DOWN == npc.dir)
			{
				if (39 == npc.pos_y)
					npc.dir = DIR_UP;
				else
					npc.pos_y += 1;
			}
			else if (DIR_LEFT == npc.dir)
			{
				if (0 == npc.pos_x)
					npc.dir = DIR_RIGHT;
				else
					npc.pos_x -= 1;
			}
			else if (DIR_RIGHT == npc.dir)
			{
				if (39 == npc.pos_x)
					npc.dir = DIR_LEFT;
				else
					npc.pos_x += 1;
			}
			Ellipse(hdc, C.left + npc.pos_x * C.right / DIVIDE_NOW + 1, C.top + npc.pos_y * C.bottom / DIVIDE_NOW + 1,
				C.left + (npc.pos_x + 1) * C.right / DIVIDE_NOW - 1, C.top + (npc.pos_y + 1) * C.bottom / DIVIDE_NOW - 1);
			ReleaseDC(hWnd, hdc);
		}
		break;
		default:
			break;
		}
		if (20 == booster_count)
		{
			isBooster = false;
			booster_count = 0;
			SetTimer(hWnd, 1, player_timer, NULL);
		}
	}
	break;
	case WM_CHAR:
	{
		GetClientRect(hWnd, &C);
		switch (wParam)
		{
		case 'S':
		case 's':
			DIVIDE_NOW = 30;
			board_mode = 1;
			break;
		case 'M':
		case 'm':
			DIVIDE_NOW = 40;
			board_mode = 2;
			break;
		case 'L':
		case 'l':
			DIVIDE_NOW = 50;
			board_mode = 3;
			break;
		case 'E':
		case 'e': // 원
			if (false == isFirst)
				shape_count++;

			save_shape[shape_count].shape = 0;
			save_shape[shape_count].pos_x = rand() % DIVIDE_NOW;
			save_shape[shape_count].pos_y = rand() % DIVIDE_NOW;
			save_shape[shape_count].x1 = C.left + save_shape[shape_count].pos_x * C.right / DIVIDE_NOW;
			save_shape[shape_count].x2 = C.left + (save_shape[shape_count].pos_x + 1) * C.right / DIVIDE_NOW;
			save_shape[shape_count].y1 = C.top + save_shape[shape_count].pos_y * C.bottom / DIVIDE_NOW;
			save_shape[shape_count].y2 = C.top + (save_shape[shape_count].pos_y + 1) * C.bottom / DIVIDE_NOW;
			save_shape[shape_count].isSelect = true;
			save_shape[shape_count].r = rand() % 256;
			save_shape[shape_count].g = rand() % 256;
			save_shape[shape_count].b = rand() % 256;
			save_shape[shape_count].p_r = rand() % 256;
			save_shape[shape_count].p_g = rand() % 256;
			save_shape[shape_count].p_b = rand() % 256;
			save_shape[shape_count].isDraw = true;
			isFirst = false;
			select = shape_count;
			break;
		case 'T':
		case 't': // 삼각형
			if (false == isFirst)
				shape_count++;

			save_shape[shape_count].shape = 1;
			save_shape[shape_count].pos_x = rand() % DIVIDE_NOW;
			save_shape[shape_count].pos_y = rand() % DIVIDE_NOW;
			save_shape[shape_count].x1 = C.left + save_shape[shape_count].pos_x * C.right / DIVIDE_NOW;
			save_shape[shape_count].x2 = C.left + (save_shape[shape_count].pos_x + 1) * C.right / DIVIDE_NOW;
			save_shape[shape_count].y1 = C.top + save_shape[shape_count].pos_y * C.bottom / DIVIDE_NOW;
			save_shape[shape_count].y2 = C.top + (save_shape[shape_count].pos_y + 1) * C.bottom / DIVIDE_NOW;
			save_shape[shape_count].isSelect = true;
			save_shape[shape_count].r = rand() % 256;
			save_shape[shape_count].g = rand() % 256;
			save_shape[shape_count].b = rand() % 256;
			save_shape[shape_count].p_r = rand() % 256;
			save_shape[shape_count].p_g = rand() % 256;
			save_shape[shape_count].p_b = rand() % 256;
			save_shape[shape_count].isDraw = true;
			isFirst = false;
			select = shape_count;
			break;
		case 'R':
		case 'r': // 사각형
			if (false == isFirst)
				shape_count++;

			save_shape[shape_count].shape = 2;
			save_shape[shape_count].pos_x = rand() % DIVIDE_NOW;
			save_shape[shape_count].pos_y = rand() % DIVIDE_NOW;
			save_shape[shape_count].x1 = C.left + save_shape[shape_count].pos_x * C.right / DIVIDE_NOW;
			save_shape[shape_count].x2 = C.left + (save_shape[shape_count].pos_x + 1) * C.right / DIVIDE_NOW;
			save_shape[shape_count].y1 = C.top + save_shape[shape_count].pos_y * C.bottom / DIVIDE_NOW;
			save_shape[shape_count].y2 = C.top + (save_shape[shape_count].pos_y + 1) * C.bottom / DIVIDE_NOW;
			save_shape[shape_count].isSelect = true;
			save_shape[shape_count].r = rand() % 256;
			save_shape[shape_count].g = rand() % 256;
			save_shape[shape_count].b = rand() % 256;
			save_shape[shape_count].p_r = rand() % 256;
			save_shape[shape_count].p_g = rand() % 256;
			save_shape[shape_count].p_b = rand() % 256;
			save_shape[shape_count].isDraw = true;
			isFirst = false;
			select = shape_count;
			break;
		case 'Q':
		case 'q':
			PostQuitMessage(0);
			break;
		}
	}
	InvalidateRect(hWnd, NULL, TRUE);
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
			dir = DIR_UP;
			break;
		case VK_DOWN:
			dir = DIR_DOWN;
			break;
		case VK_LEFT:
			dir = DIR_LEFT;
			break;
		case VK_RIGHT:
			dir = DIR_RIGHT;
			break;
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
		mouse_x = LOWORD(lParam);
		mouse_y = HIWORD(lParam);
		hdc = GetDC(hWnd);
		GetClientRect(hWnd, &C);
		float temp = (((pos_x * C.right / DIVIDE_NOW) + C.right / DIVIDE_NOW/2) - mouse_x) *
			(((pos_x * C.right / DIVIDE_NOW) + C.right / DIVIDE_NOW / 2) - mouse_x) +
			(((pos_y * C.bottom / DIVIDE_NOW) + C.bottom / DIVIDE_NOW / 2) - mouse_y) *
			(((pos_y * C.bottom / DIVIDE_NOW) + C.bottom / DIVIDE_NOW / 2) - mouse_y);
		if (r * r > temp)
		{
			if (false == isBooster)
			{
				isBooster = true;
				SetTimer(hWnd, 1, player_timer - 80, NULL);
			}
		}
		else if (abs(mouse_x - (pos_x * C.right / DIVIDE_NOW)) < abs(mouse_y - (pos_y * C.bottom / DIVIDE_NOW))) // 세로 차이가 더 클때
		{
			if ((pos_y * C.bottom / DIVIDE_NOW) > mouse_y)
			{
				dir = DIR_UP;
			}
			else
			{
				dir = DIR_DOWN;
			}
		}
		else // 가로 차이가 더 클때 
		{
			if ((pos_x * C.right / DIVIDE_NOW) > mouse_x)
			{
				dir = DIR_LEFT;
			}
			else
			{
				dir = DIR_RIGHT;
			}
		}
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_RBUTTONDOWN:
	{

	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &C);
		for (int i = 0; i < DIVIDE_NOW; ++i)
		{
			for (int j = 0; j < DIVIDE_NOW; ++j)
			{
				Board[i][j] = { C.left + j * C.right / DIVIDE_NOW,C.top + i * C.bottom / DIVIDE_NOW,
					C.left + (j + 1) * C.right / DIVIDE_NOW,C.top + (i + 1) * C.bottom / DIVIDE_NOW };

				Rectangle(hdc, Board[i][j].left, Board[i][j].top, Board[i][j].right, Board[i][j].bottom);
			}
		}

		for (auto& s : save_shape)
		{
			if (1 == s.second.shape) // 삼각형
			{
				hBrush = CreateSolidBrush(RGB(s.second.r, s.second.g, s.second.b));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				hPen = CreatePen(PS_SOLID, s.second.isSelect, RGB(s.second.p_r, s.second.p_g, s.second.p_b));
				oldPen = (HPEN)SelectObject(hdc, hPen);
				POINT Tri[6] = { {((s.second.pos_x * C.right / DIVIDE_NOW + (s.second.pos_x + 1) * C.right / DIVIDE_NOW)) / 2 ,s.second.pos_y * C.bottom / DIVIDE_NOW},
					{s.second.pos_x * C.right / DIVIDE_NOW, (s.second.pos_y + 1) * C.bottom / DIVIDE_NOW},
					{(s.second.pos_x + 1) * C.right / DIVIDE_NOW, (s.second.pos_y + 1) * C.bottom / DIVIDE_NOW} };
				Polygon(hdc, Tri, 3); // 삼각형
				SelectObject(hdc, oldPen);
				DeleteObject(hPen);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
			}
			if (2 == s.second.shape) // 사각형
			{
				hBrush = CreateSolidBrush(RGB(s.second.r, s.second.g, s.second.b));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				hPen = CreatePen(PS_SOLID, s.second.isSelect, RGB(s.second.p_r, s.second.p_g, s.second.p_b));
				oldPen = (HPEN)SelectObject(hdc, hPen);
				Rectangle(hdc, s.second.pos_x* C.right / DIVIDE_NOW, s.second.pos_y* C.bottom / DIVIDE_NOW, 
					(s.second.pos_x + 1)* C.right / DIVIDE_NOW, (s.second.pos_y + 1)* C.bottom / DIVIDE_NOW);
				SelectObject(hdc, oldPen);
				DeleteObject(hPen);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
			}
			if (3 == s.second.shape) // 원
			{
				hBrush = CreateSolidBrush(RGB(s.second.r, s.second.g, s.second.b));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				hPen = CreatePen(PS_SOLID, s.second.isSelect, RGB(s.second.p_r, s.second.p_g, s.second.p_b));
				oldPen = (HPEN)SelectObject(hdc, hPen);
				Ellipse(hdc, s.second.pos_x* C.right / DIVIDE_NOW, s.second.pos_y* C.bottom / DIVIDE_NOW,
					(s.second.pos_x + 1)* C.right / DIVIDE_NOW, (s.second.pos_y + 1)* C.bottom / DIVIDE_NOW);
				SelectObject(hdc, oldPen);
				DeleteObject(hPen);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
			}
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}