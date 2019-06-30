#include <d3d12.h>

#include "..\Direct X\DXHelper.h"

#include "GameWindow.h"
#include "WindowProcedure.h"

using ArtemisWindow::GameWindow;

GameWindow::GameWindow(HINSTANCE handleInstance, const LPCWSTR className, int windowState)
	: Window(handleInstance, className, windowState)
{
#if defined(_DEBUG)
	EnableDebugLayer();
#endif


}

ComPtr<IDXGIAdapter4> GameWindow::GetAdapter()
{
	ComPtr<IDXGIFactory4> dxgiFactory;
	UINT createFactoryFlags = 0;

#if defined(_DEBUG)
	createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

	ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory)));

	ComPtr<IDXGIAdapter1> dxgiAdapter1;
	ComPtr<IDXGIAdapter4> dxgiAdapter4;

	if (useWARPAdapter)
	{
		ThrowIfFailed(dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&dxgiAdapter1)));
		ThrowIfFailed(dxgiAdapter1.As(&dxgiAdapter4));
	}
	else
	{
		GetBestGraphicsAdapater(dxgiFactory, dxgiAdapter1, dxgiAdapter4);
	}

	return dxgiAdapter4;
}

void GameWindow::GetBestGraphicsAdapater(const ComPtr<IDXGIFactory4> dxgiFactory, ComPtr<IDXGIAdapter1> dxgiAdapter1, ComPtr<IDXGIAdapter4> dxgiAdapter4) const
{
	SIZE_T maxDedicatedVideoMemory = 0;
	for (UINT i = 0; dxgiFactory->EnumAdapters1(i, &dxgiAdapter1) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		DXGI_ADAPTER_DESC1 dxgiAdapterDesc1;
		dxgiAdapter1->GetDesc1(&dxgiAdapterDesc1);

		if (!IsWARPAdapater(dxgiAdapterDesc1) && IsAdapterDirectX12Compatible(dxgiAdapter1)
			&& dxgiAdapterDesc1.DedicatedVideoMemory > maxDedicatedVideoMemory)
		{
			maxDedicatedVideoMemory = dxgiAdapterDesc1.DedicatedVideoMemory;
			ThrowIfFailed(dxgiAdapter1.As(&dxgiAdapter4));
		}
	}
}

bool GameWindow::IsWARPAdapater(const DXGI_ADAPTER_DESC1& adapter) const
{
	return (adapter.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) != 0;
}

bool GameWindow::IsAdapterDirectX12Compatible(const ComPtr<IDXGIAdapter1> adapter) const
{
	return SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr));
}

void GameWindow::CreateWindowClass() const
{
	WNDCLASSEXW windowClass{ };

	windowClass.cbSize = sizeof(WNDCLASSEXW);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProcedure;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = handleInstance;
	windowClass.hIcon = ::LoadIcon(handleInstance, NULL);
	windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = Color(BackgroundColor);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = className;
	windowClass.hIconSm = ::LoadIcon(handleInstance, nullptr);

	static ATOM atom = ::RegisterClassExW(&windowClass);
	assert(atom > 0);
}

HWND ArtemisWindow::GameWindow::CreateWindowHandle()
{
	int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

	RECT windowRect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
	::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;

	// Center the window within the screen. Clamp to 0, 0 for the top-left corner.
	int windowX = std::max<int>(0, (screenWidth - windowWidth) / 2);
	int windowY = std::max<int>(0, (screenHeight - windowHeight) / 2);

	HWND handle = ::CreateWindowExW(
		NULL,							// Extended Window Style
		className,
		Title,
		WS_OVERLAPPEDWINDOW,
		
		windowX, windowY, windowWidth, windowHeight,

		NULL,							// Parent window
		NULL,							// Menu
		handleInstance,
		this
	);

	assert(handle && "Failed to create window");

	return handle;
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