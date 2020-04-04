#include "Renderer.h"

#include <memory>

#include "RasterizerState.h"
#include "RenderStateGroups.h"
#include "VertexBuffer.h"

#include "Include/Exceptions/DirectXException.h"

using ArtemisWindow::IWindow;
using namespace ArtemisEngine::Rendering;

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
	CreateRenderStates();

	SetRenderState(RenderStateGroups::GetSolidState());

	hasInitialized = true;
}
void Renderer::Render()
{
	renderTargetView->Clear(rawBackBufferColor);
	depthBuffer->Clear();
	swapChain->Present();

	//SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//// Test remove this hard reference to mesh
	//VertexBufferData vertexBufferData(8);
	//vertexBufferData[0] = Vector3(-1.0, -1.0, -1.0);
	//vertexBufferData[1] = Vector3(-1.0, 1.0, -1.0);
	//vertexBufferData[2] = Vector3(1.0, 1.0, -1.0);
	//vertexBufferData[3] = Vector3(1.0, -1.0, -1.0);
	//vertexBufferData[4] = Vector3(-1.0, -1.0, 1.0);
	//vertexBufferData[5] = Vector3(-1.0, 1.0, 1.0);
	//vertexBufferData[6] = Vector3(1.0, 1.0, 1.0);
	//vertexBufferData[7] = Vector3(1.0, -1.0, 1.0);

	//IndexBufferData ibd(8 * 3);
	//ibd[0] = 0;		ibd[1] = 1;		ibd[2] = 2;
	//ibd[3] = 0;		ibd[4] = 2;		ibd[5] = 3;
	//ibd[6] = 0;		ibd[7] = 3;		ibd[8] = 4;
	//ibd[9] = 0;		ibd[10] = 4;	ibd[11] = 5;
	//ibd[12] = 0;	ibd[13] = 5;	ibd[14] = 6;
	//ibd[15] = 0;	ibd[16] = 6;	ibd[17] = 7;
	//ibd[18] = 0;	ibd[19] = 7;	ibd[20] = 8;
	//ibd[21] = 0;	ibd[22] = 8;	ibd[23] = 1;

	//Mesh mesh = {};
	//mesh.Indices = ibd;
	//mesh.Vertices = vertexBufferData;
	//// End Test

	//Draw(mesh);
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

void Renderer::SetRenderState(class RasterizerState* state)
{
	graphicsDevice->GetRawContext()->RSSetState(state->GetRawState());
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
	VertexBuffer vertexBuffer(*graphicsDevice, mesh.Vertices);
	IndexBuffer indexBuffer(*graphicsDevice, mesh.Indices);

	BindVertexBuffer(vertexBuffer);
	DrawVertices(vertexBuffer);

	BindIndexBuffer(indexBuffer);
	DrawIndices(indexBuffer);
}
void Renderer::BindVertexBuffer(const VertexBuffer& vertexBuffer) const
{
	const unsigned int stride = vertexBuffer.GetStride();
	const unsigned int offset = 0;

	ComPtr<ID3D11Buffer> buffer = vertexBuffer.GetRawBuffer();
	ComPtr<ID3D11DeviceContext> context = graphicsDevice->GetRawContext();

	context->IASetVertexBuffers(0, 1,
		&buffer,
		&stride,
		&offset);
}
void Renderer::DrawVertices(const VertexBuffer& vertexBuffer) const
{
	graphicsDevice->GetRawContext()->Draw(vertexBuffer.GetLength(), 0);
}
void Renderer::BindIndexBuffer(IndexBuffer& indexBuffer) const
{
	graphicsDevice->GetRawContext()->IASetIndexBuffer(indexBuffer.GetRawBuffer().Get(), indexBuffer.GetFormat(), 0);
}
void Renderer::DrawIndices(const IndexBuffer& indexBuffer) const
{
	graphicsDevice->GetRawContext()->DrawIndexed(indexBuffer.GetLength(), 0, 0);
}
void Renderer::SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	graphicsDevice->GetRawContext()->IASetPrimitiveTopology(topology);
}

void Renderer::CreateRenderStates() const
{
	RenderStateGroups::CreateStateGroups(graphicsDevice.get());
}
