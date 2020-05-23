#pragma once

#include <memory>
#include <map>

#include "Private/DirectX/GraphicsDevice.h"
#include "Private/DirectX/SwapChain.h"
#include "Private/DirectX/DepthBuffer.h"
#include "Private/DirectX/RenderTargetView.h"
#include "Public/Game/SafePtr.h"
#include "Private/Windows/IWindow.h"
#include "Public/Game/Color.h"
#include "Public/Game/Mesh.h"


#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShaderObject.h"

namespace ArtemisEngine
{
	class Camera;
}

using namespace ArtemisEngine::Rendering;
using namespace ArtemisEngine;
using namespace ArtemisWindow;

using std::shared_ptr;
using std::map;

// Responsible for managing DirectX resources and the entire rendering pipeline
class Renderer
{
public:
	explicit Renderer(const IWindow* const window);

	VertexShaderObject* GetVertexShader(const string& name);
	ComPtr<ID3D11PixelShader> GetPixelShader(const string& name);
	
	bool GetUseWARPAdapter() const { return useWARPAdapter; }
	void SetUseWARPAdapter(const bool value) { useWARPAdapter = value; }

	bool IsInitialized() const { return hasInitialized; }

	void Initialize();
	void Render();
	void Resize();
	void CreateViewport();
	void SetRenderState(class RasterizerState* state);
	void SetCamera(SafePtr<Camera> camera);

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

	map<string, ComPtr<ID3D11PixelShader>> pixelShaders;
	map<string, VertexShaderObject> vertexShaders;

	SafePtr<Camera> mainCamera;
	
	const IWindow* gameWindow;

	void Draw(const Mesh& mesh) const;
	void CreateRawBackbufferColor();
	void CreateResources();
	void BindVertexBuffer(const VertexBuffer& vertexBuffer) const;
	void DrawVertices(const VertexBuffer& vertexBuffer) const;
	void BindIndexBuffer(IndexBuffer& indexBuffer) const;
	void DrawIndices(const IndexBuffer& indexBuffer) const;
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
	void CreateRenderStates() const;
	void LoadShaders();
};