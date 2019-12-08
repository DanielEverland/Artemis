#include <assert.h>

#include "GraphicsDevice.h"
#include "DirectXHelper.h"
#include "Exceptions/DirectXException.h"


IDXGIAdapter* GraphicsDevice::DefaultAdapter = 0;
HMODULE GraphicsDevice::DefaultSoftwareDevice = 0;

const std::map<D3D_FEATURE_LEVEL, string> GraphicsDevice::featureLevelNames
{
	{ D3D_FEATURE_LEVEL_1_0_CORE, "MCDM Core 1.0" },
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

GraphicsDevice::GraphicsDevice()
{
	CreateDeviceObject();
}

void GraphicsDevice::CreateRenderTargetView(const ComPtr<ID3D11Texture2D>& backBuffer, ComPtr<ID3D11RenderTargetView>& renderTargetView) const
{
	ThrowIfFailed(device->CreateRenderTargetView(backBuffer.Get(), 0, &renderTargetView));
}

ComPtr<ID3D11Device> GraphicsDevice::GetRawDevice() const
{
	return device;
}
ComPtr<ID3D11DeviceContext> GraphicsDevice::GetRawContext() const
{
	return context;
}

void GraphicsDevice::CreateDeviceObject()
{
	UINT deviceFlags = GetDeviceFlags();

	ThrowIfFailed(D3D11CreateDevice(
		DefaultAdapter,
		D3D_DRIVER_TYPE_HARDWARE,
		DefaultSoftwareDevice,
		deviceFlags,
		&FeatureLevels, FeatureLevelCount,
		D3D11_SDK_VERSION,
		&device,
		&usedFeatureLevel,
		&context
	));
	
	if (usedFeatureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, "Direct3D Feature Level 11 unsupported", 0, 0);
		throw DirectXException("Direct3D Feature Level 11 unsupported");
	}
	else
	{
		Output::Space();
		OutputDebugInfo();
		Output::Space();
	}
}
UINT GraphicsDevice::GetDeviceFlags()
{
	UINT deviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	return deviceFlags;
}
#pragma warning (suppress : 26812)
void GraphicsDevice::GetMSAASupport(DXGI_FORMAT format, UINT* sampleCount, UINT* quality) const
{
	*sampleCount = 1;
	*quality = 0;

	if (GraphicsDevice::MSAASampleCount > D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT)
	{
		throw DirectXException("Requested MSAA sample size is " + std::to_string(GraphicsDevice::MSAASampleCount) + ", but maximum sample count is " + std::to_string(D3D10_MAX_MULTISAMPLE_SAMPLE_COUNT));
	}

	UINT qualityBuffer = 0;

	ThrowIfFailed(device->CheckMultisampleQualityLevels(format, GraphicsDevice::MSAASampleCount, &qualityBuffer));

	// Quality buffer starts at 0, so we have to subtract one value
	qualityBuffer--;
	
	if (qualityBuffer == 0)
	{
		*sampleCount = 1;
		*quality = 0;
	}
	else
	{
		*sampleCount = GraphicsDevice::MSAASampleCount;
		*quality = qualityBuffer;
	}
}

string GraphicsDevice::GetFeatureLevelString() const
{
	auto iter = featureLevelNames.find(usedFeatureLevel);
	if (iter != featureLevelNames.end())
	{
		return iter->second;
	}
	else
	{
		DirectXLogError("Couldn't find feature name for feature level " + std::to_string(usedFeatureLevel));
		return "N/A (" + std::to_string(usedFeatureLevel) + ")";
	}
}

void GraphicsDevice::OutputDebugInfo() const
{
	DirectXLogLine("Initialized DirectX");

	OutputFeatureLevel();
	OutputGraphicsAdapter();
}
void GraphicsDevice::OutputFeatureLevel() const
{
	DirectXLogLine("Feature Level: " + GetFeatureLevelString());
}
void GraphicsDevice::OutputGraphicsAdapter() const
{
	ComPtr<IDXGIDevice> dxgiDevice;
	ThrowIfFailed(device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	ComPtr<IDXGIAdapter> adapter = 0;
	ThrowIfFailed(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&adapter));

	DXGI_ADAPTER_DESC description;
	ThrowIfFailed(adapter->GetDesc(&description));

	DirectXLogLine(description.Description);
}