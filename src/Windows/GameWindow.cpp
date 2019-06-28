#include "GameWindow.h"
#include <d3d12.h>
#include "..\Direct X\DXHelper.h"

using ArtemisWindow::GameWindow;

GameWindow::GameWindow(HINSTANCE handleInstance, const LPCWSTR className, int windowState)
	: Window(handleInstance, className, windowState)
{
#if defined(_DEBUG)
	EnableDebugLayer();
#endif


}

void GameWindow::EnableDebugLayer() const
{
	ComPtr<ID3D12Debug> debugInterface;
	ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface)));
	debugInterface->EnableDebugLayer();
}

void GameWindow::RunMessageLoop()
{
	bool currentMessage;
	MSG message;
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