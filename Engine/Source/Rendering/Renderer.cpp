#include "Renderer.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <format>

#include <SDL.h>

#include "DirectXCore.h"
#include "SwapChain.h"
#include "Core/StringUtility.h"

using namespace ArtemisEngine;

DefineLogCategory(LogRenderer, Verbosity::VeryVerbose);

Color Renderer::BackbufferColor = Color::CornflowerBlue;

Renderer::Renderer(Window* targetWindow) : MainWindow(targetWindow)
{
	RawBackbufferColor = new float[4];
	Color::CornflowerBlue.ToFloat(RawBackbufferColor);
	
	InitializeD3D();
}

Renderer::~Renderer()
{
	delete[] RawBackbufferColor;
}

void Renderer::DoRender()
{
	RenderTargetView->Clear(RawBackbufferColor);
	SwapChain->Present();
}

void Renderer::InitializeD3D()
{
	CreateDevice();
	CreateSwapChain();
	CreateRenderTarget();
}

void Renderer::CreateRenderTarget()
{
	RenderTargetView = make_shared<ArtemisEngine::RenderTargetView>(SwapChain, Device);
}

void Renderer::CreateDevice()
{
	Device = make_shared<GraphicsDevice>();
}

void Renderer::CreateSwapChain()
{
	SwapChain = make_shared<ArtemisEngine::SwapChain>(MainWindow, Device);
}