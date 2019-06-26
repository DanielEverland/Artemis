#include "GameWindow.h"

using ArtemisWindow::GameWindow;

GameWindow::GameWindow(HandleInstance handleInstance, const UnicodeChar* className, int windowState)
	: Window(handleInstance, className, windowState) { }

void GameWindow::RunMessageLoop()
{
	bool currentMessage;
	Message message;
	message.message = WM_NULL;

	PeekMessage(&message, NULL, 0U, 0U, PM_NOREMOVE);
	while (message.message != WM_QUIT)
	{
		// Process window events.
		// Use PeekMessage() so we can use idle time to render the scene.
		currentMessage = PeekMessage(&message, NULL, 0U, 0U, PM_REMOVE) != 0;

		if (currentMessage)
		{
			// Translate and dispatch the message
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			// Update the scene.
			//renderer->Update();

			// Render frames during idle time (when no messages are waiting).
			//renderer->Render();

			// Present the frame to the screen.
			//deviceResources->Present();
		}
	}
}