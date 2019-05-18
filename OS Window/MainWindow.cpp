#include "MainWindow.h"
#include "Window.h"

MainWindow::MainWindow(HandleInstance handleInstance, int windowState)
{
	Window windowInstance(handleInstance, ClassName, windowState, WindowProcedure);
	windowInstance.Title = WindowTitle;

	windowInstance.Create();
}
LONG_PTR CALLBACK WindowProcedure(WindowHandle handle, UINT messageCode, UINT_PTR wParam, LONG_PTR lParam)
{
	switch (messageCode)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(handle, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(handle, &ps);
	}
	return 0;

	}
	return DefWindowProc(handle, messageCode, wParam, lParam);
}