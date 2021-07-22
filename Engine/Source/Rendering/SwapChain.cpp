#include "SwapChain.h"

#include <SDL_syswm.h>

#include "Application/Application.h"
#include "Application/Window.h"

using namespace ArtemisEngine;

SwapChain::SwapChain(Window* window, shared_ptr<GraphicsDevice> graphicsDevice) : TargetWindow(window), Device(move(graphicsDevice))
{
	DXGI_SWAP_CHAIN_DESC description = GetDescription();
	ComPtr<IDXGIFactory> factory = GetFactory();

	CheckResult(factory->CreateSwapChain(
		Device->GetRawDevice().Get(),
		&description,
		&RawSwapChain),
		"Failed creating swapchain");
}

DXGI_SWAP_CHAIN_DESC SwapChain::GetDescription() const
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	swapChainDesc.BufferDesc = GetBufferDescription();
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	Device->GetMSAASupport(swapChainDesc.BufferDesc.Format, &swapChainDesc.SampleDesc.Count, &swapChainDesc.SampleDesc.Quality);

	swapChainDesc.Flags = 0;

	SDL_SysWMinfo sysWMInfo;
	SDL_VERSION(&sysWMInfo.version);
	SDL_GetWindowWMInfo(TargetWindow->GetRaw(), &sysWMInfo);

	swapChainDesc.OutputWindow = sysWMInfo.info.win.window;

	return swapChainDesc;
}

DXGI_MODE_DESC SwapChain::GetBufferDescription() const
{
	DXGI_MODE_DESC description;
	description.Width = TargetWindow->GetWidth();
	description.Height = TargetWindow->GetHeight();
	description.RefreshRate = { 0, 1 };
	description.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	description.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	description.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	return description;
}

ComPtr<IDXGIFactory> SwapChain::GetFactory() const
{
	ComPtr<ID3D11Device> device = Device->GetRawDevice();

	ComPtr<IDXGIDevice> dxgiDevice;
	CheckResult(device->QueryInterface(__uuidof(IDXGIDevice), &dxgiDevice),
	format("{}: Couldn't get IDXGIDevice", FuncName));

	ComPtr<IDXGIAdapter> adapter = 0;
	CheckResult(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), &adapter),
	format("{}: Couldn't get IDXGIAdapter", FuncName));

	ComPtr<IDXGIFactory> factory = 0;
	CheckResult(adapter->GetParent(__uuidof(IDXGIFactory), &factory),
	format("{}: Couldn't get IDXGIFactory", FuncName));

	return factory;
}

ComPtr<IDXGISwapChain> SwapChain::GetRawSwapChain() const
{
	return RawSwapChain;
}

void SwapChain::GetBuffer(ComPtr<ID3D11Texture2D>& backBuffer) const
{
	CheckResult(RawSwapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())),
	format("{}: Couldn't get Texture buffer", FuncName));
}

void SwapChain::Present() const
{
	CheckResult(RawSwapChain->Present(false, 0),
	format("{}: Couldn't present swapchain", FuncName));
}