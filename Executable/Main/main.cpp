#include <Application/Application.h>

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args)
{
	Application application = { };
	if(!application.Initialize())
		return -1;

	application.Start();
	return 0;
}