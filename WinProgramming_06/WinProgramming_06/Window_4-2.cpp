#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <stdlib.h>
#include "resource.h"

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
	DIR dir;
	RECT rect;
};

struct OBS
{
	short pos_x, pos_y;
	bool isSet;
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	Window = CreateWindow(lpszClass, L"windows program 4-2", WS_OVERLAPPEDWINDOW,
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
	static RECT npc2_range;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	POINT mouse;
	static vector <OBS> obstacle;

	static NPC tail20[20];
	static NPC tail30[30];
	static NPC tail25[25];
	static NPC* tail;

	static RECT Board[DIVIDE_HEIGHT][DIVIDE_WIDTH];
	static short pos_x, pos_y, dir_x, dir_y;
	static short TAIL_LENGTH;
	static short head_r, head_g, head_b;

	static bool isMoving, isBooster, isCollision, isObs, isCircle;
	static int player_timer;
	static int npc_timer1;
	static int npc_timer2;
	static float r;
	static short booster_count, npc_summon_count, big_ball_count, ob_count;
	static DIR dir, dir_temp1, dir_temp2;
	static NPC npc1;
	static NPC npc2;

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
		isCollision = false;
		isObs = false;
		booster_count = 0;
		
		player_timer = 100;
		npc_timer1 = 100;
		npc_timer2 = 70;

		r = C.right / 80;

		dir = DIR_RIGHT;
		pos_x = 0;
		pos_y = 0;
		isCircle = true;

		head_r = 255, head_g = 255, head_b = 0;
		TAIL_LENGTH = 20;
		tail = tail20;
		ob_count = 0;

		npc1.pos_x = rand() % DIVIDE_MAX; // 정상
		npc1.pos_y = rand() % DIVIDE_MAX;
		npc1.isSummon = true;
		npc1.dir = (DIR)(rand() % 4);

		//npc1.pos_x = 5; // npc 충돌 테스트
		//npc1.pos_y = 10;
		//npc1.isSummon = true;
		//npc1.dir = DIR_DOWN;

		//npc2_range.left = 5; // npc충돌테스트
		//npc2_range.top = 5;
		//npc2_range.right = 6;
		//npc2_range.bottom = 10;

		npc2_range.left = rand() % 19; // 정상
		npc2_range.top = rand() % 19;
		npc2_range.right = rand() % 20 + 19;
		npc2_range.bottom = rand() % 20 + 19;

		npc2.pos_x = npc2_range.left;
		npc2.pos_y = npc2_range.top;
		npc2.isSummon = true;
		npc2.dir = DIR_DOWN;
		
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_GAME_START:
			isMoving = true;
			SetTimer(hWnd, 1, player_timer, NULL); // 플레이어
			SetTimer(hWnd, 2, npc_timer1, NULL); // npc
			SetTimer(hWnd, 3, npc_timer2, NULL); // npc
			break;
		case ID_GAME_RESET:
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);
			for (int i = 0; i < TAIL_LENGTH; ++i)
			{
				tail[i].isSummon = false;
			}
			obstacle.clear();
			ob_count = 0;
			isMoving = false;
			isBooster = false;
			isCollision = false;
			isObs = false;
			booster_count = 0;

			pos_x = 0;
			pos_y = 0;
			dir = DIR_RIGHT;
			isCircle = true;

			npc1.pos_x = rand() % DIVIDE_MAX; // 정상
			npc1.pos_y = rand() % DIVIDE_MAX;
			npc1.isSummon = true;
			npc1.dir = (DIR)(rand() % 4);
			npc2_range.left = rand() % 19; // 정상
			npc2_range.top = rand() % 19;
			npc2_range.right = rand() % 20 + 19;
			npc2_range.bottom = rand() % 20 + 19;

			npc2.pos_x = npc2_range.left;
			npc2.pos_y = npc2_range.top;
			npc2.isSummon = true;
			npc2.dir = DIR_DOWN;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_GAME_END:
			PostQuitMessage(0);
			break;
		case ID_SPEED_FAST:
			SetTimer(hWnd, 1, player_timer - 40, NULL);// 플레이어
			SetTimer(hWnd, 2, npc_timer1 - 40, NULL); // npc
			SetTimer(hWnd, 3, npc_timer2 - 40, NULL); // npc
			break;
		case ID_SPEED_MEDIUM:
			SetTimer(hWnd, 1, player_timer, NULL); // 플레이어
			SetTimer(hWnd, 2, npc_timer1, NULL); // npc
			SetTimer(hWnd, 3, npc_timer2, NULL); // npc
			break;
		case ID_SPEED_SLOW:
			SetTimer(hWnd, 1, player_timer + 40, NULL);;// 플레이어
			SetTimer(hWnd, 2, npc_timer1 + 40, NULL); // npc
			SetTimer(hWnd, 3, npc_timer2 + 40, NULL); // npc
			break;
		case ID_COLOR_CYAN:
			head_r = 0, head_g = 255, head_b = 255;
			break;
		case ID_COLOR_MAGENTA:
			head_r = 255, head_g = 0, head_b = 255;
			break;
		case ID_COLOR_YELLOW:
			head_r = 255, head_g = 255, head_b = 0;
			break;
		case ID_SHAPE_CIRCLE:
			isCircle = true;
			break;
		case ID_SHAPE_SQUARE:
			isCircle = false;
			break;
		case ID_TAIL_20:
			for (int i = 0; i < 20; ++i)
			{
				tail20[i] = tail[i];
			}
			if (tail25 == tail)
			{
				for (int i = 20; i < 25; ++i)
					tail25[i].isSummon = false;
			}
			if (tail30 == tail)
			{
				for (int i = 20; i < 30; ++i)
					tail30[i].isSummon = false;
			}
			tail = tail20;
			TAIL_LENGTH = 20;
			break;
		case ID_TAIL_25:
			for (int i = 0; i < 25; ++i)
			{
				if (tail20 == tail)
				{
					if (20 == i)
					{
						for (int i = 0; i < 20; ++i)
							tail20[i].isSummon = false;
						break;
					}
				}

				tail25[i] = tail[i];
			}
			if (tail30 == tail)
			{
				for (int i = 25; i < 30; ++i)
					tail30[i].isSummon = false;
			}
			tail = tail25;
			TAIL_LENGTH = 25;
			break;
		case ID_TAIL_30:
			for (int i = 0; i < 30; ++i)
			{
				if (tail20 == tail)
					if (20 == i)
					{
						for (int i = 0; i < 20; ++i)
							tail20[i].isSummon = false;
						break;
					}

				if (tail25 == tail)
					if (25 == i)
					{
						for (int i = 0; i < 25; ++i)
							tail25[i].isSummon = false;
						break;
					}
				tail30[i] = tail[i];
			}
			tail = tail30;
			TAIL_LENGTH = 30;
			break;
		}
	}
	break;
	case WM_TIMER:
	{
		GetClientRect(hWnd, &C);
		switch (wParam)
		{
		case 1: // 플레이어
		{
			if (true == isBooster)
				booster_count++;
			if (true == isMoving)
			{
				RECT rect = { C.left + pos_x * C.right / 40 + 1, C.top + pos_y * C.bottom / 40 + 1,
				C.left + (pos_x + 1) * C.right / 40 - 1, C.top + (pos_y + 1) * C.bottom / 40 - 1 };

				tail[0].pos_x = pos_x;
				tail[0].pos_y = pos_y;
				tail[0].dir = dir;

				for (int i = TAIL_LENGTH - 1; i > 0; --i)
				{
					if (tail[i].isSummon)
					{
						tail[i].pos_x = tail[i - 1].pos_x;
						tail[i].pos_y = tail[i - 1].pos_y;
						tail[i].dir = tail[i - 1].dir;
					}
				}
				if (DIR_UP == dir)
				{
					DIR temp = dir;
					for (auto& a : obstacle)
					{
						if (a.pos_x == pos_x && a.pos_y == pos_y - 1)
						{
							dir = DIR_RIGHT;
							break;
						}

					}

					if (temp != dir)
						break;

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
					DIR temp = dir;
					for (auto& a : obstacle)
					{
						if (a.pos_x == pos_x && a.pos_y == pos_y + 1)
						{
							dir = DIR_LEFT;
							break;
						}
					}

					if (temp != dir)
						break;

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
					DIR temp = dir;
					for (auto& a : obstacle)
					{
						if (a.pos_x == pos_x - 1 && a.pos_y == pos_y)
						{
							dir = DIR_DOWN;
							break;
						}
					}

					if (temp != dir)
						break;

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
					DIR temp = dir;
					for (auto& a : obstacle)
					{
						if (a.pos_x == pos_x + 1 && a.pos_y == pos_y)
						{
							dir = DIR_UP;
							break;
						}
					}

					if (temp != dir)
						break;

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
				InvalidateRect(hWnd, NULL, FALSE);
			}
		}
		break;
		case 2: // npc 직선
		{
			npc1.rect = { C.left + npc1.pos_x * C.right / 40 + 1, C.top + npc1.pos_y * C.bottom / 40 + 1,
			C.left + (npc1.pos_x + 1) * C.right / 40 - 1, C.top + (npc1.pos_y + 1) * C.bottom / 40 - 1 };
			InvalidateRect(hWnd, &npc1.rect, FALSE);
			if (DIR_UP == npc1.dir)
			{
				DIR temp = npc1.dir;
				for (auto& a : obstacle)
				{
					if (a.pos_x == npc1.pos_x && a.pos_y == npc1.pos_y-1)
					{
						npc1.dir = DIR_RIGHT;
						break;
					}
				}

				if (temp != npc1.dir)
					break;

				if (0 == npc1.pos_y)
					npc1.dir = DIR_DOWN;
				else
					npc1.pos_y -= 1;
			}
			else if (DIR_DOWN == npc1.dir)
			{
				DIR temp = npc1.dir;
				for (auto& a : obstacle)
				{
					if (a.pos_x == npc1.pos_x && a.pos_y == npc1.pos_y + 1)
					{
						npc1.dir = DIR_LEFT;
						break;
					}
				}

				if (temp != npc1.dir)
					break;

				if (39 == npc1.pos_y)
					npc1.dir = DIR_UP;
				else
					npc1.pos_y += 1;
			}
			else if (DIR_LEFT == npc1.dir)
			{
				DIR temp = npc1.dir;
				for (auto& a : obstacle)
				{
					if (a.pos_x == npc1.pos_x -1 && a.pos_y == npc1.pos_y)
					{
						npc1.dir = DIR_DOWN;
						break;
					}
				}

				if (temp != npc1.dir)
					break;

				if (0 == npc1.pos_x)
					npc1.dir = DIR_RIGHT;
				else
					npc1.pos_x -= 1;
			}
			else if (DIR_RIGHT == npc1.dir)
			{
				DIR temp = npc1.dir;
				for (auto& a : obstacle)
				{
					if (a.pos_x == npc1.pos_x+1 && a.pos_y == npc1.pos_y)
					{
						npc1.dir = DIR_UP;
						break;
					}
				}

				if (temp != npc1.dir)
					break;

				if (39 == npc1.pos_x)
					npc1.dir = DIR_LEFT;
				else
					npc1.pos_x += 1;
			}
			npc1.rect = { C.left + npc1.pos_x * C.right / 40 + 1, C.top + npc1.pos_y * C.bottom / 40 + 1,
			C.left + (npc1.pos_x + 1) * C.right / 40 - 1, C.top + (npc1.pos_y + 1) * C.bottom / 40 - 1 };
			InvalidateRect(hWnd, &npc1.rect, FALSE);
		}
		break;
		case 3:
		{
			{
				npc2.rect = { C.left + npc2.pos_x * C.right / 40 + 1, C.top + npc2.pos_y * C.bottom / 40 + 1,
				C.left + (npc2.pos_x + 1) * C.right / 40 - 1, C.top + (npc2.pos_y + 1) * C.bottom / 40 - 1 };
				InvalidateRect(hWnd, &npc2.rect, FALSE);
				if (DIR_UP == npc2.dir)
				{
					DIR temp = npc2.dir;
					for (auto& a : obstacle)
					{
						if (a.pos_x == npc2.pos_x && a.pos_y == npc2.pos_y - 1)
						{
							npc2.dir = DIR_LEFT;
							break;
						}
					}

					if (temp != npc2.dir)
						break;
					if (npc2_range.top == npc2.pos_y)
						npc2.dir = DIR_LEFT;
					else
						npc2.pos_y -= 1;
				}
				else if (DIR_DOWN == npc2.dir)
				{
					DIR temp = npc2.dir;
					for (auto& a : obstacle)
					{
						if (a.pos_x == npc2.pos_x && a.pos_y == npc2.pos_y + 1)
						{
							npc2.dir = DIR_RIGHT;
							break;
						}
					}

					if (temp != npc2.dir)
						break;
					if (npc2_range.bottom-1 == npc2.pos_y)
						npc2.dir = DIR_RIGHT;
					else
						npc2.pos_y += 1;
				}
				else if (DIR_LEFT == npc2.dir)
				{
					DIR temp = npc2.dir;
					for (auto& a : obstacle)
					{
						if (a.pos_x == npc2.pos_x - 1 && a.pos_y == npc2.pos_y)
						{
							npc2.dir = DIR_DOWN;
							break;
						}
					}

					if (temp != npc2.dir)
						break;
					if (npc2_range.left == npc2.pos_x)
						npc2.dir = DIR_DOWN;
					else
						npc2.pos_x -= 1;
				}
				else if (DIR_RIGHT == npc2.dir)
				{
					DIR temp = npc2.dir;
					for (auto& a : obstacle)
					{
						if (a.pos_x == npc2.pos_x + 1 && a.pos_y == npc2.pos_y)
						{
							npc2.dir = DIR_UP;
							break;
						}
					}

					if (temp != npc2.dir)
						break;
					if (npc2_range.right-1 == npc2.pos_x)
						npc2.dir = DIR_UP;
					else
						npc2.pos_x += 1;
				}
				npc2.rect = { C.left + npc2.pos_x * C.right / 40 + 1, C.top + npc2.pos_y * C.bottom / 40 + 1,
				C.left + (npc2.pos_x + 1) * C.right / 40 - 1, C.top + (npc2.pos_y + 1) * C.bottom / 40 - 1 };
				InvalidateRect(hWnd, &npc2.rect, FALSE);
			}

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

		if (npc1.pos_x == npc2.pos_x && npc1.pos_y == npc2.pos_y)
		{
			if (!isCollision)
			{
				dir_temp1 = npc1.dir;
				dir_temp2 = npc2.dir;

				npc1.dir = DIR_END;
				npc2.dir = DIR_END;

				isCollision = true;
				
			}
			else
			{
				big_ball_count++;
				if (15 == big_ball_count)
				{
					isCollision = false;
					npc1.dir = dir_temp1;
					npc2.dir = dir_temp2;
					big_ball_count = 0;
				}
			}
			RECT rect = { npc2.pos_x * C.right / 40 - 10, C.top + npc2.pos_y * C.bottom / 40 - 10,
				C.left + (npc2.pos_x + 1) * C.right / 40 + 10, C.top + (npc2.pos_y + 1) * C.bottom / 40 + 10 };
			InvalidateRect(hWnd, &rect, FALSE);
		}

		if (pos_x == npc1.pos_x && pos_y == npc1.pos_y)
		{
			for (int i = 1; i < TAIL_LENGTH; ++i)
			{
				if (!tail[i].isSummon)
				{
					if (DIR_DOWN == tail[i - 1].dir)
					{
						tail[i].pos_x = tail[i - 1].pos_x;
						tail[i].pos_y = tail[i - 1].pos_y - 1;
					}
					else if (DIR_UP == tail[i - 1].dir)
					{
						tail[i].pos_x = tail[i - 1].pos_x;
						tail[i].pos_y = tail[i - 1].pos_y + 1;
					}
					else if (DIR_LEFT == tail[i - 1].dir)
					{
						tail[i].pos_x = tail[i - 1].pos_x+1;
						tail[i].pos_y = tail[i - 1].pos_y;
					}
					else if (DIR_RIGHT == tail[i - 1].dir)
					{
						tail[i].pos_x = tail[i - 1].pos_x - 1;
						tail[i].pos_y = tail[i - 1].pos_y;
					}
					tail[i].dir = tail[i - 1].dir;
					tail[i].isSummon = true;
					npc1.pos_x = rand() % 40;
					npc1.pos_y = rand() % 40;
					npc1.dir = DIR(rand() % 4);
					SetTimer(hWnd, 2, npc_timer1, NULL); // npc
					break;
				}
			}
		}

		if (pos_x == npc2.pos_x && pos_y == npc2.pos_y)
		{
			for (int i = 1; i < TAIL_LENGTH; ++i)
			{
				if (!tail[i].isSummon)
				{
					if (DIR_DOWN == tail[i - 1].dir)
					{
						tail[i].pos_x = tail[i - 1].pos_x;
						tail[i].pos_y = tail[i - 1].pos_y - 1;
					}
					else if (DIR_UP == tail[i - 1].dir)
					{
						tail[i].pos_x = tail[i - 1].pos_x;
						tail[i].pos_y = tail[i - 1].pos_y + 1;
					}
					else if (DIR_LEFT == tail[i - 1].dir)
					{
						tail[i].pos_x = tail[i - 1].pos_x + 1;
						tail[i].pos_y = tail[i - 1].pos_y;
					}
					else if (DIR_RIGHT == tail[i - 1].dir)
					{
						tail[i].pos_x = tail[i - 1].pos_x - 1;
						tail[i].pos_y = tail[i - 1].pos_y;
					}
					tail[i].dir = tail[i - 1].dir;
					tail[i].isSummon = true;

					npc2_range.left = rand() % 19;
					npc2_range.top = rand() % 19;
					npc2_range.right = rand() % 20 + 19;
					npc2_range.bottom = rand() % 20 + 19;

					npc2.pos_x = npc2_range.left;
					npc2.pos_y = npc2_range.top;
					npc2.isSummon = true;
					npc2.dir = DIR_DOWN;
					SetTimer(hWnd, 3, npc_timer2, NULL); // npc
					break;
				}
			}
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
	case WM_LBUTTONUP:
	{
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
		hdc = GetDC(hWnd);
		GetClientRect(hWnd, &C);
		float temp = (((pos_x * C.right / 40) + C.right / 80) - mouse.x) * (((pos_x * C.right / 40) + C.right / 80) - mouse.x)
			+ (((pos_y * C.bottom / 40) + C.bottom / 80) - mouse.y) * (((pos_y * C.bottom / 40) + C.bottom / 80) - mouse.y);
		if (r * r > temp)
		{
			if (false == isBooster)
			{
				isBooster = true;
				SetTimer(hWnd, 1, player_timer - 80, NULL);
			}
		}
		else if (abs(mouse.x - (pos_x * C.right / 40)) < abs(mouse.y - (pos_y * C.bottom / 40))) // 세로 차이가 더 클때
		{
			if ((pos_y * C.bottom / 40) > mouse.y)
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
			if ((pos_x * C.right / 40) > mouse.x)
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
	case WM_RBUTTONUP:
	{
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
		for (int i = 0; i < DIVIDE_HEIGHT; ++i)
		{
			int temp = ob_count;
			for (int j = 0; j < DIVIDE_WIDTH; ++j)
			{
				RECT rect = { Board[i][j].left, Board[i][j].top, Board[i][j].right, Board[i][j].bottom };
				if (PtInRect(&rect, mouse))
				{
					OBS temp;
					temp.isSet = true;
					temp.pos_x = j;
					temp.pos_y = i;
					obstacle.emplace_back(temp);
					ob_count++;
					break;
				}
			}
			if (temp != ob_count)
				break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
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

		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		
		if (0 != obstacle.size())
		{
			for (auto& a : obstacle)
				Rectangle(hdc, C.left + a.pos_x * C.right / 40 + 1, C.top + a.pos_y * C.bottom / 40 + 1,
					C.left + (a.pos_x + 1) * C.right / 40 - 1, C.top + (a.pos_y + 1) * C.bottom / 40 - 1);
		}

		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		RECT rect = { C.left + npc2_range.left * C.right / 40 + 1, C.top + npc2_range.top * C.bottom / 40 + 1,
			C.left + npc2_range.right * C.right / 40 - 1, C.top + npc2_range.bottom * C.bottom / 40 - 1 };
		FrameRect(hdc, &rect, hBrush);

		hBrush = CreateSolidBrush(RGB(head_r, head_g, head_b));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		if (isCircle)
			Ellipse(hdc, C.left + (pos_x * C.right / 40) + 1, C.top + (pos_y * C.bottom / 40) + 1,
				C.left + ((pos_x + 1) * C.right / 40) - 1, C.top + ((pos_y + 1) * C.bottom / 40) - 1);
		else
			Rectangle(hdc, C.left + (pos_x * C.right / 40) + 1, C.top + (pos_y * C.bottom / 40) + 1,
				C.left + ((pos_x + 1) * C.right / 40) - 1, C.top + ((pos_y + 1) * C.bottom / 40) - 1);

		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, C.left + npc1.pos_x * C.right / 40 + 1, C.top + npc1.pos_y * C.bottom / 40 + 1,
			C.left + (npc1.pos_x + 1) * C.right / 40 - 1, C.top + (npc1.pos_y + 1) * C.bottom / 40 - 1);

		Ellipse(hdc, C.left + npc2.pos_x * C.right / 40 + 1, C.top + npc2.pos_y * C.bottom / 40 + 1,
			C.left + (npc2.pos_x + 1) * C.right / 40 - 1, C.top + (npc2.pos_y + 1) * C.bottom / 40 - 1);

		if (isCollision)
		{
			Ellipse(hdc, C.left + npc2.pos_x * C.right / 40 - 10, C.top + npc2.pos_y * C.bottom / 40 - 10,
				C.left + (npc2.pos_x + 1) * C.right / 40 + 10, C.top + (npc2.pos_y + 1) * C.bottom / 40 + 10);
		}


		for (int i = 0; i < TAIL_LENGTH; ++i)
		{
			if (tail[i].isSummon)
			{
				Ellipse(hdc, C.left + tail[i].pos_x * C.right / 40 + 1, C.top + tail[i].pos_y * C.bottom / 40 + 1,
					C.left + (tail[i].pos_x + 1) * C.right / 40 - 1, C.top + (tail[i].pos_y + 1) * C.bottom / 40 - 1);
			}
		}
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}