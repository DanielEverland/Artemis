#pragma once

#include <DirectXMath.h>
#include <d3d11.h>

#include "GraphicsDevice.h"
#include "Engine/Rendering/VertexBufferData.h"

using namespace ArtemisEngine::Rendering;
using namespace DirectX;

class VertexBuffer
{
public:
	VertexBuffer(const GraphicsDevice& device, const VertexBufferData& data);

	unsigned int GetStride() const;
	int GetLength() const;

	ComPtr<ID3D11Buffer> GetRawBuffer() const;

private:
	struct VertexData
	{
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};

	D3D11_BUFFER_DESC CreateBufferDescription(const VertexBufferData& data) const;
	D3D11_SUBRESOURCE_DATA CreateResourceData(const VertexBufferData& data) const;
	void CreateRawBuffer(const ComPtr<ID3D11Device> device, const D3D11_BUFFER_DESC* const description, const D3D11_SUBRESOURCE_DATA* const resource);

	ComPtr<ID3D11Buffer> rawBuffer;
	int length;
};