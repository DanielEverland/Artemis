#include "main.h"
#include "Window.h"

int WINAPI wWinMain(HandleInstance handleInstance, HandleInstance, UnicodeChar* arguments, int windowState)
{
	Window windowInstance(handleInstance, ClassName, windowState, WindowProcedure);
	windowInstance.Title = WindowTitle;

	windowInstance.Create();

	return 0;
}
LONG_PTR CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, UINT_PTR wParam, LONG_PTR lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}