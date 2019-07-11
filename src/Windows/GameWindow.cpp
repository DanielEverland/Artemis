#include <d3d12.h>

#include "..\Direct X\DXHelper.h"

#include "GameWindow.h"
#include "WindowProcedure.h"

using ArtemisWindow::GameWindow;

const D3D12_MESSAGE_SEVERITY GameWindow::BreakOnSeverity[]
{
	D3D12_MESSAGE_SEVERITY_CORRUPTION,
	D3D12_MESSAGE_SEVERITY_ERROR,
	D3D12_MESSAGE_SEVERITY_WARNING,
};

D3D12_MESSAGE_SEVERITY GameWindow::IgnoreSeverity[]
{
	D3D12_MESSAGE_SEVERITY_INFO,
};

D3D12_MESSAGE_ID GameWindow::IgnoreMessages[]
{
	D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,
	D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,
	D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,
};

D3D12_MESSAGE_CATEGORY GameWindow::IgnoreCategories[1]
{
};

GameWindow::GameWindow(HINSTANCE handleInstance, const LPCWSTR className, int windowState)
	: Window(handleInstance, className, windowState)
{
#if defined(_DEBUG)
	EnableDebugLayer();
#endif


}


void GameWindow::Update()
{
	static uint64_t frameCounter = 0;
	static double elapsedSeconds = 0.0;
	static std::chrono::high_resolution_clock clock;
	static auto t0 = clock.now();

	frameCounter++;
	auto t1 = clock.now();
	auto deltaTime = t1 - t0;
	t0 = t1;

	elapsedSeconds += deltaTime.count() * 1e-9;
	if (elapsedSeconds > 1.0)
	{
		char buffer[500];
		auto fps = frameCounter / elapsedSeconds;
		sprintf_s(buffer, 500, "FPS: %f\n", fps);
		OutputDebugString(buffer);

		frameCounter = 0;
		elapsedSeconds = 0.0;
	}
}

void GameWindow::Render()
{
	auto commandAllocator = commandAllocators[currentBackBufferIndex];
	auto backBuffer = backBuffers[currentBackBufferIndex];

	commandAllocator->Reset();
	commandList->Reset(commandAllocator.Get(), nullptr);

	// Clear the render target
	{
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
			backBuffer.Get(),
			D3D12_RESOURCE_STATE_PRESENT,
			D3D12_RESOURCE_STATE_RENDER_TARGET);

		commandList->ResourceBarrier(1, &barrier);

		float clearColor[] = { 0.4f, 0.6f, 0.9f, 1.0f };
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtv(RTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), currentBackBufferIndex, RTVDescriptorSize);

		commandList->ClearRenderTargetView(rtv, clearColor, 0, nullptr);
	}

	// Present
	{
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
			backBuffer.Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			D3D12_RESOURCE_STATE_PRESENT);

		commandList->ResourceBarrier(1, &barrier);

		ThrowIfFailed(commandList->Close());

		ID3D12CommandList* const commandLists[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

		UINT syncInterval = vSync ? 1 : 0;
		UINT presentFlags = (tearingSupported && !vSync) ? DXGI_PRESENT_ALLOW_TEARING : 0;

		ThrowIfFailed(swapChain->Present(syncInterval, presentFlags));

		frameFenceValues[currentBackBufferIndex] = Signal(commandQueue, fence, fenceValue);

		currentBackBufferIndex = swapChain->GetCurrentBackBufferIndex();
		WaitForFenceValue(fence, frameFenceValues[currentBackBufferIndex], fenceEvent);
	}
}

void GameWindow::SetFullscreen(bool newFullscreenState)
{
	if (fullscreen != newFullscreenState)
	{
		fullscreen = newFullscreenState;

		if (fullscreen) // Switching to fullscreen
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
		else
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
	}
}

void GameWindow::Resize(uint32_t newWidth, uint32_t newHeight)
{
	if (width != newWidth || height != newHeight)
	{
		width = std::max(1u, newWidth);
		height = std::max(1u, newHeight);

		// Flush the GPU queue to make sure the swap chain's back buffers
		// are not being referenced by an in-flight command list.
		Flush(commandQueue, fence, fenceValue, fenceEvent);

		for (int i = 0; i < swapChainBufferSize; i++)
		{
			// Any references to the back buffers must be released
			// before the swap chain can be resized.
			backBuffers[i].Reset();
			frameFenceValues[i] = frameFenceValues[currentBackBufferIndex];

			DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
			ThrowIfFailed(swapChain->GetDesc(&swapChainDesc));
			ThrowIfFailed(swapChain->ResizeBuffers(swapChainBufferSize, width, height, swapChainDesc.BufferDesc.Format, swapChainDesc.Flags));
			
			currentBackBufferIndex = swapChain->GetCurrentBackBufferIndex();
			UpdateRenderTargetViews(device, swapChain, RTVDescriptorHeap);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
//---------------------------------------------MESSAGES-------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

LONG_PTR GameWindow::HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam)
{
	if (directXInitialized)
		return Window::HandleMessage(messageCode, wParam, lParam);

	return DefWindowProc(windowHandle, messageCode, wParam, lParam);
}

void GameWindow::OnPaint()
{
	Update();
	Render();
}

void GameWindow::OnSystemKeyDown(UINT_PTR wParam)
{
	HandleKeyDown(wParam);
}

void GameWindow::OnKeyDown(UINT_PTR wParam)
{
	HandleKeyDown(wParam);
}

void GameWindow::HandleKeyDown(UINT_PTR wParam)
{
	bool alt = (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;
	
	switch (wParam)
	{
	case 'V':
		vSync = !vSync;
		break;
	case VK_ESCAPE:
		::PostQuitMessage(0);
		break;
	case VK_RETURN:
		if (alt)
		{
	case VK_F11:
		SetFullscreen(!fullscreen);
		}
		break;
	}
}

void GameWindow::OnResize()
{
	RECT clientRect = { };
	GetClientRect(windowHandle, &clientRect);

	int width = clientRect.right - clientRect.left;
	int height = clientRect.bottom - clientRect.top;

	Resize(width, height);
}

//-------------------------------------------------------------------------------------------------------------
//----------------------------------------LOW LEVEL FUNCTIONS--------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

void GameWindow::Flush(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue, HANDLE fenceEvent) const
{
	uint64_t fenceValueSignal = Signal(commandQueue, fence, fenceValue);
	WaitForFenceValue(fence, fenceValueSignal, fenceEvent);
}

void GameWindow::WaitForFenceValue(ComPtr<ID3D12Fence> fence, uint64_t fenceValue, HANDLE fenceEvent, std::chrono::milliseconds duration) const
{
	if (fence->GetCompletedValue() < fenceValue)
	{
		ThrowIfFailed(fence->SetEventOnCompletion(fenceValue, fenceEvent));
		WaitForSingleObject(fenceEvent, static_cast<DWORD>(duration.count()));
	}
}

uint64_t GameWindow::Signal(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue) const
{
	uint64_t fenceValueForSignal = ++fenceValue;
	ThrowIfFailed(commandQueue->Signal(fence.Get(), fenceValueForSignal));

	return fenceValueForSignal;
}

HANDLE GameWindow::CreateEventHandle() const
{
	HANDLE fenceEvent;

	fenceEvent = CreateEvent(nullptr, false, false, nullptr);
	assert(fenceEvent && "Failed to create fence event.");

	return fenceEvent;
}

ComPtr<ID3D12Fence> GameWindow::CreateFence(ComPtr<ID3D12Device2> device) const
{
	ComPtr<ID3D12Fence> fence;

	ThrowIfFailed(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)));

	return fence;
}

ComPtr<ID3D12GraphicsCommandList> GameWindow::CreateCommandList(ComPtr<ID3D12Device2> device, ComPtr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type) const
{
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ThrowIfFailed(device->CreateCommandList(0, type, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)));

	ThrowIfFailed(commandList->Close());

	return commandList;
}

ComPtr<ID3D12CommandAllocator> GameWindow::CreateCommandAllocator(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type) const
{
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ThrowIfFailed(device->CreateCommandAllocator(type, IID_PPV_ARGS(&commandAllocator)));

	return commandAllocator;
}

void GameWindow::UpdateRenderTargetViews(ComPtr<ID3D12Device2> device, ComPtr<IDXGISwapChain4> swapChain, ComPtr<ID3D12DescriptorHeap> descriptorHeap)
{
	UINT rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(descriptorHeap->GetCPUDescriptorHandleForHeapStart());

	for (int i = 0; i < swapChainBufferSize; i++)
	{
		ComPtr<ID3D12Resource> backBuffer;
		ThrowIfFailed(swapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffer)));

		device->CreateRenderTargetView(backBuffer.Get(), nullptr, rtvHandle);

		backBuffers[i] = backBuffer;

		rtvHandle.Offset(rtvDescriptorSize);
	}
}

ComPtr<ID3D12DescriptorHeap> GameWindow::CreateDescriptorHeap(ComPtr<ID3D12Device2> device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors) const
{
	ComPtr<ID3D12DescriptorHeap> descriptorHeap;

	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = numDescriptors;
	desc.Type = type;

	ThrowIfFailed(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&descriptorHeap)));

	return descriptorHeap;
}

ComPtr<IDXGISwapChain4> GameWindow::CreateSwapChain(HWND handle, ComPtr<ID3D12CommandQueue> commandQueue, uint32_t width, uint32_t height, uint32_t bufferCount) const
{
	ComPtr<IDXGISwapChain4> swapChain4;
	ComPtr<IDXGIFactory4> factory;

	UINT createFactoryFlags = 0;

#if defined(_DEBUG)
	createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

	ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&factory)));

	DXGI_SWAP_CHAIN_DESC1 swapChainDescription = GetSwapChainDescription(width, height, bufferCount);

	ComPtr<IDXGISwapChain1> swapChain1;
	ThrowIfFailed(factory->CreateSwapChainForHwnd(
		commandQueue.Get(),
		handle,
		&swapChainDescription,
		nullptr,
		nullptr,
		&swapChain1
	));

	if (!AllowAltEnterFullscreen)
		ThrowIfFailed(factory->MakeWindowAssociation(handle, DXGI_MWA_NO_ALT_ENTER));

	ThrowIfFailed(swapChain1.As(&swapChain4));

	return swapChain4;
}

DXGI_SWAP_CHAIN_DESC1 GameWindow::GetSwapChainDescription(uint32_t width, uint32_t height, uint32_t bufferCount) const
{
	DXGI_SWAP_CHAIN_DESC1 description = { };
	description.Width = width;
	description.Height = height;
	description.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	description.Stereo = false;
	description.SampleDesc = { 1, 0 };
	description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	description.BufferCount = bufferCount;
	description.Scaling = DXGI_SCALING_STRETCH;
	description.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	description.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	description.Flags = CheckTearingSupport() ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

	return description;
}

bool GameWindow::CheckTearingSupport() const
{
	bool allowTearing = false;

	// Rather than create the DXGI 1.5 factory interface directly, we create the
	// DXGI 1.4 interface and query for the 1.5 interface. This is to enable the 
	// graphics debugging tools which will not support the 1.5 factory interface 
	// until a future update.
	ComPtr<IDXGIFactory4> factory4;
	if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(&factory4))))
	{
		ComPtr<IDXGIFactory5> factory5;
		if (SUCCEEDED(factory4.As(&factory5)))
		{
			if (FAILED(factory5->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(allowTearing))))
				allowTearing = false;
		}
	}

	return allowTearing;
}

ComPtr<ID3D12CommandQueue> GameWindow::CreateCommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type) const
{
	ComPtr<ID3D12CommandQueue> commandQueue;

	D3D12_COMMAND_QUEUE_DESC desc = {};
	desc.Type		= type;
	desc.Priority	= D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags		= D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask	= 0;

	ThrowIfFailed(device->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue)));

	return commandQueue;
}

ComPtr<ID3D12Device2> GameWindow::CreateDevice(ComPtr<IDXGIAdapter4> adapter) const
{
	ComPtr<ID3D12Device2> device;
	ThrowIfFailed(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device)));

#if defined(_DEBUG)
	EnableDebugMessages();
#endif

	return device;
}

void GameWindow::EnableDebugMessages() const
{
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(device.As(&infoQueue)))
	{
		for (auto severity : IgnoreSeverity)
			infoQueue->SetBreakOnSeverity(severity, TRUE);

		D3D12_INFO_QUEUE_FILTER filter = {};
		filter.DenyList.NumCategories = _countof(IgnoreCategories);
		filter.DenyList.pCategoryList = IgnoreCategories;

		filter.DenyList.NumSeverities = _countof(IgnoreSeverity);
		filter.DenyList.pSeverityList = IgnoreSeverity;

		filter.DenyList.NumIDs = _countof(IgnoreMessages);
		filter.DenyList.pIDList = IgnoreMessages;

		ThrowIfFailed(infoQueue->PushStorageFilter(&filter));
	}
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