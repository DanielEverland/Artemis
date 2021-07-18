#pragma once

#include "DirectXCore.h"
#include "Core.h"

namespace ArtemisEngine
{
	class GraphicsDevice
	{
	public:
		GraphicsDevice(ComPtr<ID3D11Device> rawDevice);
		~GraphicsDevice();

		ComPtr<ID3D11Device> GetRaw() const;
		
		void GetMSAASupport(DXGI_FORMAT format, UINT* sampleCount, UINT* quality) const;
	
	private:
		static const UINT MSAASampleCount = 4;
		
		ComPtr<ID3D11Device> RawDevice;
	};
}
