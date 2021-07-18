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
	WorldMatrix = XMMatrixIdentity();
	
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
	Device->ClearDepthStencilView();

	
	SwapChain->Present();
}

void Renderer::InitializeD3D()
{
	CreateDevice();
	CreateSwapChain();
	CreateRenderTarget();
	CreateProjectionMatrix();
}

void Renderer::CreateRenderTarget()
{
	RenderTargetView = make_shared<ArtemisEngine::RenderTargetView>(SwapChain, Device);
	Device->GetRawContext()->OMSetRenderTargets(1, &RenderTargetView->GetRawRenderTargetView(), Device->GetRawStencilView().Get());
}

void Renderer::CreateDevice()
{
	Device = make_shared<GraphicsDevice>(MainWindow);
}

void Renderer::CreateSwapChain()
{
	SwapChain = make_shared<ArtemisEngine::SwapChain>(MainWindow, Device);
}

void Renderer::CreateProjectionMatrix()
{
	ProjectionMatrix = XMMatrixOrthographicLH(static_cast<float>(MainWindow->GetWidth()), static_cast<float>(MainWindow->GetHeight()), 0.f, 1.f);
}