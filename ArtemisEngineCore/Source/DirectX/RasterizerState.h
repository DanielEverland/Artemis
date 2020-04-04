#pragma once

#include <d3d11.h>

class RasterizerState
{
public:
	explicit RasterizerState(const class GraphicsDevice* device);

	ID3D11RasterizerState* GetRawState();

private:
	void CreateState(class D3D11_RASTERIZER_DESC* description, const class GraphicsDevice* device);
	D3D11_RASTERIZER_DESC GetDescription() const;

	class ID3D11RasterizerState** rawState;
};