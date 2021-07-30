#include "GraphicsDevice.h"

#pragma comment(lib, "dxgi.lib")

#include <utility>

#include <d3d11.h>
#include <directxmath.h>
#include <wrl/client.h>

#include "Renderer.h"
#include "Application/Window.h"
#include "Core/Math.h"
#include "Core/StringUtility.h"

using namespace ArtemisEngine;

DefineLogCategory(LogGraphicsDevice, Verbosity::VeryVerbose);

const std::map<D3D_FEATURE_LEVEL, string> GraphicsDevice::FeatureLevelNames
{
	{ D3D_FEATURE_LEVEL_9_1, "9.3" },
	{ D3D_FEATURE_LEVEL_9_2, "9.2" },
	{ D3D_FEATURE_LEVEL_9_3, "9.3" },
	{ D3D_FEATURE_LEVEL_10_0, "10.0" },
	{ D3D_FEATURE_LEVEL_10_1, "10.1" },
	{ D3D_FEATURE_LEVEL_11_0, "11.0" },
	{ D3D_FEATURE_LEVEL_11_1, "11.1" },
	{ D3D_FEATURE_LEVEL_12_0, "12.0" },
	{ D3D_FEATURE_LEVEL_12_1, "12.1" },
};

D3D_FEATURE_LEVEL GraphicsDevice::FeatureLevels[] =
{
	D3D_FEATURE_LEVEL_11_0,
};

GraphicsDevice::GraphicsDevice(Window* targetWindow) : TargetWindow(targetWindow), WorldMatrix(XMMatrixIdentity()), ScreenNear(0.1f), ScreenFar(1000.f)
{
	CreateDevice();

	CreateDepthStencilBuffer();
	CreateDepthStencilState();
	CreateDepthStencilView();
	CreateViewport();
	CreateProjectionMatrix();
	CacheGPUInformation();
	SetViewport();
}

GraphicsDevice::~GraphicsDevice()
{
	RawDevice->Release();
	RawDevice = nullptr;
}

ComPtr<ID3D11Device> GraphicsDevice::GetRawDevice() const
{
	return RawDevice;
}

ComPtr<ID3D11DeviceContext> GraphicsDevice::GetRawContext() const
{
	return RawContext;
}

ComPtr<ID3D11DepthStencilView> GraphicsDevice::GetRawStencilView() const
{
	return RawDepthStencilView;
}

ComPtr<ID3D11RasterizerState> GraphicsDevice::GetRawRasterizerState() const
{
	return RawRasterizerState;
}

ComPtr<ID3D11Texture2D> GraphicsDevice::GetRawDepthStencilBuffer() const
{
	return RawDepthStencilBuffer;
}

ComPtr<ID3D11DepthStencilState> GraphicsDevice::GetRawDepthStencilState() const
{
	return RawDepthStencilState;
}

ComPtr<IDXGIFactory> GraphicsDevice::CreateFactory()
{
	ComPtr<IDXGIFactory> factory;
	CheckResult(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(factory.GetAddressOf())),
		"Failed initializing factory");
	return factory;
}

ComPtr<IDXGIAdapter> GraphicsDevice::CreateAdapter()
{
	ComPtr<IDXGIAdapter> adapter;

	ComPtr<IDXGIFactory> factory = CreateFactory();
	CheckResult(factory->EnumAdapters(0, adapter.GetAddressOf()),
		"Failed creating adapter for GPU");

	return adapter;
}

void GraphicsDevice::GetMSAASupport(DXGI_FORMAT dxgiFormat, UINT* sampleCount, UINT* quality) const
{
	*sampleCount = 1;
	*quality = 0;
	
	UINT qualityBuffer = 0;

	CheckResult(RawDevice->CheckMultisampleQualityLevels(dxgiFormat, MSAASampleCount, &qualityBuffer),
		format("{}: Failed checking multi-sample quality levels", FuncName));

	// Quality buffer starts at 0, so we have to subtract one value
	qualityBuffer--;

	if (qualityBuffer == 0)
	{
		*sampleCount = 1;
		*quality = 0;
	}
	else
	{
		*sampleCount = MSAASampleCount;
		*quality = qualityBuffer;
	}
}

void GraphicsDevice::CreateRenderTargetView(const ComPtr<ID3D11Texture2D>& backBuffer, ComPtr<ID3D11RenderTargetView>& renderTargetView) const
{
	CheckResult(RawDevice->CreateRenderTargetView(backBuffer.Get(), 0, &renderTargetView),
		format("{}: Couldn't create RenderTargetView", FuncName));
}

void GraphicsDevice::ClearRenderTargetView(const float* clearColor)
{
	RawContext->ClearRenderTargetView(RenderTargetView.Get(), clearColor);
}

void GraphicsDevice::ClearDepthStencilView()
{
	RawContext->ClearDepthStencilView(RawDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.f, 0);
}

void GraphicsDevice::Present()
{
	m_swapChain->Present(0, 0);
}

string GraphicsDevice::GetFeatureLevelString() const
{
	const auto iter = FeatureLevelNames.find(UsedFeatureLevel);
	if (iter != FeatureLevelNames.end())
	{
		return iter->second;
	}
	else
	{
		Log(LogGraphicsDevice, Verbosity::Error, "Couldn't find feature name for feature level " + std::to_string(UsedFeatureLevel));
		return std::format("N/A ({})", std::to_string(UsedFeatureLevel));
	}
}

uint32 GraphicsDevice::GetDeviceFlags()
{
	uint32 flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	return flags;
}

void GraphicsDevice::OutputDebugInfo() const
{
	Log(LogGraphicsDevice, Verbosity::Log, std::format("DirectX Feature Level: {}", GetFeatureLevelString()));
	Log(LogGraphicsDevice, Verbosity::Log, std::format("DirectX Graphics Adapter: {}", GetGraphicsAdapterString()));
}

string GraphicsDevice::GetGraphicsAdapterString() const
{
	ComPtr<IDXGIDevice> dxgiDevice;
	CheckResult(RawDevice->QueryInterface(__uuidof(IDXGIDevice), &dxgiDevice),
		std::format("{}: {}", FuncName, "Couldn't get IDXGIDevice"));

	ComPtr<IDXGIAdapter> adapter;
	CheckResult(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), &adapter),
		std::format("{}: {}", FuncName, "Couldn't get IDXGIAdapter"));

	DXGI_ADAPTER_DESC description;
	CheckResult(adapter->GetDesc(&description),
		std::format("{}: {}", FuncName, "Couldn't get description"));

	return StringUtility::ConvertWideToUtf8(description.Description);
}

void GraphicsDevice::CreateDevice()
{
	const uint32 featureLevelsNum = ARRAYSIZE(FeatureLevels);



	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = TargetWindow->GetWidth();
	swapChainDesc.BufferDesc.Height = TargetWindow->GetHeight();

	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	swapChainDesc.OutputWindow = TargetWindow->GetHandle();

	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// Set to full screen or windowed mode.
	swapChainDesc.Windowed = true;

	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	// Set the feature level to DirectX 11.
	featureLevel = D3D_FEATURE_LEVEL_11_0;


	

	CheckResult(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, GetDeviceFlags(), FeatureLevels, featureLevelsNum, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &RawDevice, &UsedFeatureLevel, &RawContext),
		"Unable to create device");

	if (UsedFeatureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported", 0, 0);
		throw DirectXException("Direct3D Feature Level 11 unsupported");
	}

	OutputDebugInfo();
}

void GraphicsDevice::CreateDepthStencilBuffer()
{
	D3D11_TEXTURE2D_DESC depthBufferDescription;
	
	depthBufferDescription.Width = TargetWindow->GetWidth();
	depthBufferDescription.Height = TargetWindow->GetHeight();
	depthBufferDescription.MipLevels = 1;
	depthBufferDescription.ArraySize = 1;
	depthBufferDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDescription.SampleDesc.Count = 1;
	depthBufferDescription.SampleDesc.Quality = 0;
	depthBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDescription.CPUAccessFlags = 0;
	depthBufferDescription.MiscFlags = 0;

	CheckResult(RawDevice->CreateTexture2D(&depthBufferDescription, nullptr, &RawDepthStencilBuffer),
		format("{}: Failed creating depth buffer", FuncName));
}

void GraphicsDevice::CreateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDescription;
	
	depthStencilDescription.DepthEnable = true;
	depthStencilDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDescription.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDescription.StencilEnable = true;
	depthStencilDescription.StencilReadMask = 0xFF;
	depthStencilDescription.StencilWriteMask = 0xFF;
	
	depthStencilDescription.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDescription.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDescription.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDescription.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	
	depthStencilDescription.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDescription.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDescription.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDescription.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	
	CheckResult(RawDevice->CreateDepthStencilState(&depthStencilDescription, &RawDepthStencilState),
		format("{}: Failed creating depth stencil state", FuncName));
	
	RawContext->OMSetDepthStencilState(RawDepthStencilState.Get(), 1);
}

void GraphicsDevice::CreateDepthStencilView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDescription;

	depthStencilViewDescription.Flags = 0;
	depthStencilViewDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDescription.Texture2D.MipSlice = 0;
	
	CheckResult(RawDevice->CreateDepthStencilView(RawDepthStencilBuffer.Get(), &depthStencilViewDescription, &RawDepthStencilView),
		format("{}: Failed creating depth stencil view", FuncName));

	


	// Get the pointer to the back buffer.
	ID3D11Texture2D* backBufferPtr;
	HRESULT result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);

	// Create the render target view with the back buffer pointer.
	result = RawDevice->CreateRenderTargetView(backBufferPtr, NULL, RenderTargetView.GetAddressOf());

	
	RawContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), RawDepthStencilView.Get());
	
	/*ID3D11RenderTargetView* view[4];
	RawContext->OMGetRenderTargets(1, view, nullptr);*/
}

void GraphicsDevice::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterDescription;

	rasterDescription.AntialiasedLineEnable = false;
	rasterDescription.CullMode = D3D11_CULL_BACK;
	rasterDescription.DepthBias = 0;
	rasterDescription.DepthBiasClamp = 0.0f;
	rasterDescription.DepthClipEnable = true;
	rasterDescription.FillMode = D3D11_FILL_SOLID;
	rasterDescription.FrontCounterClockwise = false;
	rasterDescription.MultisampleEnable = false;
	rasterDescription.ScissorEnable = false;
	rasterDescription.SlopeScaledDepthBias = 0.0f;
	
	CheckResult(RawDevice->CreateRasterizerState(&rasterDescription, &RawRasterizerState),
		format("{}: Failed creating rasterizer state", FuncName));
	
	RawContext->RSSetState(RawRasterizerState.Get());
}

void GraphicsDevice::CreateViewport()
{
	Viewport.Width = static_cast<FLOAT>(TargetWindow->GetWidth());
	Viewport.Height = static_cast<FLOAT>(TargetWindow->GetHeight());
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	Viewport.TopLeftX = 0.0f;
	Viewport.TopLeftY = 0.0f;
	
	RawContext->RSSetViewports(1, &Viewport);
}

///

void GraphicsDevice::CacheGPUInformation()
{
	unsigned long long stringLength;
	DXGI_ADAPTER_DESC adapterDesc;
	ComPtr<IDXGIAdapter> adapter = CreateAdapter();
	
	// Get the adapter (video card) description.
	CheckResult(adapter->GetDesc(&adapterDesc),
	            "Couldn't retrieve GPU description");

	// Store the dedicated video card memory in megabytes.
	GPUMemory = static_cast<int>(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a character array and store it.
	char tempGPUName[128];
	const int error = wcstombs_s(&stringLength, tempGPUName, 128, adapterDesc.Description, 128);
	if (error != 0)
	{
		throw DirectXException("Couldn't store GPU name");
	}

	GPUName = string(tempGPUName);
}

void GraphicsDevice::SetViewport() const
{
	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(TargetWindow->GetWidth());
	viewport.Height = static_cast<float>(TargetWindow->GetHeight());
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport.
	RawContext->RSSetViewports(1, &viewport);
}

void GraphicsDevice::SetVSync(bool enabled)
{
	VSyncEnabled = enabled;
}

void GraphicsDevice::CreateProjectionMatrix()
{
	// Create an orthographic projection matrix for 2D rendering.
	ProjectionMatrix = XMMatrixOrthographicLH(static_cast<float>(TargetWindow->GetWidth()) / 100.f, static_cast<float>(TargetWindow->GetHeight()) / 100.f, ScreenNear, ScreenFar);
}

void GraphicsDevice::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];


	// Setup the color to clear the buffer to.
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	// Clear the back buffer.
	RawContext->ClearRenderTargetView(RenderTargetView.Get(), color);

	// Clear the depth buffer.
	RawContext->ClearDepthStencilView(RawDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void GraphicsDevice::EndScene()
{
	// Present the back buffer to the screen since rendering is complete.
	if (VSyncEnabled)
	{
		// Lock to screen refresh rate.
		GetSwapChain()->Present(1, 0);
	}
	else
	{
		// Present as fast as possible.
		GetSwapChain()->Present(0, 0);
	}
}

ID3D11Device* GraphicsDevice::GetDevice()
{
	return RawDevice.Get();
}

ID3D11DeviceContext* GraphicsDevice::GetDeviceContext()
{
	return RawContext.Get();
}

ComPtr<IDXGISwapChain> GraphicsDevice::GetSwapChain() const
{
	return TargetWindow->GetRenderer()->GetSwapChain()->GetRawSwapChain();
}

void GraphicsDevice::GetProjectionMatrix(XMMATRIX& projectionMatrix) const
{
	projectionMatrix = ProjectionMatrix;
}

void GraphicsDevice::GetWorldMatrix(XMMATRIX& worldMatrix) const
{
	worldMatrix = WorldMatrix;
}

void GraphicsDevice::Shutdown() const
{
	// Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
	GetSwapChain()->SetFullscreenState(false, nullptr);
}
