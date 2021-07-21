﻿#pragma once

#include "Core.h"
#include "DirectXCore.h"

namespace ArtemisEngine
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void SetPosition(float, float, float);
		void SetRotation(float, float, float);

		XMFLOAT3 GetPosition();
		XMFLOAT3 GetRotation();

		void Render();
		void GetViewMatrix(XMMATRIX&);

	private:
		float m_positionX, m_positionY, m_positionZ;
		float m_rotationX, m_rotationY, m_rotationZ;
		XMMATRIX m_viewMatrix;
	};
}
