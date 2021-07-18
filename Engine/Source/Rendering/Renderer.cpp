#include "Renderer.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <format>
#include <utility>

#include "DirectXCore.h"
#include "Core/StringUtility.h"

using namespace ArtemisEngine;

DefineLogCategory(LogRenderer, Verbosity::VeryVerbose);

const std::map<D3D_FEATURE_LEVEL, string> Renderer::FeatureLevelNames
{
	{ D3D_FEATURE_LEVEL_9_1, "9.3" },
	{ D3D_FEATURE_LEVEL_9_2, "9.2" },
	{ D3D_FEATURE_LEVEL_9_3, "9.3" },
	{ D3D_FEATURE_LEVEL_10_0, "10.0" },
	{ D3D_FEATURE_LEVEL_10_1, "10.1" },
	{ D3D_FEATURE_LEVEL_11_0, "11.0" },
	{ D3D_FEATURE_LEVEL_11_1, "11.1" },
	{ D3D_FEATURE_LEVEL_12_0, "12.0" },
	{ D3D_FEATURE_LEVEL_12_1, "12.1" },
};

D3D_FEATURE_LEVEL Renderer::FeatureLevels[] =
{
	D3D_FEATURE_LEVEL_11_1,
};

Renderer::Renderer(SDL_Window* targetWindow)
{
	Window = std::move(targetWindow);

	InitializeD3D();
}

void Renderer::InitializeD3D()
{
	const uint32 featureLevelsNum = ARRAYSIZE(FeatureLevels);
	CheckResult(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, GetDeviceFlags(), FeatureLevels, featureLevelsNum, D3D11_SDK_VERSION, &Device, &UsedFeatureLevel, &Context),
	"Unable to create device");

	if (UsedFeatureLevel != D3D_FEATURE_LEVEL_11_1)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported", 0, 0);
		throw DirectXException("Direct3D Feature Level 11 unsupported");
	}
	
	OutputDebugInfo();
}

uint32 Renderer::GetDeviceFlags()
{
	uint32 flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	return flags;
}

void Renderer::OutputDebugInfo() const
{
	Log(LogRenderer, Verbosity::Log, std::format("DirectX Feature Level: {}", GetFeatureLevelString()));
	Log(LogRenderer, Verbosity::Log, std::format("DirectX Graphics Adapter: {}", GetGraphicsAdapterString()));
}

string Renderer::GetFeatureLevelString() const
{
	const auto iter = FeatureLevelNames.find(UsedFeatureLevel);
	if (iter != FeatureLevelNames.end())
	{
		return iter->second;
	}
	else
	{
		Log(LogRenderer, Verbosity::Error, "Couldn't find feature name for feature level " + std::to_string(UsedFeatureLevel));
		return std::format("N/A ({})", std::to_string(UsedFeatureLevel));
	}
}

string Renderer::GetGraphicsAdapterString() const
{
	ComPtr<IDXGIDevice> dxgiDevice;
	CheckResult(Device->QueryInterface(__uuidof(IDXGIDevice), &dxgiDevice),
	std::format("{}: {}", FuncName, "Couldn't get IDXGIDevice"));

	ComPtr<IDXGIAdapter> adapter;
	CheckResult(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), &adapter),
	std::format("{}: {}", FuncName, "Couldn't get IDXGIAdapter"));

	DXGI_ADAPTER_DESC description;
	CheckResult(adapter->GetDesc(&description),
	std::format("{}: {}", FuncName, "Couldn't get description"));

	return StringUtility::ConvertWideToUtf8(description.Description);
}