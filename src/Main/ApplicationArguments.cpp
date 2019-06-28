#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>
#include "ApplicationArguments.h"

unique_ptr<long> ApplicationArguments::width = nullptr;
unique_ptr<long> ApplicationArguments::height = nullptr;
bool ApplicationArguments::useWARPDefined = false;

void ApplicationArguments::Initialize()
{
	int argc;
	wchar_t** argv = ::CommandLineToArgvW(::GetCommandLineW(), &argc);

	for (size_t i = 0; i < argc; ++i)
	{
		if (::wcscmp(argv[i], L"-w") == 0 || ::wcscmp(argv[i], L"--width") == 0)
		{
			ApplicationArguments::width = unique_ptr<long>(new long);
			*ApplicationArguments::width = ::wcstol(argv[++i], nullptr, 10);
		}
		if (::wcscmp(argv[i], L"-h") == 0 || ::wcscmp(argv[i], L"--height") == 0)
		{
			ApplicationArguments::height = unique_ptr<long>(new long);
			*ApplicationArguments::height = ::wcstol(argv[++i], nullptr, 10);
		}
		if (::wcscmp(argv[i], L"-warp") == 0 || ::wcscmp(argv[i], L"--warp") == 0)
		{
			ApplicationArguments::useWARPDefined = true;
		}
	}

	// Free memory allocated by CommandLineToArgvW
	::LocalFree(argv);
}