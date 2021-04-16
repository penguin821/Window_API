#include <iostream>
#include <Windows.h>
#include <tchar.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 800;

constexpr int DIVIDE_WIDTH = 15;
constexpr int DIVIDE_HEIGHT = 15;
constexpr int DIVIDE_NOW = 15;

constexpr short EMPTY = 0;
constexpr short BLOCK = 1;
constexpr short COLOR = 2;
constexpr short SIZECHANGE = 3;
constexpr short PLAYER1 = 4;
constexpr short PLAYER2 = 5;

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
	Window = CreateWindow(lpszClass, L"windows program 2-8", WS_OVERLAPPEDWINDOW,
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
	static short num_red, num_other, num_size, count_red, count_other, count_size;
	static short p1_x, p1_y, p2_x, p2_y;
	static short p1_r, p1_g, p1_b, p2_r, p2_g, p2_b;
	static short board[DIVIDE_WIDTH][DIVIDE_HEIGHT];
	static bool is_p1_turn, p1_shape, p2_shape;
	short temp_p1[1][1], temp_p2[1][1];
	switch (uMsg)
	{
	case WM_CREATE:
	{
		for (int i = 0; i < DIVIDE_HEIGHT; ++i)
		{
			for (int j = 0; j < DIVIDE_WIDTH; ++j)
			{
				board[i][j] = EMPTY;
			}
		}
		p1_x = 0;
		p1_y = 0;
		p2_x = DIVIDE_WIDTH - 1;
		p2_y = DIVIDE_HEIGHT - 1;
		p2_g = 150;
		p2_b = 150;
		is_p1_turn = true;
		p1_shape = false;
		p2_shape = false;
		board[p1_x][p1_y] = PLAYER1;
		board[p2_x][p2_y] = PLAYER2;
		count_red = 0;
		count_other = 0;
		count_size = 0;
		while (true)
		{
			num_red = rand() % 10 + 1;
			num_other = rand() % 10 + 1;
			num_size = rand() % 10 + 1;

			if (20 <= num_red + num_other + num_size)
			{
				while (true)
				{
					int board_x = rand() % DIVIDE_WIDTH;
					int board_y = rand() % DIVIDE_HEIGHT;

					if (EMPTY == board[board_x][board_y])
					{
						board[board_x][board_y] = rand() % 3 + 1;

						if (BLOCK == board[board_x][board_y])
						{
							if (num_red != count_red)
								count_red++;
							else
								board[board_x][board_y] = 0;
						}
						else if (COLOR == board[board_x][board_y])
						{
							if (num_other != count_other)
								count_other++;
							else
								board[board_x][board_y] = 0;
						}
						else if (SIZECHANGE == board[board_x][board_y])
						{
							if (num_size != count_size)
								count_size++;
							else
								board[board_x][board_y] = 0;
						}

						if (num_red == count_red && num_other == count_other && num_size == count_size)
							break;
					}
					else
						continue;
				}
			}
			else
				continue;
			break;
		}
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'W':
		case 'w':
			if (true == is_p1_turn)
			{
				is_p1_turn = false;
				if (0 == p1_y)
				{
					if (EMPTY == board[p1_x][DIVIDE_NOW - 1])
						p1_y = DIVIDE_NOW - 1;
					else if (COLOR == board[p1_x][DIVIDE_NOW - 1])
					{
						p1_r = rand() % 256;
						p1_g = rand() % 256;
						p1_b = rand() % 256;
						p1_y = DIVIDE_NOW - 1;
					}
					else if (SIZECHANGE == board[p1_x][DIVIDE_NOW - 1])
					{
						if (false == p1_shape)
							p1_shape = true;
						else
							p1_shape = false;
						p1_y = DIVIDE_NOW - 1;
					}
				}
				else
				{
					if (EMPTY == board[p1_x][p1_y - 1])
						--p1_y;
					else if (COLOR == board[p1_x][p1_y - 1])
					{
						p1_r = rand() % 256;
						p1_g = rand() % 256;
						p1_b = rand() % 256;
						--p1_y;
					}
					else if (SIZECHANGE == board[p1_x][p1_y - 1])
					{
						if (false == p1_shape)
							p1_shape = true;
						else
							p1_shape = false;
						--p1_y;
					}
				}
			}
			break;
		case 'S':
		case 's':
			if (true == is_p1_turn)
			{
				is_p1_turn = false;
				if (DIVIDE_NOW - 1 == p1_y)
				{
					if (EMPTY == board[p1_x][0])
						p1_y = 0;
					else if (COLOR == board[p1_x][0])
					{
						p1_r = rand() % 256;
						p1_g = rand() % 256;
						p1_b = rand() % 256;
						p1_y = 0;
					}
					else if (SIZECHANGE == board[p1_x][0])
					{
						if (false == p1_shape)
							p1_shape = true;
						else
							p1_shape = false;
						p1_y = 0;
					}
				}
				else
				{
					if (EMPTY == board[p1_x][p1_y + 1])
						++p1_y;
					else if (COLOR == board[p1_x][p1_y + 1])
					{
						p1_r = rand() % 256;
						p1_g = rand() % 256;
						p1_b = rand() % 256;
						++p1_y;
					}
					else if (SIZECHANGE == board[p1_x][p1_y + 1])
					{
						if (false == p1_shape)
							p1_shape = true;
						else
							p1_shape = false;
						++p1_y;
					}
				}
			}
			break;
		case 'A':
		case 'a':
			if (true == is_p1_turn)
			{
				is_p1_turn = false;
				if (0 == p1_x)
				{
					if (EMPTY == board[DIVIDE_NOW - 1][p1_y])
						p1_x = DIVIDE_NOW - 1;
					else if (COLOR == board[DIVIDE_NOW - 1][p1_y])
					{
						p1_r = rand() % 256;
						p1_g = rand() % 256;
						p1_b = rand() % 256;
						p1_x = DIVIDE_NOW - 1;
					}
					else if (SIZECHANGE == board[DIVIDE_NOW - 1][p1_y])
					{
						if (false == p1_shape)
							p1_shape = true;
						else
							p1_shape = false;
						p1_x = DIVIDE_NOW - 1;
					}
				}
				else
				{
					if (EMPTY == board[p1_x - 1][p1_y])
						--p1_x;
					else if (COLOR == board[p1_x - 1][p1_y])
					{
						p1_r = rand() % 256;
						p1_g = rand() % 256;
						p1_b = rand() % 256;
						--p1_x;
					}
					else if (SIZECHANGE == board[p1_x - 1][p1_y])
					{
						if (false == p1_shape)
							p1_shape = true;
						else
							p1_shape = false;
						--p1_x;
					}
				}
			}
			break;
		case 'D':
		case 'd':
			if (true == is_p1_turn)
			{
				is_p1_turn = false;
				if (DIVIDE_NOW - 1 == p1_x)
				{
					if (EMPTY == board[0][p1_y])
						p1_x = 0;
					else if (COLOR == board[0][p1_y])
					{
						p1_r = rand() % 256;
						p1_g = rand() % 256;
						p1_b = rand() % 256;
						p1_x = 0;
					}
					else if (SIZECHANGE == board[0][p1_y])
					{
						if (false == p1_shape)
							p1_shape = true;
						else
							p1_shape = false;
						p1_x = 0;
					}
				}
				else
				{
					if (EMPTY == board[p1_x + 1][p1_y])
						++p1_x;
					else if (COLOR == board[p1_x + 1][p1_y])
					{
						p1_r = rand() % 256;
						p1_g = rand() % 256;
						p1_b = rand() % 256;
						++p1_x;
					}
					else if (SIZECHANGE == board[p1_x + 1][p1_y])
					{
						if (false == p1_shape)
							p1_shape = true;
						else
							p1_shape = false;
						++p1_x;
					}
				}
			}
			break;
		case 'Q':
		case 'q':
			PostQuitMessage(0);
			break;
		case VK_UP:
			if (false == is_p1_turn)
			{
				is_p1_turn = true;
				if (0 == p2_y)
				{
					if (EMPTY == board[p2_x][DIVIDE_NOW - 1])
						p2_y = DIVIDE_NOW - 1;
					else if (COLOR == board[p2_x][DIVIDE_NOW - 1])
					{
						p2_r = rand() % 256;
						p2_g = rand() % 256;
						p2_b = rand() % 256;
						p2_y = DIVIDE_NOW - 1;
					}
					else if (SIZECHANGE == board[p2_x][DIVIDE_NOW - 1])
					{
						if (false == p1_shape)
							p2_shape = true;
						else
							p2_shape = false;
						p2_y = DIVIDE_NOW - 1;
					}
				}
				else
				{
					if (EMPTY == board[p2_x][p2_y - 1])
						--p2_y;
					else if (COLOR == board[p2_x][p2_y - 1])
					{
						p2_r = rand() % 256;
						p2_g = rand() % 256;
						p2_b = rand() % 256;
						--p2_y;
					}
					else if (SIZECHANGE == board[p2_x][p2_y - 1])
					{
						if (false == p2_shape)
							p2_shape = true;
						else
							p2_shape = false;
						--p2_y;
					}
				}
			}
			break;
		case VK_DOWN:
			if (false == is_p1_turn)
			{
				is_p1_turn = true;
				if (DIVIDE_NOW - 1 == p2_y)
				{
					if (EMPTY == board[p2_x][0])
						p2_y = 0;
					else if (COLOR == board[p2_x][0])
					{
						p2_r = rand() % 256;
						p2_g = rand() % 256;
						p2_b = rand() % 256;
						p2_y = 0;
					}
					else if (SIZECHANGE == board[p2_x][0])
					{
						if (false == p2_shape)
							p2_shape = true;
						else
							p2_shape = false;
						p2_y = 0;
					}
				}
				else
				{
					if (EMPTY == board[p2_x][p2_y + 1])
						++p2_y;
					else if (COLOR == board[p2_x][p2_y + 1])
					{
						p2_r = rand() % 256;
						p2_g = rand() % 256;
						p2_b = rand() % 256;
						++p2_y;
					}
					else if (SIZECHANGE == board[p2_x][p2_y + 1])
					{
						if (false == p2_shape)
							p2_shape = true;
						else
							p2_shape = false;
						++p2_y;
					}
				}
			}
			break;
		case VK_LEFT:
			if (false == is_p1_turn)
			{
				is_p1_turn = true;
				if (0 == p2_x)
				{
					if (EMPTY == board[DIVIDE_NOW - 1][p2_y])
						p2_x = DIVIDE_NOW - 1;
					else if (COLOR == board[DIVIDE_NOW - 1][p2_y])
					{
						p2_r = rand() % 256;
						p2_g = rand() % 256;
						p2_b = rand() % 256;
						p2_x = DIVIDE_NOW - 1;
					}
					else if (SIZECHANGE == board[DIVIDE_NOW - 1][p2_y])
					{
						if (false == p2_shape)
							p2_shape = true;
						else
							p2_shape = false;
						p2_x = DIVIDE_NOW - 1;
					}
				}
				else
				{
					if (EMPTY == board[p2_x - 1][p2_y])
						--p2_x;
					else if (COLOR == board[p2_x - 1][p2_y])
					{
						p2_r = rand() % 256;
						p2_g = rand() % 256;
						p2_b = rand() % 256;
						--p2_x;
					}
					else if (SIZECHANGE == board[p2_x - 1][p2_y])
					{
						if (false == p2_shape)
							p2_shape = true;
						else
							p2_shape = false;
						--p2_x;
					}
				}
			}
			break;
		case VK_RIGHT:
			if (false == is_p1_turn)
			{
				is_p1_turn = true;
				if (DIVIDE_NOW - 1 == p2_x)
				{
					if (EMPTY == board[0][p2_y])
						p2_x = 0;
					else if (COLOR == board[0][p2_y])
					{
						p2_r = rand() % 256;
						p2_g = rand() % 256;
						p2_b = rand() % 256;
						p2_x = 0;
					}
					else if (SIZECHANGE == board[0][p2_y])
					{
						if (false == p2_shape)
							p2_shape = true;
						else
							p2_shape = false;
						p2_x = 0;
					}
				}
				else
				{
					if (EMPTY == board[p2_x + 1][p2_y])
						++p2_x;
					else if (COLOR == board[p2_x + 1][p2_y])
					{
						p2_r = rand() % 256;
						p2_g = rand() % 256;
						p2_b = rand() % 256;
						++p2_x;
					}
					else if (SIZECHANGE == board[p2_x + 1][p2_y])
					{
						if (false == p2_shape)
							p2_shape = true;
						else
							p2_shape = false;
						++p2_x;
					}
				}
			}
			break;
		case 'R':
		case 'r':
			for (int i = 0; i < DIVIDE_HEIGHT; ++i)
			{
				for (int j = 0; j < DIVIDE_WIDTH; ++j)
				{
					board[i][j] = EMPTY;
				}
			}
			p1_x = 0;
			p1_y = 0;
			p2_x = DIVIDE_WIDTH - 1;
			p2_y = DIVIDE_HEIGHT - 1;
			p1_r = 0;
			p1_g = 0;
			p1_b = 0;
			p2_r = 0;
			p2_g = 150;
			p2_b = 150;
			is_p1_turn = true;
			p1_shape = false;
			p2_shape = false;
			board[p1_x][p1_y] = PLAYER1;
			board[p2_x][p2_y] = PLAYER2;
			count_red = 0;
			count_other = 0;
			count_size = 0;
			while (true)
			{
				num_red = rand() % 10 + 1;
				num_other = rand() % 10 + 1;
				num_size = rand() % 10 + 1;

				if (20 <= num_red + num_other + num_size)
				{
					while (true)
					{
						int board_x = rand() % DIVIDE_WIDTH;
						int board_y = rand() % DIVIDE_HEIGHT;

						if (EMPTY == board[board_x][board_y])
						{
							board[board_x][board_y] = rand() % 3 + 1;

							if (BLOCK == board[board_x][board_y])
							{
								if (num_red != count_red)
									count_red++;
								else
									board[board_x][board_y] = 0;
							}
							else if (COLOR == board[board_x][board_y])
							{
								if (num_other != count_other)
									count_other++;
								else
									board[board_x][board_y] = 0;
							}
							else if (SIZECHANGE == board[board_x][board_y])
							{
								if (num_size != count_size)
									count_size++;
								else
									board[board_x][board_y] = 0;
							}

							if (num_red == count_red && num_other == count_other && num_size == count_size)
								break;
						}
						else
							continue;
					}
				}
				else
					continue;
				break;
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
	//InvalidateRect(hWnd, NULL, TRUE);
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &C);

		for (int i = 0; i < DIVIDE_NOW; ++i)
		{
			MoveToEx(hdc, C.left + i * C.right / 15, C.top, NULL);
			LineTo(hdc, C.left + i * C.right / 15, C.top + C.bottom);
			MoveToEx(hdc, C.left, C.top + i * C.bottom / 15, NULL);
			LineTo(hdc, C.left + C.right, C.top + i * C.bottom / 15);
		}

		for (int i = 0; i < DIVIDE_WIDTH; ++i)
		{
			for (int j = 0; j < DIVIDE_HEIGHT; ++j)
			{
				if (BLOCK == board[i][j]) // 장애물일때
				{
					hBrush = CreateSolidBrush(RGB(255, 0, 0));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, C.left + i * C.right / 15, C.top + j * C.bottom / 15,
						C.left + (i + 1) * C.right / 15, C.top + (j + 1) * C.bottom / 15);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				else if (COLOR == board[i][j]) // 색상 변화
				{
					hBrush = CreateSolidBrush(RGB(0, 255, 0));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, C.left + i * C.right / 15, C.top + j * C.bottom / 15,
						C.left + (i + 1) * C.right / 15, C.top + (j + 1) * C.bottom / 15);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				else if (SIZECHANGE == board[i][j]) // 크기 변화
				{
					hBrush = CreateSolidBrush(RGB(0, 0, 255));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					RECT rect = { C.left + i * C.right / 15, C.top + j * C.bottom / 15,
						C.left + (i + 1) * C.right / 15, C.top + (j + 1) * C.bottom / 15 };
					InflateRect(&rect, -(C.right / 20), -(C.bottom / 20));
					FillRect(hdc, &rect, hBrush);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
			}
		}

		hBrush = CreateSolidBrush(RGB(p1_r, p1_g, p1_b));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		RECT rect_p1 = { C.left + p1_x * C.right / 15, C.top + p1_y * C.bottom / 15,
			C.left + (p1_x + 1) * C.right / 15, C.top + (p1_y + 1) * C.bottom / 15 };
		if (true == p1_shape)
			InflateRect(&rect_p1, -(C.right / 20), -(C.bottom / 20));
		FillRect(hdc, &rect_p1, hBrush);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(p2_r, p2_g, p2_b));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		RECT rect_p2 = { C.left + p2_x * C.right / 15, C.top + p2_y * C.bottom / 15,
			C.left + (p2_x + 1) * C.right / 15, C.top + (p2_y + 1) * C.bottom / 15 };
		if (true == p2_shape)
			InflateRect(&rect_p2, -(C.right / 20), -(C.bottom / 20));
		FillRect(hdc, &rect_p2, hBrush);
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