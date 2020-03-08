#pragma once

#include <memory>

#include "Direct X/GraphicsDevice.h"
#include "Direct X/SwapChain.h"
#include "Direct X/DepthBuffer.h"
#include "Direct X/RenderTargetView.h"
#include "Windows/IWindow.h"

#include "Structs/Color.h"

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

	void CreateRawBackbufferColor();
	void CreateResources();
};

