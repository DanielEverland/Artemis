#include "RenderTargetView.h"

using namespace ArtemisEngine;

RenderTargetView::RenderTargetView(shared_ptr<ArtemisEngine::SwapChain> swapChain, shared_ptr<ArtemisEngine::GraphicsDevice> graphicsDevice) : SwapChain(swapChain), GraphicsDevice(graphicsDevice)
{	
	swapChain->GetBuffer(BackBuffer);
	graphicsDevice->CreateRenderTargetView(BackBuffer, RawRenderTargetView);
}

void RenderTargetView::Clear(const float* clearColor) const
{
	GraphicsDevice->GetRawContext()->ClearRenderTargetView(RawRenderTargetView.Get(), clearColor);
}

ComPtr<ID3D11RenderTargetView> RenderTargetView::GetRawRenderTargetView() const
{
	return RawRenderTargetView;
}
