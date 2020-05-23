#pragma once

#include "Source/Game/Rendering/RenderingBufferDataContainer.h"

namespace ArtemisEngine::Rendering
{
	struct IndexBufferData : public RenderingBufferDataContainer<int>
	{
		using RenderingBufferDataContainer::RenderingBufferDataContainer;
		using RenderingBufferDataContainer::operator[];
	};
}