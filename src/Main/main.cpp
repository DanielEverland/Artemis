

#include "..\Windows\GameWindow.h"

using namespace ArtemisWindow;

int WINAPI wWinMain(_In_ HINSTANCE handleInstance, _In_opt_ HINSTANCE, _In_ WCHAR* arguments, _In_ int windowState)
{
	GameWindow mainWindow(handleInstance, L"ArtemisWindow", windowState);
	mainWindow.Title = L"Artemis";
	mainWindow.Show();
}