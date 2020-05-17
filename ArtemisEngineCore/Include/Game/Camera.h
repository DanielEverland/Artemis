#pragma once

#include "Include/Game/GameObject.h"

namespace ArtemisEngine
{
	class Camera : public GameObject
	{
	public:
		Camera();

		float VerticalFieldOfView;
		float NearClipDistance;
		float FarClipDistance;
				
		[[nodiscard]] Matrix GetViewMatrix() const;
		[[nodiscard]] Matrix GetProjectionMatrix() const;
	};
}