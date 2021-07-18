#include "GraphicsDevice.h"

#include <utility>

#include "Core/StringUtility.h"

using namespace ArtemisEngine;

DefineLogCategory(LogGraphicsDevice, Verbosity::VeryVerbose);

const std::map<D3D_FEATURE_LEVEL, string> GraphicsDevice::FeatureLevelNames
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

D3D_FEATURE_LEVEL GraphicsDevice::FeatureLevels[] =
{
	D3D_FEATURE_LEVEL_11_1,
};

GraphicsDevice::GraphicsDevice()
{
	const uint32 featureLevelsNum = ARRAYSIZE(FeatureLevels);
	
	CheckResult(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, GetDeviceFlags(), FeatureLevels, featureLevelsNum, D3D11_SDK_VERSION, &RawDevice, &UsedFeatureLevel, &RawContext),
		"Unable to create device");

	if (UsedFeatureLevel != D3D_FEATURE_LEVEL_11_1)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported", 0, 0);
		throw DirectXException("Direct3D Feature Level 11 unsupported");
	}

	OutputDebugInfo();
}

GraphicsDevice::~GraphicsDevice()
{
	RawDevice->Release();
	RawDevice = nullptr;
}

ComPtr<ID3D11Device> GraphicsDevice::GetRawDevice() const
{
	return RawDevice;
}

ComPtr<ID3D11DeviceContext> GraphicsDevice::GetRawContext() const
{
	return RawContext;
}

void GraphicsDevice::GetMSAASupport(DXGI_FORMAT dxgiFormat, UINT* sampleCount, UINT* quality) const
{
	*sampleCount = 1;
	*quality = 0;
	
	UINT qualityBuffer = 0;

	CheckResult(RawDevice->CheckMultisampleQualityLevels(dxgiFormat, MSAASampleCount, &qualityBuffer),
	format("{}: Failed checking multi-sample quality levels", FuncName));

	// Quality buffer starts at 0, so we have to subtract one value
	qualityBuffer--;

	if (qualityBuffer == 0)
	{
		*sampleCount = 1;
		*quality = 0;
	}
	else
	{
		*sampleCount = MSAASampleCount;
		*quality = qualityBuffer;
	}
}

void GraphicsDevice::CreateRenderTargetView(const ComPtr<ID3D11Texture2D>& backBuffer, ComPtr<ID3D11RenderTargetView>& renderTargetView) const
{
	CheckResult(RawDevice->CreateRenderTargetView(backBuffer.Get(), 0, &renderTargetView),
	format("{}: Couldn't create RenderTargetView", FuncName));
}

string GraphicsDevice::GetFeatureLevelString() const
{
	const auto iter = FeatureLevelNames.find(UsedFeatureLevel);
	if (iter != FeatureLevelNames.end())
	{
		return iter->second;
	}
	else
	{
		Log(LogGraphicsDevice, Verbosity::Error, "Couldn't find feature name for feature level " + std::to_string(UsedFeatureLevel));
		return std::format("N/A ({})", std::to_string(UsedFeatureLevel));
	}
}

uint32 GraphicsDevice::GetDeviceFlags()
{
	uint32 flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	return flags;
}

void GraphicsDevice::OutputDebugInfo() const
{
	Log(LogGraphicsDevice, Verbosity::Log, std::format("DirectX Feature Level: {}", GetFeatureLevelString()));
	Log(LogGraphicsDevice, Verbosity::Log, std::format("DirectX Graphics Adapter: {}", GetGraphicsAdapterString()));
}

string GraphicsDevice::GetGraphicsAdapterString() const
{
	ComPtr<IDXGIDevice> dxgiDevice;
	CheckResult(RawDevice->QueryInterface(__uuidof(IDXGIDevice), &dxgiDevice),
		std::format("{}: {}", FuncName, "Couldn't get IDXGIDevice"));

	ComPtr<IDXGIAdapter> adapter;
	CheckResult(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), &adapter),
		std::format("{}: {}", FuncName, "Couldn't get IDXGIAdapter"));

	DXGI_ADAPTER_DESC description;
	CheckResult(adapter->GetDesc(&description),
		std::format("{}: {}", FuncName, "Couldn't get description"));

	return StringUtility::ConvertWideToUtf8(description.Description);
}