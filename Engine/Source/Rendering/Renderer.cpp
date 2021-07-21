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

Color Renderer::BackbufferColor = Color::Black;

Renderer::Renderer(Window* targetWindow) : MainWindow(targetWindow)
{
	WorldMatrix = XMMatrixIdentity();
	
	RawBackbufferColor = new float[4];
	Color::Black.ToFloat(RawBackbufferColor);
	
	InitializeD3D();
}

Renderer::~Renderer()
{
	delete[] RawBackbufferColor;
}

void Renderer::DoRender()
{
	//RenderTargetView->Clear(RawBackbufferColor);
	Color::Black.ToFloat(RawBackbufferColor);
	Device->ClearRenderTargetView(RawBackbufferColor);
	Device->ClearDepthStencilView();

	XMMATRIX viewMatrix = XMMatrixIdentity();
	//bool result;

	
	// Generate the view matrix based on the camera's position.
	MainCamera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	//m_Direct3D->GetWorldMatrix(worldMatrix);
	MainCamera->GetViewMatrix(viewMatrix);
	//m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	TestModel->Render(Device->GetRawContext().Get());

	// Render the model using the color shader.
	//result = ColorShader->Render(Device->GetRawContext().Get(), TestModel->GetIndexCount(), WorldMatrix, viewMatrix, ProjectionMatrix);
	
	Device->Present();
	//SwapChain->Present();
}

shared_ptr<Camera> Renderer::GetMainCamera()
{
	return MainCamera;
}

shared_ptr<SwapChain> Renderer::GetSwapChain()
{
	return SwapChain;
}

void Renderer::InitializeD3D()
{
	CreateDevice();
	//CreateSwapChain();
	//CreateRenderTarget();
	CreateProjectionMatrix();
	CreateRenderObjects();
}

void Renderer::CreateRenderTarget()
{
	RenderTargetView = make_shared<ArtemisEngine::RenderTargetView>(SwapChain, Device);
	Device->GetRawContext()->OMSetRenderTargets(1, &RenderTargetView->GetRawRenderTargetView(), Device->GetRawStencilView().Get());

	ID3D11RenderTargetView* view[4];
	Device->GetRawContext()->OMGetRenderTargets(1, view, nullptr);
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
	//ProjectionMatrix = XMMatrixOrthographicLH(static_cast<float>(MainWindow->GetWidth()), static_cast<float>(MainWindow->GetHeight()), 0.f, 1.f);
	ProjectionMatrix = XMMatrixPerspectiveFovLH(3.141592654f / 4.0f, static_cast<float>(MainWindow->GetWidth())/ static_cast<float>(MainWindow->GetHeight()), 0.001f, 100.0f);
}

void Renderer::CreateRenderObjects()
{
	MainCamera = make_shared<Camera>();
	TestModel = make_shared<Model>();
	//ColorShader = make_shared<ColorShaderClass>();

	TestModel->Initialize(Device->GetRawDevice().Get());
	//ColorShader->Initialize(Device->GetRawDevice().Get(), MainWindow->GetHandle());
}