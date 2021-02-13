#include <Core/Core/Core.h>
#include <Framework/Application.h>

string LogCategoryMain = "Main";

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args)
{
	TRY_START
	
	Application application = { };
	if (!application.Initialize())
		return -1;

	application.Start();
	return 0;

	TRY_END(LogCategoryMain, Verbosity::Fatal);
}