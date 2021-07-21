#pragma once

#include <SDL_video.h>
#include <d3d11.h>

#include "Camera.h"
#include "ColorShaderClass.h"
#include "Core.h"
#include "DirectXCore.h"
#include "GraphicsDevice.h"
#include "Model.h"
#include "RenderTargetView.h"
#include "SwapChain.h"
#include "Application/Window.h"
#include "Core/Color.h"

namespace ArtemisEngine
{
	using namespace std;
	
	class Renderer
	{
	public:
		Renderer(Window* targetWindow);
		~Renderer();

		void DoRender();
		
		[[nodiscard]] shared_ptr<Camera> GetMainCamera();
		[[nodiscard]] shared_ptr<SwapChain> GetSwapChain();
	
	private:
		static Color BackbufferColor;
		
		Window* MainWindow;
		float* RawBackbufferColor;

		shared_ptr<GraphicsDevice> Device;
		shared_ptr<SwapChain> SwapChain;
		shared_ptr<RenderTargetView> RenderTargetView;
		shared_ptr<Camera> MainCamera;
		shared_ptr<Model> TestModel;
		//shared_ptr<ColorShaderClass> ColorShader;

		XMMATRIX ProjectionMatrix;
		XMMATRIX WorldMatrix;
				
		void InitializeD3D();
		void CreateRenderTarget();
		void CreateDevice();
		void CreateSwapChain();
		void CreateProjectionMatrix();
		void CreateRenderObjects();
	};
}
