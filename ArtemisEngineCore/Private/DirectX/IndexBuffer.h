#pragma once

#include <d3d11.h>

#include "GraphicsDevice.h"
#include "Public/Game/IndexBufferData.h"

namespace ArtemisEngine::Rendering
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const GraphicsDevice& device, const IndexBufferData& data);

		DXGI_FORMAT GetFormat() const;
		ComPtr<ID3D11Buffer> GetRawBuffer();

		int GetLength() const;

	private:
		D3D11_BUFFER_DESC CreateBufferDescription(const IndexBufferData& data);
		D3D11_SUBRESOURCE_DATA CreateResourceData(const IndexBufferData& data);
		void CreateRawBuffer(const ComPtr<ID3D11Device> device, const D3D11_BUFFER_DESC* const description, const D3D11_SUBRESOURCE_DATA* const resource);

		ComPtr<ID3D11Buffer> rawBuffer;
		int length;
	};
}