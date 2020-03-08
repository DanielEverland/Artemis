#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const GraphicsDevice& device, const IndexBufferData& data)
{
	D3D11_BUFFER_DESC description = CreateBufferDescription(data);
	D3D11_SUBRESOURCE_DATA resourceData = CreateResourceData(data);

	CreateRawBuffer(device.GetRawDevice(), &description, &resourceData);
}
D3D11_BUFFER_DESC IndexBuffer::CreateBufferDescription(const IndexBufferData& data)
{
	D3D11_BUFFER_DESC description;

	description.Usage = D3D11_USAGE_IMMUTABLE;
	description.ByteWidth = sizeof(int) * data.GetBufferSize();
	description.BindFlags = D3D11_BIND_INDEX_BUFFER;
	description.CPUAccessFlags = 0;
	description.MiscFlags = 0;
	description.StructureByteStride = 0;

	return description;
}
D3D11_SUBRESOURCE_DATA IndexBuffer::CreateResourceData(const IndexBufferData& data)
{
	D3D11_SUBRESOURCE_DATA resourceData;

	resourceData.pSysMem = &data.Elements;

	return resourceData;
}
void IndexBuffer::CreateRawBuffer(const ComPtr<ID3D11Device> device, const D3D11_BUFFER_DESC* const description, const D3D11_SUBRESOURCE_DATA* const resource)
{
	device->CreateBuffer(description, resource, &rawBuffer);
}
ComPtr<ID3D11Buffer> IndexBuffer::GetRawBuffer()
{
	return rawBuffer;
}
DXGI_FORMAT IndexBuffer::GetFormat() const
{
	return DXGI_FORMAT_R32_UINT;
}