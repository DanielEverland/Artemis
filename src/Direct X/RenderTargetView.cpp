#include "RenderTargetView.h"

RenderTargetView::RenderTargetView(const shared_ptr<SwapChain> const swapChain, const shared_ptr<GraphicsDevice> const graphicsDevice)
{
	swapChain->GetRawSwapChain().Get()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.Get()));
	graphicsDevice->GetRawDevice()->CreateRenderTargetView(backBuffer.Get(), 0, &renderTargetView);
}