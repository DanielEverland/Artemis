#include <Windows.h>

#include <Application/Application.h>

using namespace ArtemisEngine;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Application primaryApplication;
	primaryApplication.RunMainLoop();

	return 0;
}