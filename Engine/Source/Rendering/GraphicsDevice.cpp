#include "GraphicsDevice.h"

#include <utility>

#include "Renderer.h"
#include "Application/Window.h"
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

GraphicsDevice::GraphicsDevice(Window* targetWindow) : TargetWindow(targetWindow)
{
	CreateDevice();

	CreateDepthStencilBuffer();
	CreateDepthStencilState();
	CreateDepthStencilView();
	CreateViewport();
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
	RawContext->ClearRenderTargetView(m_renderTargetView, clearColor);
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
	result = RawDevice->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);

	
	RawContext->OMSetRenderTargets(1, &m_renderTargetView, RawDepthStencilView.Get());
	
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