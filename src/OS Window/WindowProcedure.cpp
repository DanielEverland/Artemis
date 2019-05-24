#include "WindowProcedure.h"

LONG_PTR CALLBACK WindowProcedure(WindowHandle handle, UINT messageCode, UINT_PTR wParam, LONG_PTR lParam)
{
	Window* instancePointer = GetInstancePointer(handle, messageCode, lParam);

	if (instancePointer != NULL)
	{
		return instancePointer->HandleMessage(messageCode, wParam, lParam);
	}
	else // This will only happen for messages invoked prior to WM_NCCREATE
	{
		return DefWindowProc(handle, messageCode, wParam, lParam);
	}
}
Window* GetInstancePointer(WindowHandle handle, UINT messageCode, LONG_PTR lParam)
{
	if (messageCode == WM_NCCREATE)
	{
		return CreateStateInformation(handle, lParam);
	}
	else
	{
		return (Window*)GetStateInformation(handle);
	}
}
Window* CreateStateInformation(WindowHandle handle, LONG_PTR lParam)
{
	Window* instancePointer = NULL;

	CREATESTRUCT* createStruct = (CREATESTRUCT*)lParam;
	instancePointer = (Window*)createStruct->lpCreateParams;
	instancePointer->windowHandle = handle;

	SetStateInformation(instancePointer, handle);

	return instancePointer;
}
void SetStateInformation(Window* instancePointer, WindowHandle handle)
{
	SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)instancePointer);
}
LONG_PTR GetStateInformation(WindowHandle handle)
{
	return GetWindowLongPtr(handle, GWLP_USERDATA);
}