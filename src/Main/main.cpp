#include <iostream>
#include "ApplicationArguments.h"

#include "Source\Windows\GameWindow.h"
#include "Include/Game/Output.h"
#include "Include/Game/Time.h"
#include "Include/Exceptions/Exception.h"

using namespace ArtemisWindow;

void CreateMainWindow(HINSTANCE handleInstance, int windowState);
void ParseCommandLineArguments(GameWindow& window);
void InitializeTime();

int WINAPI wWinMain(_In_ HINSTANCE handleInstance, _In_opt_ HINSTANCE, _In_ PWSTR arguments, _In_ int windowState)
{
	if (!Exception::InitializeSymbols())
		Output::LogError("Couldn't initialize exception symbols!\nExceptions won't output stacktraces!");
	try
	{
		ApplicationArguments::Initialize();
		InitializeTime();

		CreateMainWindow(handleInstance, windowState);
	}
	catch (const Exception& e)
	{
		Output::LogException(e);
	}
	catch (const std::exception& e)
	{
		Output::Log("Base Exception Caught: " + string(e.what()));
	}
}

void CreateMainWindow(HINSTANCE handleInstance, int windowState)
{
	// Windows 10 Creators update adds Per Monitor V2 DPI awareness context.
	// Using this awareness context allows the client area of the window 
	// to achieve 100% scaling while still allowing non-client window content to 
	// be rendered in a DPI sensitive fashion.
	SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	GameWindow mainWindow(handleInstance, L"ArtemisWindow", windowState);
	mainWindow.Title = L"Artemis";

	ParseCommandLineArguments(mainWindow);

	mainWindow.Show();
}

void InitializeTime()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&Time::startTime);

	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)& countsPerSec);
	
	Time::secondsPerCount = float(1.0 / double(countsPerSec));
}

void ParseCommandLineArguments(GameWindow& window)
{
	if (ApplicationArguments::HasHeight())
		window.SetHeight(ApplicationArguments::GetHeight());

	if (ApplicationArguments::HasWidth())
		window.SetWidth(ApplicationArguments::GetWidth());

	if (ApplicationArguments::HasUseWARP())
		window.GetRenderer()->SetUseWARPAdapter(true);
}