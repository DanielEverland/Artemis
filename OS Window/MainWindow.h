#pragma once

#include "PrettyWin32.h"

LONG_PTR CALLBACK WindowProcedure(WindowHandle handle, UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);
void Close();
void Paint(WindowHandle handle);

class MainWindow
{
public:
	MainWindow(HandleInstance handleInstance, int windowState);

private:
	const UnicodeChar* ClassName = L"ArtemisWindow";
	const UnicodeChar* WindowTitle = L"Artemis";
};

