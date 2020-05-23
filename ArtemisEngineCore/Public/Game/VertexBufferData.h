#pragma once

#include "Private/Game/Rendering/RenderingBufferDataContainer.h"
#include "Public/Game/Vector3.h"

namespace ArtemisEngine::Rendering
{
	struct VertexBufferData : public RenderingBufferDataContainer<Vector3>
	{
		using RenderingBufferDataContainer::RenderingBufferDataContainer;
		using RenderingBufferDataContainer::operator[];
	};
}