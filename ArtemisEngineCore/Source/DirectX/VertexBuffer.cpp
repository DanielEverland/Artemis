#include "VertexBuffer.h"

#include <memory>

#include "DirectXHelper.h"
#include "GraphicsDevice.h"
#include "Engine/Rendering/VertexBufferData.h"

using namespace ArtemisEngine::Rendering;

VertexBuffer::VertexBuffer(const GraphicsDevice& device, const VertexBufferData& data)
{
	length = data.GetBufferSize();

	D3D11_BUFFER_DESC bufferDescription = CreateBufferDescription(data);
	D3D11_SUBRESOURCE_DATA resourcesData = CreateResourceData(data);

	CreateRawBuffer(device.GetRawDevice(), &bufferDescription, &resourcesData);
}
D3D11_BUFFER_DESC VertexBuffer::CreateBufferDescription(const VertexBufferData& data) const
{
	D3D11_BUFFER_DESC description;

	description.Usage = D3D11_USAGE_IMMUTABLE;
	description.ByteWidth = data.GetBufferSize() * sizeof(VertexData);
	description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	description.CPUAccessFlags = 0;
	description.MiscFlags = 0;
	description.StructureByteStride = 0;

	return description;
}
D3D11_SUBRESOURCE_DATA VertexBuffer::CreateResourceData(const VertexBufferData& data) const
{
	D3D11_SUBRESOURCE_DATA resourceData;

	// TEST - this is simply for testing vertex colouring.
	// Please remove
	static const int ColorCount = 8;
	static const XMFLOAT4 colors[ColorCount]
	{
		{ 1.0f, 1.0f, 1.0f, 1.0f }, // White
		{ 0.0f, 0.0f, 0.0f, 0.0f }, // Black
		{ 1.0f, 0.0f, 0.0f, 1.0f }, // Red
		{ 0.0f, 1.0f, 0.0f, 1.0f }, // Green
		{ 0.0f, 0.0f, 1.0f, 1.0f }, // Blue
		{ 1.0f, 1.0f, 0.0f, 1.0f }, // Yellow
		{ 0.0f, 1.0f, 1.0f, 1.0f }, // Cyan
		{ 1.0f, 0.0f, 1.0f, 1.0f }, // Magenta
	};

	std::shared_ptr<VertexData[]> vertexData(new VertexData[data.GetBufferSize()]);

	for (int i = 0; i < data.GetBufferSize(); i++)
	{
		XMFLOAT4 color = colors[i % ColorCount];
		
		vertexData[i].Pos = XMFLOAT3(data[i].X, data[i].Y, data[i].Z);
		vertexData[i].Color.x = color.x;
		vertexData[i].Color.y = color.y;
		vertexData[i].Color.z = color.z;
		vertexData[i].Color.w = color.w;
	}

	resourceData.pSysMem = &vertexData;

	return resourceData;
}
void VertexBuffer::CreateRawBuffer(const ComPtr<ID3D11Device> device, const D3D11_BUFFER_DESC* const description, const D3D11_SUBRESOURCE_DATA* const resource)
{
	ThrowIfFailed(device->CreateBuffer(
		description,
		resource,
		&rawBuffer));
}
ComPtr<ID3D11Buffer> VertexBuffer::GetRawBuffer() const
{
	return rawBuffer;
}
unsigned int VertexBuffer::GetStride() const
{
	return sizeof(VertexData);
}
int VertexBuffer::GetLength() const
{
	return length;
}