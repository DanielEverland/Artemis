#include "main.h"

int WINAPI wWinMain(HandleInstance handleInstance, HandleInstance, UnicodeChar* arguments, int windowState)
{
	MainWindow mainWindow(handleInstance, windowState);

	return 0;
}