#include "main.h"

int WINAPI wWinMain(HandleInstance handleInstance, HandleInstance, UnicodeChar* arguments, int windowState)
{
	Window mainWindow(handleInstance, L"ArtemisWindow", windowState);
	mainWindow.Title = L"Artemis";
	mainWindow.Show();

	return 0;
}