#include "..\Windows\GameWindow.h"

using namespace ArtemisWindow;

int WINAPI wWinMain(_In_ HandleInstance handleInstance, _In_opt_ HandleInstance, _In_ UnicodeChar* arguments, _In_ int windowState)
{
	GameWindow mainWindow(handleInstance, L"ArtemisWindow", windowState);
	mainWindow.Title = L"Artemis";
	mainWindow.Show();
}