#pragma once

#include "ObjectContainer.h"

namespace ArtemisEngine
{
	class IGameObject;
	class GameObjectContainer : public ObjectContainer<IGameObject>
	{
	};
}