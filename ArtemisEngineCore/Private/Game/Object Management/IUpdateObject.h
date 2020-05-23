#pragma once

#include "IObject.h"

namespace ArtemisEngine
{
	class IUpdateObject : public IObject
	{
	public:
		virtual void Update() = 0;
	};
}
