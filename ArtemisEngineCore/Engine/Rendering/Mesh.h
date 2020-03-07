#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace ArtemisEngine::Rendering
{
	struct Mesh
	{
	public:
		Mesh();
		
		VertexBuffer Vertices;
		IndexBuffer Indices;
	};
}