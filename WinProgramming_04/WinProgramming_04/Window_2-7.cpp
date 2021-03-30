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
	Window = CreateWindow(lpszClass, L"windows program 2-7", WS_OVERLAPPEDWINDOW,
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
	HBRUSH hTriBrush, hSandBrush, hPentaBrush, hPieBrush, oldBrush;
	static int t_r, t_g, t_b, s_r, s_g, s_b, pe_r, pe_g, pe_b, pi_r, pi_g, pi_b,
		t_tr, t_tg, t_tb, t_sr, t_sg, t_sb, t_per, t_peg, t_peb, t_pir, t_pig, t_pib;
	static bool select_t = false, select_s = false, select_pe = false, select_pi = false;
	switch (uMsg)
	{
	case WM_CREATE:
	{
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'T':
		case 't':
			t_r = rand() % 256;
			t_g = rand() % 256;
			t_b = rand() % 256;
			t_tr = t_r;
			t_tg = t_g;
			t_tb = t_b;
			break;
		case 'S':
		case 's':
			s_r = rand() % 256;
			s_g = rand() % 256;
			s_b = rand() % 256;
			t_sr = s_r;
			t_sg = s_g;
			t_sb = s_b;
			break;
		case 'P':
		case 'p':
			pe_r = rand() % 256;
			pe_g = rand() % 256;
			pe_b = rand() % 256;
			t_per = pe_r;
			t_peg = pe_g;
			t_peb = pe_b;
			break;
		case 'E':
		case 'e':
			pi_r = rand() % 256;
			pi_g = rand() % 256;
			pi_b = rand() % 256;
			t_pir = pi_r;
			t_pig = pi_g;
			t_pib = pi_b;
			break;
		case 'Q':
		case 'q':
			PostQuitMessage(0);
			break;
		case VK_UP:
			if (t_sr == s_r && t_sg == s_g && t_sb == s_b)
			{
				s_r = rand() % 256;
				s_g = rand() % 256;
				s_b = rand() % 256;
			}
			select_s = true;
			break;
		case VK_LEFT:
			if (t_tr == t_r && t_tg == t_g && t_tb == t_b)
			{
				t_r = rand() % 256;
				t_g = rand() % 256;
				t_b = rand() % 256;
			}
			select_t = true;
			break;
		case VK_RIGHT:
			if (t_per == pe_r && t_peg == pe_g && t_peb == pe_b)
			{
				pe_r = rand() % 256;
				pe_g = rand() % 256;
				pe_b = rand() % 256;
			}
			select_pe = true;
			break;
		case VK_DOWN:
			if (t_pir == pi_r && t_pig == pi_g && t_pib == pi_b)
			{
				pi_r = rand() % 256;
				pi_g = rand() % 256;
				pi_b = rand() % 256;
			}
			select_pi = true;
			break;
		}
	}
	InvalidateRect(hWnd, NULL, TRUE);
	break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case VK_UP:
			s_r = t_sr;
			s_g = t_sg;
			s_b = t_sb;
			select_s = false;
			break;
		case VK_LEFT:
			t_r = t_tr;
			t_g = t_tg;
			t_b = t_tb;
			select_t = false;
			break;
		case VK_RIGHT:
			pe_r = t_per;
			pe_g = t_peg;
			pe_b = t_peb;
			select_pe = false;
			break;
		case VK_DOWN:
			pi_r = t_pir;
			pi_g = t_pig;
			pi_b = t_pib;
			select_pi = false;
			break;
		}
	}
	InvalidateRect(hWnd, NULL, TRUE);
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &C);
		Rectangle(hdc, C.left + C.right / 3, C.top + C.bottom / 3, 2 * C.right / 3, 2 * C.bottom / 3);

		hTriBrush = CreateSolidBrush(RGB(t_r, t_g, t_b));
		oldBrush = (HBRUSH)SelectObject(hdc, hTriBrush);

		POINT Tri[6] = { {C.left + C.right / 6,C.top + C.bottom / 3},
		{C.left,C.top + 2 * C.bottom / 3},{C.left + C.right / 3,C.top + 2 * C.bottom / 3} };
		Polygon(hdc, Tri, 3); // 삼각형

		if (true == select_t)
		{
			POINT Tri[6] = { {C.left + C.right / 2,C.top + C.bottom / 3},
			{C.left + C.right / 3,C.top + 2 * C.bottom / 3},{C.left + 2 * C.right / 3,C.top + 2 * C.bottom / 3} };
			Polygon(hdc, Tri, 3); // 삼각형
		}

		hSandBrush = CreateSolidBrush(RGB(s_r, s_g, s_b));
		oldBrush = (HBRUSH)SelectObject(hdc, hSandBrush);

		POINT Sand1[6] = { {C.left + C.right / 2,C.top + C.bottom / 6},
		{C.left + C.right / 3,C.top},{C.left + 2 * C.right / 3,C.top} };
		Polygon(hdc, Sand1, 3); 
		POINT Sand2[6] = { {C.left + C.right / 2,C.top + C.bottom / 6},
		{C.left + C.right / 3,C.top + C.bottom / 3},{C.left + 2 * C.right / 3,C.top + C.bottom / 3} };
		Polygon(hdc, Sand2, 3); // 모래시계

		if (true == select_s)
		{
			POINT Sand1[6] = { {C.left + C.right / 2,C.top + C.bottom / 2},
			{C.left + C.right / 3,C.top + C.bottom / 3},{C.left + 2 * C.right / 3,C.top + C.bottom / 3} };
			Polygon(hdc, Sand1, 3);
			POINT Sand2[6] = { {C.left + C.right / 2,C.top + C.bottom / 2},
			{C.left + C.right / 3,C.top + 2 * C.bottom / 3},{C.left + 2 * C.right / 3,C.top + 2 * C.bottom / 3} };
			Polygon(hdc, Sand2, 3); // 모래시계
		}

		hPentaBrush = CreateSolidBrush(RGB(pe_r, pe_g, pe_b));
		oldBrush = (HBRUSH)SelectObject(hdc, hPentaBrush);

		POINT Penta[10] = { {C.left + 5 * C.right / 6,C.top + C.bottom / 3},
		{C.left + 2 * C.right / 3,C.top + C.bottom / 2},{C.left + 3 * C.right / 4,C.top + 2 * C.bottom / 3},
		{C.left + 11 * C.right / 12 ,C.top + 2 * C.bottom / 3},{C.left + C.right ,C.top + C.bottom / 2} };
		Polygon(hdc, Penta, 5); // 모래시계

		if (true == select_pe)
		{
			POINT Penta[10] = { {C.left + C.right / 2,C.top + C.bottom / 3},
			{C.left + C.right / 3,C.top + C.bottom / 2},{C.left + 5 * C.right / 12,C.top + 2 * C.bottom / 3},
			{C.left + 7 * C.right / 12 ,C.top + 2 * C.bottom / 3},{C.left + 2 * C.right / 3 ,C.top + C.bottom / 2} };
			Polygon(hdc, Penta, 5); // 모래시계
		}

		hPieBrush = CreateSolidBrush(RGB(pi_r, pi_g, pi_b));
		oldBrush = (HBRUSH)SelectObject(hdc, hPieBrush);

		Pie(hdc, C.left + C.right / 3, C.top + 2 * C.bottom / 3, C.left + 2 * C.right / 3, C.top + C.bottom // 파이
			, C.left + C.right / 2, C.top + 2 * C.bottom / 3, C.left + 2 * C.right / 3, C.top + 5 * C.bottom / 6);

		if (true == select_pi)
		{
			Pie(hdc, C.left + C.right / 3, C.top + C.bottom / 3, C.left + 2 * C.right / 3, C.top + 2 * C.bottom / 3 // 파이
				, C.left + C.right / 2, C.top + C.bottom / 3, C.left + 2 * C.right / 3, C.top + C.bottom / 2);
		}

		SelectObject(hdc, oldBrush);
		DeleteObject(hTriBrush);
		DeleteObject(hSandBrush);
		DeleteObject(hPentaBrush);
		DeleteObject(hPieBrush);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}