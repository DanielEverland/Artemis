#pragma once

#include "ObjectContainer.h"

namespace ArtemisEngine
{
	class IComponent;
	class ComponentContainer : public ObjectContainer<IComponent>
	{
	};
}