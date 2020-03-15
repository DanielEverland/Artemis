#pragma once

#include <memory>

#include "Source/DirectX/GraphicsDevice.h"
#include "Source/DirectX/SwapChain.h"
#include "Source/DirectX/DepthBuffer.h"
#include "Source/DirectX/RenderTargetView.h"
#include "Source/Windows/IWindow.h"
#include "Include/Game/Color.h"

#include "Engine/Rendering/Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

using namespace ArtemisEngine;
using namespace ArtemisWindow;

using std::shared_ptr;

// Responsible for managing DirectX resources and the entire rendering pipeline
class Renderer
{
public:
	Renderer(const IWindow* const window);

	inline bool GetUseWARPAdapter() const { return useWARPAdapter; }
	inline void SetUseWARPAdapter(bool value) { useWARPAdapter = value; }

	inline bool IsInitialized() const { return hasInitialized; }

	void Initialize();
	void Render();
	void Resize();
	void CreateViewport();

private:
	static const uint8_t swapChainBufferSize = 3;

	Color BackbufferColor = Color::CornflowerBlue;

	bool hasInitialized = false;
	bool useWARPAdapter = false;
	float rawBackBufferColor[4] = {};

	shared_ptr<GraphicsDevice> graphicsDevice;
	shared_ptr<SwapChain> swapChain;
	shared_ptr<RenderTargetView> renderTargetView;
	shared_ptr<DepthBuffer> depthBuffer;

	const IWindow* gameWindow;

	void Draw(const Mesh& mesh) const;
	void CreateRawBackbufferColor();
	void CreateResources();
	void BindVertexBuffer(const VertexBuffer& vertexBuffer) const;
	void DrawVertices(const VertexBuffer& vertexBuffer) const;
	void BindIndexBuffer(IndexBuffer& indexBuffer) const;
	void DrawIndices(const IndexBuffer& indexBuffer) const;
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
};