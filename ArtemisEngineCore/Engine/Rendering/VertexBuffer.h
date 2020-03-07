#pragma once

#include "Engine/Vector3.h"

namespace ArtemisEngine::Rendering
{
	struct VertexBuffer : public RenderingBuffer<Vector3>
	{
		using RenderingBuffer::RenderingBuffer;
		using RenderingBuffer::operator[];
	};
}