#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace ArtemisEngine::Rendering
{
	struct Mesh
	{
	public:		
		VertexBufferData Vertices;
		IndexBufferData Indices;
	};
}