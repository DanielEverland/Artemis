#pragma once

#include "RenderingBufferDataContainer.h"
#include "Include/Game/Vector3.h"

namespace ArtemisEngine::Rendering
{
	struct VertexBufferData : public RenderingBufferDataContainer<Vector3>
	{
		using RenderingBufferDataContainer::RenderingBufferDataContainer;
		using RenderingBufferDataContainer::operator[];
	};
}