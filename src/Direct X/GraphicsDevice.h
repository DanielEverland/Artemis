#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wrl.h>
#include <string>
#include <map>
#include <d3d11.h>

using namespace Microsoft::WRL;
using std::string;

class GraphicsDevice
{
public:
	explicit GraphicsDevice();

	ComPtr<ID3D11Device> GetRawDevice() const;
	ComPtr<ID3D11DeviceContext> GetRawContext() const;

	void GetMSAASupport(DXGI_FORMAT format, UINT* sampleCount, UINT* quality) const;

private:
#pragma warning(disable : 26812)
	static const UINT MSAASampleCount = 4;
	static const UINT FeatureLevelCount = 1;
	static const D3D_FEATURE_LEVEL FeatureLevels
	{
		D3D_FEATURE_LEVEL_11_0,
	};

	static IDXGIAdapter* DefaultAdapter;
	static HMODULE DefaultSoftwareDevice;
#pragma warning(default : 26812)

	D3D_FEATURE_LEVEL usedFeatureLevel;
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	static const std::map<D3D_FEATURE_LEVEL, string> featureLevelNames;

	void CreateDeviceObject();	
	UINT GetDeviceFlags();
	string GetFeatureLevelString() const;

	void OutputDebugInfo() const;
	void OutputFeatureLevel() const;
	void OutputGraphicsAdapter() const;
};