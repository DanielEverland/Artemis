#pragma once

#include <d3d11.h>
#include <wrl.h>

#include "DirectXHelper.h"

using Microsoft::WRL::ComPtr;

namespace ArtemisEngine::Rendering
{
	struct VertexShaderObject
	{
	public:
		VertexShaderObject(ID3DBlob* blob, ComPtr<ID3D11VertexShader> shader, ComPtr<ID3D11Device>& device)
		{
			Shader = shader;
			
			D3D11_INPUT_ELEMENT_DESC inputLayout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			ThrowIfFailed(device->CreateInputLayout(inputLayout, 2, blob->GetBufferPointer(), blob->GetBufferSize(), &InputLayout));
		}

		ComPtr<ID3D11VertexShader> Shader;
		ComPtr<ID3D11InputLayout> InputLayout;
	};
}
