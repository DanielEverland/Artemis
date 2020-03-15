#include <string>

#include "GameWindow.h"
#include "WindowProcedure.h"

#include "Include/Game/Output.h"
#include "Include/Game/Time.h"
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

	renderer = shared_ptr<Renderer>(new Renderer(this));
}

void GameWindow::Show()
{
	CreateWindowClass();
	HWND windowHandle = CreateWindowHandle();

	InitializeRenderer();

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
	renderer->Render();
}

void GameWindow::ToggleVSync()
{
	Application::SetVSync(!Application::GetVSync());
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

void GameWindow::HasResized()
{
	renderer->Resize();
}

//-------------------------------------------------------------------------------------------------------------
//---------------------------------------------MESSAGES--------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

void GameWindow::OnGainedFocus()
{
	Input::SanitizeDownKeys();
}

void GameWindow::InitializeRenderer()
{
	// Initialize the global window rect variable.
	GetWindowRect(windowHandle, &previousWindowRect);

	renderer->Initialize();
}

LONG_PTR GameWindow::HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam)
{
	if (renderer->IsInitialized())
		return Window::HandleMessage(messageCode, wParam, lParam);
	
	Output::LogWarning("Game Window cannot handle messages because renderer isn't initialized");

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