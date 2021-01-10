#include <Application/Framework/Application.h>

using namespace ArtemisApplication;

int WINAPI wWinMain(_In_ HINSTANCE handleInstance, _In_opt_ HINSTANCE, _In_ PWSTR arguments, _In_ int windowState)
{
    // Use HeapSetInformation to specify that the process should
    // terminate if the heap manager detects an error in any heap used
    // by the process.
    // The return value is ignored, because we want to continue running in the
    // unlikely event that HeapSetInformation fails.
    HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);

    if (SUCCEEDED(CoInitialize(nullptr)))
    {
        Application app;

        if (SUCCEEDED(app.Initialize()))
        {
            app.RunMessageLoop();
        }
        CoUninitialize();
    }

    return 0;
}