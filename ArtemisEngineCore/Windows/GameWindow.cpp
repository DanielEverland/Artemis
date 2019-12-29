#include <string>

#include "GameWindow.h"
#include "WindowProcedure.h"

#include "Exceptions/DirectXException.h"
#include "Time/Time.h"
#include "Debugging/Output.h"
#include "Input/Key.h"
#include "Input/Input.h"
#include "Exceptions/Exception.h"
#include "Engine/Application.h"

using ArtemisWindow::GameWindow;
using std::string;

GameWindow::GameWindow(HINSTANCE handleInstance, const LPCWSTR className, int windowState)
	: Window(handleInstance, className, windowState)
{
	// Initialize the global window rect variable.
	::GetWindowRect(windowHandle, &previousWindowRect);
}

void GameWindow::Show()
{
	CreateWindowClass();
	HWND windowHandle = CreateWindowHandle();

	InitializeDirectX();

	ShowWindow(windowHandle, SW_SHOW);
	RunMessageLoop();
}

void TickTime()
{
	static float lastTime = 0;

	float currentTime = Time::GetTimeSinceStart();
		
	Time::frameCount++;
	Time::deltaTime = currentTime - lastTime;

	lastTime = currentTime;
}

void GameWindow::Update()
{
	try
	{
		TickTime();

		OutputFramerate();
		HandleKeyBindings();

		Input::EndOfFrame();
	}
	catch (const Exception& e)
	{
		Output::LogException(e);
	}
	catch (const std::exception& e)
	{
		Output::LogError(string("Caught Base Exception: ") + e.what());
	}	
}

void GameWindow::Render()
{
	renderTargetView->Clear(rawBackBufferColor);
	depthBuffer->Clear();
	swapChain->Present();
}

void GameWindow::SetFullscreen(bool newFullscreenState)
{
	if (fullscreen != newFullscreenState)
	{
		fullscreen = newFullscreenState;

		if (fullscreen)
		{
			SwitchToFullscreen();
		}
		else
		{
			SwitchToWindowed();
		}
	}
}

void GameWindow::Resize(uint32_t newWidth, uint32_t newHeight)
{
	if (width != newWidth || height != newHeight)
	{
		width = std::max(1u, newWidth);
		height = std::max(1u, newHeight);
		
		renderTargetView->Reset();

		swapChain->Resize(width, height);
		renderTargetView->CreateBackBuffer();
		depthBuffer->Resize(width, height);
		
		CreateViewport();
	}
}

void GameWindow::ToggleFullscreen()
{
	SetFullscreen(!fullscreen);
}

void GameWindow::ToggleVSync()
{
	Application::SetVSync(!Application::GetVSync());
}

void GameWindow::SwitchToFullscreen()
{
	// Store the current window dimensions so they can be restored 
	// when switching out of fullscreen state.
	GetWindowRect(windowHandle, &previousWindowRect);

	UINT windowStyle = WS_OVERLAPPEDWINDOW & ~(WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	SetWindowLong(windowHandle, GWL_STYLE, windowStyle);

	HMONITOR monitor = MonitorFromWindow(windowHandle, MONITOR_DEFAULTTONEAREST);
	MONITORINFOEX monitorInfo = { };
	monitorInfo.cbSize = sizeof(MONITORINFOEX);
	GetMonitorInfo(monitor, &monitorInfo);

	SetWindowPos(windowHandle, HWND_TOP,
		monitorInfo.rcMonitor.left,
		monitorInfo.rcMonitor.top,
		monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
		monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
		SWP_FRAMECHANGED | SWP_NOACTIVATE);

	ShowWindow(windowHandle, SW_MAXIMIZE);
}

void GameWindow::SwitchToWindowed()
{
	SetWindowLong(windowHandle, GWL_STYLE, WS_OVERLAPPEDWINDOW);

	SetWindowPos(windowHandle, HWND_NOTOPMOST,
		previousWindowRect.left,
		previousWindowRect.top,
		previousWindowRect.right - previousWindowRect.left,
		previousWindowRect.bottom - previousWindowRect.top,
		SWP_FRAMECHANGED | SWP_NOACTIVATE);

	ShowWindow(windowHandle, SW_NORMAL);
}

void GameWindow::HandleKeyBindings()
{
	if (Input::IsDown(Key::V))
	{
		ToggleVSync();
	}
	if (Input::IsDown(Key::Esc))
	{
		PostQuitMessage(0);
	}
	if (Input::IsDown(Key::F11) || (Input::IsStay(Key::LeftAlt) && Input::IsDown(Key::Enter)))
	{
		ToggleFullscreen();
	}
}

void GameWindow::OutputFramerate() const
{
	static uint64_t frameCounter = 0;
	static double elapsedSeconds = 0.0;

	frameCounter++;

	elapsedSeconds += Time::GetDeltaTime();
	if (elapsedSeconds > 1.0)
	{
		auto fps = frameCounter / elapsedSeconds;
		Output::Log("FPS: " + std::to_string(fps));

		frameCounter = 0;
		elapsedSeconds = 0.0;
	}
}

//-------------------------------------------------------------------------------------------------------------
//---------------------------------------------MESSAGES--------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

void GameWindow::OnGainedFocus()
{
	Input::SanitizeDownKeys();
}

void GameWindow::InitializeDirectX()
{
	// Initialize the global window rect variable.
	GetWindowRect(windowHandle, &previousWindowRect);

	if (directXInitialized)
		throw DirectXException("DirectX has already been initialized!");
	
	CreateDirectXObjects();
	CreateViewport();
	CreateRawBackBufferColor();

	directXInitialized = true;
}

void GameWindow::CreateRawBackBufferColor()
{
	BackbufferColor.ToFloat(rawBackBufferColor);
}

void GameWindow::CreateDirectXObjects()
{
	graphicsDevice = shared_ptr<GraphicsDevice>(new GraphicsDevice());
	swapChain = shared_ptr<SwapChain>(new SwapChain(width, height, !fullscreen, windowHandle, graphicsDevice));
	renderTargetView = shared_ptr<RenderTargetView>(new RenderTargetView(swapChain, graphicsDevice));
	depthBuffer = shared_ptr<DepthBuffer>(new DepthBuffer(width, height, graphicsDevice));
}

void GameWindow::CreateViewport()
{
	ComPtr<ID3D11DeviceContext> rawContext = graphicsDevice->GetRawContext();
	ComPtr<ID3D11RenderTargetView> rawRenderTargetView = renderTargetView->GetRawRenderTargetView();
	ComPtr<ID3D11DepthStencilView> rawDepthStencilView = depthBuffer->GetRawStencilView();

	rawContext->OMSetRenderTargets(1, &rawRenderTargetView, rawDepthStencilView.Get());

	D3D11_VIEWPORT viewPortDescription
	{
		0, 0, // Top left (x, y)
		static_cast<float>(width),
		static_cast<float>(height),
		0, 1, // Min, Max depth
	};

	rawContext->RSSetViewports(1, &viewPortDescription);
}

LONG_PTR GameWindow::HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam)
{
	if (directXInitialized)
		return Window::HandleMessage(messageCode, wParam, lParam);

	return DefWindowProcW(windowHandle, messageCode, wParam, lParam);
}

void GameWindow::OnPaint()
{
	Update();
	Render();
}

void GameWindow::OnSystemKeyDown(UINT_PTR wParam)
{
	if (wParam != VK_F10)
	{
		if (wParam == VK_MENU)
			Input::OnKeyDown(Input::GetDownAltKey());

		Input::OnKeyDown(Key(wParam));
	}
	else
	{
		Input::OnKeyDown(Key::F10);
	}
}

void GameWindow::OnSystemKeyUp(UINT_PTR wParam)
{
	if (wParam != VK_F10)
	{
		Input::OnKeyUp(Key(wParam));

		if(wParam == VK_MENU)
			Input::OnKeyUp(Input::GetUpAltKey());
	}
	else
	{
		Input::OnKeyUp(Key::F10);
	}
}

void GameWindow::OnKeyDown(UINT_PTR wParam)
{
	Key keyCode = Input::DownWParamToKey(wParam);
	Input::OnKeyDown(keyCode);
}

void GameWindow::OnKeyUp(UINT_PTR wParam)
{
	Key keyCode = Input::UpWParamToKey(wParam);
	Input::OnKeyUp(keyCode);
}

void GameWindow::OnResize()
{
	RECT clientRect = { };
	GetClientRect(windowHandle, &clientRect);

	int width = clientRect.right - clientRect.left;
	int height = clientRect.bottom - clientRect.top;

	Resize(width, height);
}

void GameWindow::OnClose()
{
	Window::OnClose();

	// DX12 Snip
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
	windowClass.hIcon = ::LoadIcon(handleInstance, IDI_APPLICATION);
	windowClass.hIconSm = ::LoadIcon(handleInstance, IDI_APPLICATION);
	windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = Color(BackgroundColor);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = className;

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

void GameWindow::RunMessageLoop()
{
	MSG msg = { };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}