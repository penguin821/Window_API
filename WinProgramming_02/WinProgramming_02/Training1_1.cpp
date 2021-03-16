#include <Windows.h>
#include <tchar.h>

static int winCount = 0;

HINSTANCE g_hInst;
LPCTSTR lpszClass1 = L"Window1";
LPCTSTR lpszClass2 = L"Window2";
LRESULT CALLBACK WndProc1(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND Window1, Window2;
	MSG Message;
	WNDCLASSEX WndClass1, WndClass2;
	g_hInst = hInstance;
	WndClass1.cbSize = sizeof(WndClass1);
	WndClass1.style = CS_HREDRAW | CS_VREDRAW;
	WndClass1.lpfnWndProc = (WNDPROC)WndProc1;
	WndClass1.cbClsExtra = 0;
	WndClass1.cbWndExtra = 0;
	WndClass1.hInstance = hInstance;
	WndClass1.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass1.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass1.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass1.lpszMenuName = NULL;
	WndClass1.lpszClassName = lpszClass1;
	WndClass1.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass1);
	Window1 = CreateWindow(lpszClass1, L"windows program 1-2", WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, 
		100, 50, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);

	WndClass2.cbSize = sizeof(WndClass2);
	WndClass2.style = CS_HREDRAW | CS_VREDRAW;
	WndClass2.lpfnWndProc = (WNDPROC)WndProc2;
	WndClass2.cbClsExtra = 0;
	WndClass2.cbWndExtra = 0;
	WndClass2.hInstance = hInstance;
	WndClass2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass2.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass2.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass2.lpszMenuName = NULL;
	WndClass2.lpszClassName = lpszClass2;
	WndClass2.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass2);
	Window2 = CreateWindow(lpszClass2, L"windows program 1-1", WS_CAPTION | WS_BORDER | WS_SYSMENU,
		0, 0, 1280, 800, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(Window2, nCmdShow);
	UpdateWindow(Window2);// WM_PAINT
	ShowWindow(Window1, nCmdShow);
	UpdateWindow(Window1); 

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
	HDC hDC;
	switch (uMsg) {
	case WM_CREATE:
		winCount++;
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		winCount--;
		if (0 == winCount)
			PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK WndProc2(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	switch (uMsg) {
	case WM_CREATE:
		winCount++;
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		winCount--;
		if (0 == winCount)
			PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}