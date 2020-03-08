#include "Exceptions/NullReferenceException.h"
#include "RenderTargetView.h"
#include "DirectXHelper.h"

RenderTargetView::RenderTargetView(const shared_ptr<const SwapChain> swapChain, const shared_ptr<const GraphicsDevice> graphicsDevice)
{
	this->swapChain = swapChain;
	this->graphicsDevice = graphicsDevice;

	CreateBackBuffer();
}

void RenderTargetView::CreateBackBuffer()
{
	GetSwapChain()->GetBuffer(backBuffer);
	graphicsDevice->CreateRenderTargetView(backBuffer, renderTargetView);
}

ComPtr<ID3D11RenderTargetView> RenderTargetView::GetRawRenderTargetView() const
{
	return renderTargetView;
}

void RenderTargetView::Clear(const float* clearColor) const
{
	graphicsDevice->GetRawContext()->ClearRenderTargetView(renderTargetView.Get(), clearColor);
}

void RenderTargetView::Reset()
{
	renderTargetView.Reset();
	backBuffer.Reset();
}

const shared_ptr<const SwapChain> RenderTargetView::GetSwapChain() const
{
	if (swapChain.use_count() == 0)
		throw NullReferenceException("SwapChain has expired");

	return shared_ptr<const SwapChain>(swapChain);
}