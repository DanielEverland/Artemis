#include <Core/Core/Core.h>
#include <Framework/Application.h>

string LogCategoryMain = "Main";

#pragma warning(disable:4100)
// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args)
{
#pragma warning(default:4100)
	TRY_START
	
	Application application = { };
	if (!application.Initialize())
		return -1;

	application.Start();
	
	TRY_END(LogCategoryMain, Verbosity::Fatal);	
	return 0;
}