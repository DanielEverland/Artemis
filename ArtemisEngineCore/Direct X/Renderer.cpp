#include "Renderer.h"

#include "Exceptions/DirectXException.h"
#include "VertexBuffer.h"

using ArtemisWindow::IWindow;

Renderer::Renderer(const IWindow* owner)
{
	gameWindow = owner;
}

void Renderer::Initialize()
{
	if (hasInitialized)
		throw DirectXException("DirectX has already been initialized!");

	CreateRawBackbufferColor();
	CreateResources();
	CreateViewport();

	hasInitialized = true;
}
void Renderer::Render()
{
	renderTargetView->Clear(rawBackBufferColor);
	depthBuffer->Clear();
	swapChain->Present();
}
void Renderer::Resize()
{
	renderTargetView->Reset();

	swapChain->Resize();
	renderTargetView->CreateBackBuffer();
	depthBuffer->Resize();

	CreateViewport();
}
void Renderer::CreateRawBackbufferColor()
{
	BackbufferColor.ToFloat(rawBackBufferColor);
}
void Renderer::CreateViewport()
{
	ComPtr<ID3D11DeviceContext> rawContext = graphicsDevice->GetRawContext();
	ComPtr<ID3D11RenderTargetView> rawRenderTargetView = renderTargetView->GetRawRenderTargetView();
	ComPtr<ID3D11DepthStencilView> rawDepthStencilView = depthBuffer->GetRawStencilView();

	rawContext->OMSetRenderTargets(1, &rawRenderTargetView, rawDepthStencilView.Get());

	D3D11_VIEWPORT viewPortDescription
	{
		0, 0, // Top left (x, y)
		static_cast<float>(gameWindow->GetWidth()),
		static_cast<float>(gameWindow->GetHeight()),
		0, 1, // Min, Max depth
	};

	rawContext->RSSetViewports(1, &viewPortDescription);
}
void Renderer::CreateResources()
{
	graphicsDevice = shared_ptr<GraphicsDevice>(new GraphicsDevice());
	swapChain = shared_ptr<SwapChain>(new SwapChain(gameWindow, graphicsDevice));
	renderTargetView = shared_ptr<RenderTargetView>(new RenderTargetView(swapChain, graphicsDevice));
	depthBuffer = shared_ptr<DepthBuffer>(new DepthBuffer(gameWindow, graphicsDevice));
}
void Renderer::Draw(const Mesh& mesh) const
{
	VertexBuffer vertexBuffer(mesh.Vertices);
	IndexBuffer indexBuffer(mesh.Indices);

	BindVertexBuffer(vertexBuffer);
	BindIndexBuffer(indexBuffer);
}
void Renderer::BindVertexBuffer(const VertexBuffer& vertexBuffer) const
{
	const unsigned int stride = vertexBuffer.GetStride();

	graphicsDevice->GetRawContext()->IASetVertexBuffers(
		0,
		1,
		&vertexBuffer.GetRawBuffer(),
		&stride,
		0);
}
void Renderer::BindIndexBuffer(IndexBuffer& indexBuffer) const
{
	graphicsDevice->GetRawContext()->IASetIndexBuffer(indexBuffer.GetRawBuffer().Get(), indexBuffer.GetFormat(), 0);
}