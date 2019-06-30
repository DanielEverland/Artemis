#include "ApplicationArguments.h"
#include "..\Windows\GameWindow.h"
#include <iostream>

using namespace ArtemisWindow;

void CreateMainWindow(HINSTANCE handleInstance, int windowState);
void ParseCommandLineArguments(GameWindow& window);

int WINAPI wWinMain(_In_ HINSTANCE handleInstance, _In_opt_ HINSTANCE, _In_ PWSTR arguments, _In_ int windowState)
{
	ApplicationArguments::Initialize();
	CreateMainWindow(handleInstance, windowState);
}

void CreateMainWindow(HINSTANCE handleInstance, int windowState)
{
	GameWindow mainWindow(handleInstance, L"ArtemisWindow", windowState);
	mainWindow.Title = L"Artemis";

	ParseCommandLineArguments(mainWindow);

	mainWindow.Show();
}

void ParseCommandLineArguments(GameWindow& window)
{
	if (ApplicationArguments::HasHeight())
		window.SetHeight(ApplicationArguments::GetHeight());

	if (ApplicationArguments::HasWidth())
		window.SetWidth(ApplicationArguments::GetWidth());

	if (ApplicationArguments::HasUseWARP())
		window.SetUseWARPAdapter(true);
}