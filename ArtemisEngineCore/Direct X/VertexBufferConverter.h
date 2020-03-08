#pragma once

#include <d3d11.h>

#include "Engine/Rendering/VertexBuffer.h"

using namespace ArtemisEngine::Rendering;

// Converts a user-faced vertex buffer struct into a DX11 resource
class VertexBufferConverter
{
public:
	static ID3D11Buffer Convert(VertexBuffer buffer)
	{

	}
};