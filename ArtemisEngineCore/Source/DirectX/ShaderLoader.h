#pragma once

#include <wrl.h>
#include <d3d11.h>

using Microsoft::WRL::ComPtr;

class ShaderLoader
{
public:
	static void LoadShaders(ComPtr<ID3D11Device>& device);
	
private:
	static const int BlobSize;
};
