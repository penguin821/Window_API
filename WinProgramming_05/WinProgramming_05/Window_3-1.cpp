#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <stdlib.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 800;

constexpr int DIVIDE_WIDTH = 40;
constexpr int DIVIDE_HEIGHT = 40;
constexpr int DIVIDE_MAX = 40;

constexpr short EMPTY = 0;
constexpr short BLOCK = 1;
constexpr short COLOR = 2;
constexpr short SIZECHANGE = 3;
constexpr short PLAYER1 = 4;
constexpr short PLAYER2 = 5;
enum DIR { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_END };

using namespace std;

struct NPC 
{
	bool isSummon;
	short pos_x, pos_y;
	short pattern;
	DIR dir;
	RECT rect;
};

struct node
{
	struct node* next;    // 다음 노드의 주소를 저장할 포인터
	NPC data;             // 데이터를 저장할 멤버
};

void addNode(node* target, NPC npc)    // 기준 노드 뒤에 노드를 추가하는 함수
{
	node* newNode = new node; // 새 노드 생성
	newNode->next = target->next;    // 새 노드의 다음 노드에 기준 노드의 다음 노드를 지정
	newNode->data = npc;            // 데이터 저장

	target->next = newNode;    // 기준 노드의 다음 노드에 새 노드를 지정
}

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

	static vector<NPC> follow_player; 
	static RECT Board[DIVIDE_HEIGHT][DIVIDE_WIDTH];
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
		hdc = GetDC(hWnd);
		GetClientRect(hWnd, &C);
		for (int i = 0; i < DIVIDE_HEIGHT; ++i)
		{
			for (int j = 0; j < DIVIDE_WIDTH; ++j)
			{
				Board[i][j] = { C.left + j * C.right / 40,C.top + i * C.bottom / 40,
					C.left + (j + 1) * C.right / 40,C.top + (i + 1) * C.bottom / 40 };
			}
		}
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
		ReleaseDC(hWnd, hdc);
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
				RECT rect = { C.left + pos_x * C.right / 40 + 1, C.top + pos_y * C.bottom / 40 + 1,
				C.left + (pos_x + 1) * C.right / 40 - 1, C.top + (pos_y + 1) * C.bottom / 40 - 1 };
				InvalidateRect(hWnd, &rect, FALSE);
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
				 rect = { C.left + pos_x * C.right / 40 + 1, C.top + pos_y * C.bottom / 40 + 1,
				C.left + (pos_x + 1) * C.right / 40 - 1, C.top + (pos_y + 1) * C.bottom / 40 - 1 };
				InvalidateRect(hWnd, &rect, FALSE);
			}
			break;
		case 2: // npc
		{
			npc.rect = { C.left + npc.pos_x * C.right / 40 + 1, C.top + npc.pos_y * C.bottom / 40 + 1,
			C.left + (npc.pos_x + 1) * C.right / 40 - 1, C.top + (npc.pos_y + 1) * C.bottom / 40 - 1 };
			InvalidateRect(hWnd, &npc.rect, FALSE);
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
			npc.rect = { C.left + npc.pos_x * C.right / 40 + 1, C.top + npc.pos_y * C.bottom / 40 + 1,
			C.left + (npc.pos_x + 1) * C.right / 40 - 1, C.top + (npc.pos_y + 1) * C.bottom / 40 - 1 };
			InvalidateRect(hWnd, &npc.rect, FALSE);
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
		switch (wParam)
		{
		case '+':
		case '=':
			if (200 >= player_timer)
			{
				player_timer += 10;
				SetTimer(hWnd, 1, player_timer, NULL);
			}
			break;
		case 'S':
		case 's':
			if (false == isMoving)
			{
				isMoving = true;
				SetTimer(hWnd, 1, player_timer, NULL); // 플레이어
			}
			else
				isMoving = false;
			break;
		case '-':
		case '_':
			if (90 <= player_timer)
			{
				player_timer -= 10;
				SetTimer(hWnd, 1, player_timer, NULL);
			}
			break;
		case 'J':
		case 'j':
			break;
		case 'T':
		case 't':
			break;
		case 'Q':
		case 'q':
			PostQuitMessage(0);
			break;
		}
	}
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
		float temp = (((pos_x * C.right / 40) + C.right / 80) - mouse_x) * (((pos_x * C.right / 40) + C.right / 80) - mouse_x)
			+ (((pos_y * C.bottom / 40) + C.bottom / 80) - mouse_y) * (((pos_y * C.bottom / 40) + C.bottom / 80) - mouse_y);
		if (r*r > temp)
		{
			if (false == isBooster)
			{
				isBooster = true;
				SetTimer(hWnd, 1, player_timer - 80, NULL);
			}
		}
		else if (abs(mouse_x - (pos_x * C.right / 40)) < abs(mouse_y - (pos_y * C.bottom / 40))) // 세로 차이가 더 클때
		{
			if ((pos_y * C.bottom / 40) > mouse_y)
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
			if ((pos_x * C.right / 40) > mouse_x)
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
		for (int i = 0; i < DIVIDE_HEIGHT; ++i)
		{
			for (int j = 0; j < DIVIDE_WIDTH; ++j)
			{
				Rectangle(hdc, Board[i][j].left, Board[i][j].top, Board[i][j].right, Board[i][j].bottom);
			}
		}

		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, C.left + (pos_x * C.right / 40) + 1, C.top + (pos_y * C.bottom / 40) + 1,
			C.left + ((pos_x + 1) * C.right / 40) - 1, C.top + ((pos_y + 1) * C.bottom / 40) - 1);

		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		//hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
		//oldPen = (HPEN)SelectObject(hdc, hPen);
		Ellipse(hdc, C.left + npc.pos_x * C.right / 40 + 1, C.top + npc.pos_y * C.bottom / 40 + 1,
			C.left + (npc.pos_x + 1) * C.right / 40 - 1, C.top + (npc.pos_y + 1) * C.bottom / 40 - 1);

		//SelectObject(hdc, oldPen);
		//DeleteObject(hPen);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
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