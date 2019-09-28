#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wrl.h>

#include <d3d11.h>

using namespace Microsoft::WRL;

class GraphicsDevice
{
public:
	explicit GraphicsDevice();

	ComPtr<ID3D11Device> GetRawDevice() const;
	bool SupportsMSAA() const;
	UINT GetMSAASampleCount() const;
	UINT GetMSAAQuality() const;

private:
	static const DXGI_FORMAT MSAAFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	static const UINT MSAASampleCount = 4;

	static const UINT FeatureLevelCount = 1;
	static const D3D_FEATURE_LEVEL FeatureLevels
	{
		D3D_FEATURE_LEVEL_11_0,
	};

	static IDXGIAdapter* DefaultAdapter;
	static HMODULE DefaultSoftwareDevice;


	D3D_FEATURE_LEVEL usedFeatureLevel;
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	UINT MSAAQuality;

	void CreateDeviceObject();
	void AssertMSAASupport();
	UINT GetDeviceFlags();
};