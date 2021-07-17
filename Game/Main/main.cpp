#include <Windows.h>

#include <Application/Application.h>
#include <fstream>
#include <iostream>

using namespace std;
using namespace ArtemisEngine;

ofstream coutStream;

void RedirectIO()
{
	coutStream = ofstream("C:\\Users\\Daniel\\Desktop\\output.txt");

	// optional performance optimizations    
	ios_base::sync_with_stdio(false);

	std::cout.rdbuf(coutStream.rdbuf());
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	RedirectIO();
	
	Application primaryApplication;
	primaryApplication.RunMainLoop();

	return 0;
}