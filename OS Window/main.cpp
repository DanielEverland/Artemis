#include "main.h"

int WINAPI wWinMain(HandleInstance handleInstance, HandleInstance, UnicodeChar* arguments, int windowState)
{
	const UnicodeChar* ClassName = L"ArtemisWindow";
	const UnicodeChar* WindowTitle = L"Artemis";

	Window mainWindow(handleInstance, ClassName, windowState);
	mainWindow.Create();

	return 0;
}