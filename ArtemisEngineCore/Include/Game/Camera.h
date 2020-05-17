#pragma once

#include "Include/Game/GameObject.h"

namespace ArtemisEngine
{
	class Camera : public GameObject
	{
	public:
		Camera();
		
		[[nodiscard]] Matrix GetViewMatrix() const;
	};
}