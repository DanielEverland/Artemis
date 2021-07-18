#include "GraphicsDevice.h"

#include <utility>

using namespace ArtemisEngine;

GraphicsDevice::GraphicsDevice(ComPtr<ID3D11Device> rawDevice) : RawDevice(std::move(rawDevice))
{
}

GraphicsDevice::~GraphicsDevice()
{
	RawDevice->Release();
	RawDevice = nullptr;
}

ComPtr<ID3D11Device> GraphicsDevice::GetRaw() const
{
	return RawDevice;
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