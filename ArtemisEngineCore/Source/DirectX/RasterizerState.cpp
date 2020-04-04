#include "RasterizerState.h"

#include <d3d11.h>

#include "DirectXHelper.h"
#include "GraphicsDevice.h"

RasterizerState::RasterizerState(const GraphicsDevice* device)
{
	D3D11_RASTERIZER_DESC description = GetDescription();
	CreateState(&description, device);
}

ID3D11RasterizerState* RasterizerState::GetRawState()
{
	return *(this->rawState);
}

void RasterizerState::CreateState(D3D11_RASTERIZER_DESC* description, const GraphicsDevice* device)
{
	ThrowIfFailed(device->GetRawDevice()->CreateRasterizerState(description, this->rawState));
}

D3D11_RASTERIZER_DESC RasterizerState::GetDescription() const
{
	D3D11_RASTERIZER_DESC description;

	description.FillMode = D3D11_FILL_SOLID;
	description.CullMode = D3D11_CULL_BACK;

	description.FrontCounterClockwise = false;
	description.DepthClipEnable = true;

	return description;
}