#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wrl.h>

#include <d3d11.h>
using namespace Microsoft::WRL;

class RasterizerState
{
public:
	explicit RasterizerState();
	explicit RasterizerState(const class GraphicsDevice* device);

	ID3D11RasterizerState* GetRawState();

private:
	void CreateState(struct D3D11_RASTERIZER_DESC* description, const class GraphicsDevice* device);
	D3D11_RASTERIZER_DESC GetDescription() const;

	ComPtr<ID3D11RasterizerState> rawState;
};