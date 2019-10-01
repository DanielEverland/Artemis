#include <assert.h>

#include "GraphicsDevice.h"
#include "DirectXHelper.h"
#include "..\\Exceptions\DirectXException.h"


IDXGIAdapter* GraphicsDevice::DefaultAdapter = 0;
HMODULE GraphicsDevice::DefaultSoftwareDevice = 0;

GraphicsDevice::GraphicsDevice()
{
	CreateDeviceObject();
	AssertMSAASupport();
}

ComPtr<ID3D11Device> GraphicsDevice::GetRawDevice() const
{
	return device;
}
ComPtr<ID3D11DeviceContext> GraphicsDevice::GetRawContext() const
{
	return context;
}

bool GraphicsDevice::SupportsMSAA() const
{
	return MSAAQuality > 0;
}
UINT GraphicsDevice::GetMSAAQuality() const
{
	return MSAAQuality;
}
UINT GraphicsDevice::GetMSAASampleCount() const
{
	return MSAASampleCount;
}

void GraphicsDevice::CreateDeviceObject()
{
	UINT deviceFlags = GetDeviceFlags();

	HRESULT result = D3D11CreateDevice(
		DefaultAdapter,
		D3D_DRIVER_TYPE_HARDWARE,
		DefaultSoftwareDevice,
		deviceFlags,
		&FeatureLevels, FeatureLevelCount,
		D3D11_SDK_VERSION,
		&device,
		&usedFeatureLevel,
		&context
	);

	ThrowIfFailed(result);

	if (usedFeatureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, "Direct3D Feature Level 11 unsupported", 0, 0);
		throw DirectXException("Direct3D Feature Level 11 unsupported");
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
void GraphicsDevice::AssertMSAASupport()
{
	MSAAQuality = 0;

	HRESULT result = device->CheckMultisampleQualityLevels(MSAAFormat, MSAASampleCount, &MSAAQuality);

	ThrowIfFailed(result);

	assert(MSAAQuality > 0);
}