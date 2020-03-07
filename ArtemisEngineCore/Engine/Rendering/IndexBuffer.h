#pragma once

#include "RenderingBuffer.h"

namespace ArtemisEngine::Rendering
{
	struct IndexBuffer : public RenderingBuffer<int>
	{
		using RenderingBuffer::RenderingBuffer;
		using RenderingBuffer::operator[];
	};
}